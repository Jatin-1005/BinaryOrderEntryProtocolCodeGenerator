Hi, I realized I was over-complicating the design by attempting to apply callbacks for setting message information. It’s now clear that callbacks are better suited for the `BOE_Handler` responsible for publishing data, not for setting the message object itself.

**Decoder Design Cases:**

**Case 1: Templated `Decoder_1` Class by MessageType**

Templating the entire `Decoder` class by `MessageType` would require the compiler to generate a separate class for each message type. This is unnecessary; templating only the decoding member functions (e.g., `decode`, `_decode`) is more efficient.

```cpp
template <typename MessageType>
class Decoder_1 {
private:
	void _decode(start, end, LoginRequest msg, status);
    void _decode(start, end, NewOrder msg, status);
public:
	void decode(start, end, MessageType& msg, status) {
        _decode(start, end, msg, status);
    }
};
```

**Case 2: Improved `Decoder_2` with Templated Method Only**

To avoid redundant class generation, we removed the template parameter from `Decoder_2` and templated only the `decode` method.

```cpp
class Decoder_2 {
private:
	void _decode(start, end, LoginRequest msg, status);
    void _decode(start, end, NewOrder msg, status);
public:
    template <typename MessageType>
	void decode(start, end, MessageType& msg, status) {
        _decode(start, end, msg, status);
    }
};
```

**Case 3: Introducing `BOE_Handler` Callback for Decoding Events**

To allow logging or publishing during decoding, we introduced `BOE_Handler`, a user-implemented handler for callbacks. `Decoder` is templated with `HandlerType`, either at the class or member level.

```cpp
template <typename HandlerType>
class Decoder {
private:
    LoginRequest lr; NewOrder no; // Message objects are allocated once and reused.
    void _decodeLoginRequest(start, end, status) {
        auto StartOfMessage = readFrom(start, start + 4); 
        lr.setMessageType(StartOfMessage);
    }
public:
    void decode(start, end, HandlerType customHandler, status) {
        _decodeLoginRequest(start, end, status); // Populates the private message object.
        customHandler(msg); // User-defined handler for logging/publishing.
    }
};
```
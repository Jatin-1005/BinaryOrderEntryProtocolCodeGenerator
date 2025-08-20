
---

# **Binary Order Entry Protocol Code Generator**

Hello there! 👋

I am **Subhash** (Padala Sri Siva Shyama Sri Venkata Sri Vishnu Subhash), and I am excited to share my **BOE Code Generator** project which auto-generates C++ encoder, decoder, and message object code from a YAML schema for the BOE protocol. It provides complete support for all BOE protocol features, such as constrained fields, optional fields, and nested repeating groups — without introducing concurrency or the full scope of a FIX engine.

Think of it as:
Fix8-style codegen for low-latency BOE trading, minus the engine overhead.

## 📄 Project Documents

To better understand the motivation, technical implementation, and design goals of the BOE Code Generator, refer to the following:

- 📘 [Problem Statement](./docs/Problem%20Statement.pdf): What challenges this tool solves and why it was built.
- 💼 [Business Overview](./docs/Bussiness%20Overview.pdf): Non-technical presentation focusing on impact, use cases, and project value.
- 🛠️ [Technical Deep Dive](./docs/Technical%20Overview.pdf): Engineering-focused slides covering architecture, design patterns, and implementation challenges.

## **Key Features:**

This tool is designed to automate the process of generating and managing C++ code for different versions of **BOE (Binary Order Entry)** protocol. With this generator, you can effortlessly handle different protocol versions and related complexities. Key features include:

- **Constant Fields**: Automatically handles fields that are fixed in value (e.g., StartOfMessage).
- **Constrained Fields**: Fields with limited, predefined possible values.
- **Optional Fields**: Flexibly handle fields that may or may not appear in a message.
- **Repeating Groups**: Efficient handling of groups of fields that repeat an arbitrary number of times.
- **Param Groups**: Support for parameter groups, each having its own set of fields.
- **Nested Repeating Groups**: Nested structures that allow groups to contain other repeating groups.


- **Verification**: Supports different verifications checks like invalid message_type, invalid_payload, invalid_object, etc.
- **Error Handling**: Error is populated in status object instead of throwing exceptions.
- **Optimization**: Using C++ features like static polymorphism, constexpr, static and noexcept, etc to optimize the run-time performance.
- **Constructor**: Support constructor to create different types of groups with ease. Example: `loginRequest.setGroupUnitSequences(GroupUnitSequences(0x000F, GroupUnitSequences::NoUnspecifiedUnitReplayEnum::TRUE, std::vector<GroupNumberOfUnits>{GroupNumberOfUnits(0x1, 0x0001bb4a), GroupNumberOfUnits(0x02, 0x00)}));`

## **Usage**

Here’s how to get started with the BOE Code Generator. 👇

### **Step 1: Set Up the Environment**

```sh
# Navigate to your project directory and activate the environment
cd ./Subhash/src
source ../.env/bin/activate
```

### **Step 2: Generate C++ Code**

Once the environment is set up, generate the C++ code based on the YAML protocol specification for your desired exchange, protocol, and version.

```sh
# Generate code for BOE Protocol (version 2.11.68) for C1 exchange
# The generated files will be placed in codecs/<exchange>/<protocol>/<version>/
python3 ./generate_codec.py --config c1_boe_2_11_68.yaml --preview --create
```

### **Step 3: Compile and Test**

The generated code includes the necessary header files and test files to validate the functionality.

```sh
# Navigate to the generated folder for C1/BOE/2_11_68
cd ./codecs/C1/BOE/2_11_68/

# Compile the generated C++ test file with optimizations
g++ -O3 test.cpp -o test.out

# Run the compiled test executable with sample payloads
./test.out 55 tests/LoginRequest.txt
./test.out 65 tests/NewCrossOrder.txt
```

### **Step 4: Customize and Use**

- **Add Custom Handlers**: Modify the `BOE_Handler.h` file to suit your custom logic.
- **Write Unit Tests**: Modify or extend the `test.cpp` file to add additional test cases as per your requirements.


## **Project Structure**

Here’s how the project is organized for maximum clarity and ease of use:

- **[common](./src/common)**  
  Contains shared utilities across all BOE protocol versions:
  - `status.h`: Handles various statuses during encoding/decoding.
  - `stopwatch.h`: Utility for measuring the duration of operations.
  - `utils.h`: Miscellaneous helper functions.

- **[codecs/C1/BOE/2_11_68](./src/codecs/C1/BOE/2_11_68/)**  
  This folder contains the generated code, including:
  - **spec**: The YAML specification file used as input.
  - **BOE_Msgs.h, BOE_Encoder.h, BOE_Decoder.h, BOE_Stream.h**: Generated header files.
  - **test.cpp**: A sample unit test file to validate the generated code.
  - **BOE_Handler.h**: A file for custom handlers that you can modify for specific use cases.

- **[templates](./src/templates/)**  
  Contains all the Jinja2 templates used for code generation. The templates are designed for:
  - **Message Class**: Defines how to structure messages, including fields and groups.
  - **Encoder**: Responsible for efficiently encoding protocol messages.
  - **Decoder**: Decodes received messages back into usable structures.
  - **ostream**: Defines how to output the messages in a readable format.

The code generation is highly customizable. By simply modifying the YAML file and Jinja2 templates, you can adapt the code generator to support new versions of BOE or even different protocols.

Note: The encoder encodes message object to binary payload, convertBinaryToHex is used to convert binary to hex payload.

### **Code Comments in Jinja2 Templates**
The comments in the generated code are automatically populated from the Jinja2 templates, I have specified most comments in Jinja2, since the generated code is self-explanatory from the meta-comments.

## **Why This Code Generator?**

This tool provides a clean, automated solution for generating C++ code for the BOE protocol. Key benefits include:

- **High Flexibility**: Supports various complex field types, including repeating groups and param groups.
- **Easy Maintenance**: The YAML configuration file acts as the single source of truth. Modify the YAML and regenerate the code to reflect protocol changes.
- **High Performance**: The generated code is optimized for low-latency systems, making it suitable for high-frequency trading (HFT) applications.
- **Future-Proof**: The YAML schema design is modular to supports easy updates to new protocol versions, allowing you to keep up with evolving standards without the need for manual code changes.


## **PS: Code Formatting**

Apologies for the inconvenience, but the generated C++ code may require formatting.

Please use tools like clang-format or astyle to automatically format the code for consistency and readability.

---
**Arigatoooo!** 🙏 

Let me know if you need further clarification or have any questions!
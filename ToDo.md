* [ ] AI automatically gather the examples from the document, and generate the test files. (should be one of my selling point)
* [ ] throwing exception is not correct way, updating status to BUFFER_OVERFLOW or someother value should revert to finding nextStart = BABA, rather than continuously reading, and writing, it should stop.
* [ ] Adding comments to the templates.
* [-] Template metaprogramming can be done, to generate encoding of predefined fields, to enable fast encoding.
* [-] cases where negative index are given is not handled. Throwing error is the only way I could see, or just automatically let it fail? Fuzzing testing POV needs to be seen
* [ ] break the template into multiple subtemplates, nd modify the generate_codec.py accordingly, this allows easy finding of which template is generating issue code.
* [ ] The status buffer overflow can be updated, based on the MessageLength, and ParamGroupLength arguments.
* [ ] MessageLength and ParamGroupLength variables should be automatically updated, might be good if we can do that.
* [ ] types which have constraints, and types which can take `0` or `1` , `True` or `False`
* [ ] alphanumeric, alpha, text, DataTime and Date etc.
* [ ] the above things are required to make the code error free.
* [ ] maintan the status object same for encoder and decoder, the design should work the same. 
* [ ] intially metaData was used, but now metaData was removed to make everything as ParamGroups, and ParamGroups can have fixed sizeEntries
* [ ] optional returnbitfield thing with nested classes, inside if 'ParamGroups' add nested if 'Optionals' to handle it appropriately, the nested class will manipulate the bitfield or another option is the returnbitfield of message class is directly dependent on 'optionXYZ_1' 's returnbitfield member.

* [ ] default constructor and temporary object based constructor are created, can implement Length thingy also fast.
* [ ] move assignment operator should be declared, then decoder simply reads and verifies the payload, like better to first verify and then read or read or what to do?
        // how to handle for unknow in enum, remove it from map, and then do rest of the logic
        // for constant types, just do the checkup enough.

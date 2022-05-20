# ethereum-rpc-cpp
Wrapper written in C++ for the ethereum JSON-RPC.

**NOTE:**
Please note that this project is still a WIP. Features are expected to be added and the codebase possibly to be reworked / refactored.

### Dependencies
 - [libcurl](https://github.com/curl/curl)
 - [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

### Practice
This wrapper also converts results that are considered (integer) overflow save into actual integers rather than hexadecimal strings. The main reason for this is to reduce the amount of code neccessary when utilizing this library. If you however disagree with this then feel free to alter the code to your needs. This is after all more of a library for private use that I have happened to open-source.

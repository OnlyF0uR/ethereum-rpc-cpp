# ethereum-rpc-cpp
Library written in C++ 11 that serves as a wrapper / handler for the ethereum JSON-RPC.

**NOTE:**
Please note that this project is still a WIP. Features are expected to be added and the codebase possibly to be reworked / refactored.

### Dependencies
 - [libcurl](https://github.com/curl/curl)
 - [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

### Building
```bash
mkdir -p build
cd build
cmake --DCURL_INCLUDE_DIR=/path/to/curl/include --DJSONCPP_INCLUDE_DIR=/path/to/jsoncpp/include ..
```
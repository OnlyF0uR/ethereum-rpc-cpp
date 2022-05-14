# ethereum-rpc-cpp
Wrapper written in C++ for the ethereum JSON-RPC.

### Practice
This wrapper also converts results that are considered (integer) overflow save into actual integers rather than hexadecimal strings. The main reason for this is to reduce the amount of code neccessary when utilizing this library. If you however disagree with this then feel free to alter the code to your needs. This is after all more of a library for private use that I have happened to open-source.

#include <iostream>
#include "eth-rpc/wrapper.hh"

int main() {
    std::string rpcUrl = "http://localhost:8545";

    Wrapper wr = Wrapper(&rpcUrl);

    return 0;
}
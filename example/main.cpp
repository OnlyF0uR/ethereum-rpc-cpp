#include <iostream>
#include "wrapper.hh"
#include "endpoints/getter.hh"

int main() {
    Wrapper wr = Wrapper("http://localhost:8545");
    Getter getter = Getter(&wr);

    // Block number
    int blockNumber = getter.BlockNumber();
    if (blockNumber != -1) {
        std::cout << "BlockNumber: " << blockNumber << std::endl;
    }

    return 0;
}
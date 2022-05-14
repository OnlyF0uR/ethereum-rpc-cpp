#include <iostream>
#include "wrapper.hh"
#include "endpoints/getter.hh"
#include <unistd.h>

int main() {
    Wrapper wr = Wrapper("http://localhost:8545");
    Getter getter = Getter(&wr);

    // Block number
    BlockNumberResult *block_num = getter.BlockNumber();
    if (block_num != NULL) {
        std::cout << "BlockNumber: " << block_num->blockNumber << std::endl;
        delete block_num;
    } else {
        std::cout << "block_num is NULL" << std::endl;
    }

    // // Get block by hash
    // BlockResult *hash_block = getter.BlockByHash("0x3b1a11cad7b09dee442ba3df78dc1f7d2faa623c8773d24a90a25635e39a9f8a", false);
    // if (hash_block != NULL) {
    //     std::cout << "BlockInfo (Hash):\n";
    //     std::cout << " - Hash: " << hash_block->block.hash << "\n";
    //     std::cout << " - ParentHash: " << hash_block->block.parentHash << "\n";
    //     std::cout << " - Difficulty: " << hash_block->block.difficulty << "\n";
    //     std::cout << " - GasUsed: " << hash_block->block.gasUsed << "\n";
    //     std::cout << " - Nonce: " << hash_block->block.nonce << "\n";
    //     std::cout << " - Number: " << hash_block->block.number << std::endl;
    //     delete hash_block;
    // } else {
    //     std::cout << "hash_block is NULL" << std::endl;
    // }

    // // Get block by number (or, in this case tag (earliest, latest or pending))
    // BlockResult *num_block = getter.BlockByNumber("latest", false);
    // if (num_block != NULL) {
    //     std::cout << "BlockInfo (Latest):\n";
    //     std::cout << " - Hash: " << num_block->block.hash << "\n";
    //     std::cout << " - ParentHash: " << num_block->block.parentHash << "\n";
    //     std::cout << " - Difficulty: " << num_block->block.difficulty << "\n";
    //     std::cout << " - GasUsed: " << num_block->block.gasUsed << "\n";
    //     std::cout << " - Nonce: " << num_block->block.nonce << "\n";
    //     std::cout << " - Number: " << num_block->block.number << std::endl;
    //     delete num_block;
    // } else {
    //     std::cout << "num_block is NULL" << std::endl;
    // }

    return 0;
}
#ifndef TYPES_DOT_H
#define TYPES_DOT_H
#include <iostream>

// ===============================
struct Default
{
    std::string jsonrpc;
    int id; 
};

// ===============================
struct BlockNumberResult : Default
{
    int data;
};

// ===============================
struct Block
{
    int baseFeePerGas;
    std::string difficulty;
    std::string extraData;
    int gasLimit;
    int gasUsed;
    std::string hash;
    std::string logsBloom;
    std::string miner;
    std::string mixHash;
    std::string nonce;
    int number;
    std::string parentHash;
    std::string receiptsRoot;
    std::string sha3Uncles;
    int size;
    std::string stateRoot;
    int timestamp;
    std::string totalDifficulty;
    Json::Value transactions;
    std::string transactionsRoot;
    Json::Value uncles;
};

struct BlockResult : Default
{
    Block block; 
};

// ===============================

#endif
#ifndef GETTER_DOT_H
#define GETTER_DOT_H
#include "wrapper.hh"
#include "json/json.h"

class Wrapper;

class Getter
{
  public:
    Getter(Wrapper *wr);

    int BlockNumber();
    Json::Value BlockByHash(std::string tag, bool full);
    Json::Value BlockByNumber(std::string tag, bool full);

    Json::Value TransactionByHash(std::string hash);
    Json::Value TransactionCount(std::string address, std::string tag);
    Json::Value TransactionReceipt(std::string hash);
    Json::Value TransactionCountByHash(std::string hash);
    Json::Value TransactionCountByNumber(std::string tag);
    Json::Value TransactionByBlockHashAndIndex(std::string hash, int quantity);
    Json::Value TransactionByBlockNumberAndIndex(std::string tag, int quantity);

    int Balance(std::string address, std::string tag);
    std::string Code(std::string address, std::string tag);
    std::string StorageAt(std::string address, std::string pos, std::string tag);
    std::string *Accounts();
    Json::Value Proof(std::string address, std::string *storageKeys, std::string tag);
    // TODO: Logs
    int ProtocolVersion();
    int GasPrice();
    // TODO: Estimate Gas
    // TODO: Fee history
    int PriorityFeePerGas();
    int ChainId();
    int NetVersion();
    bool NetListing();
    int UncleByBlockNumberAndIndex(std::string tag, int index);
    int UncleByBlockHashAndIndex(std::string tag, int index);
    int UncleCountByBlockHash(std::string hash);
    // TODO: UncleCountByBlockNumber
    // TODO: FilterChanges
    // TODO: FilterLogs
    int NewBlockFilter();

  private:
    Wrapper *wrapper;
};

#endif
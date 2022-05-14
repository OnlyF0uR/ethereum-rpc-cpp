#ifndef GETTER_DOT_H
#define GETTER_DOT_H
#include "wrapper.hh"
#include "json/json.h"
#include "types.hh"

// https://eth.wiki/json-rpc/API

class Wrapper;

class Getter
{
  public:
    Getter(Wrapper *wr);

    NetVersionResult *NetVersion();
    NetListingResult *NetListing();
    NetPeerCountResult *NetPeerCount();

    ProtocolVersionResult *ProtocolVersion();
    SyncingResult *Syncing();
    CoinbaseResult *Coinbase();
    MiningResult *Mining();
    HashrateResult *Hashrate();
    GasPriceResult *GasPrice();
    AccountsResult *Accounts();
    BlockNumberResult *BlockNumber();
    BalanceResult *Balance(std::string address, std::string tag);
    StorageAtResult *StorageAt(std::string address, int pos, std::string tag);


    // Blocks
    // BlockResult *BlockByHash(std::string hash, bool full);
    // BlockResult *BlockByNumber(std::string tag, bool full);
    // Transactions
    // TransactionResult *TransactionByHash(std::string hash);
    // TransactionCountResult *TransactionCount(std::string address, std::string tag);

  private:
    Wrapper *wrapper;
};

#endif
#include "getter.hh"

Getter::Getter(Wrapper *wr)
{
    wrapper = wr;
}

NetVersionResult *Getter::NetVersion()
{
    Json::Value buffer;
    wrapper->SendJson("net_version", &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    NetVersionResult *result = new NetVersionResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->netVersion = buffer["result"].asInt();

    return result;
}

NetListingResult *Getter::NetListing()
{
    Json::Value buffer;
    wrapper->SendJson("net_listening", &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    NetListingResult *result = new NetListingResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->listing = buffer["result"].asBool();

    return result;
}

NetPeerCountResult *Getter::NetPeerCount()
{
    Json::Value buffer;
    wrapper->SendJson("net_peerCount", &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    NetPeerCountResult *result = new NetPeerCountResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->peerCount = std::stoul(buffer["result"].asString(), nullptr, 16);

    return result;
}

ProtocolVersionResult *Getter::ProtocolVersion()
{
    Json::Value buffer;
    wrapper->SendJson("eth_protocolVersion", &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    ProtocolVersionResult *result = new ProtocolVersionResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->protocolVersion = buffer["result"].asInt();

    return result;
}

SyncingResult *Getter::Syncing()
{
    Json::Value buffer;
    wrapper->SendJson("eth_syncing", &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    SyncingResult *result = new SyncingResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->startingBlock = std::stoul(buffer["result"]["startingBlock"].asString(), nullptr, 16);
    result->currentBlock = std::stoul(buffer["result"]["currentBlock"].asString(), nullptr, 16);
    result->highestBlock = std::stoul(buffer["result"]["highestBlock"].asString(), nullptr, 16);

    return result;
}

CoinbaseResult *Getter::Coinbase()
{
    Json::Value buffer;
    wrapper->SendJson("eth_coinbase", &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    CoinbaseResult *result = new CoinbaseResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->coinbaseAddress = buffer["result"].asString();

    return result;
}

MiningResult *Getter::Mining()
{
    Json::Value buffer;
    wrapper->SendJson("eth_mining", &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    MiningResult *result = new MiningResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->mining = buffer["result"].asBool();

    return result;
}

HashrateResult *Getter::Hashrate()
{
    Json::Value buffer;
    wrapper->SendJson("eth_hashrate", &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    HashrateResult *result = new HashrateResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->hashrate = std::stoul(buffer["result"].asString(), nullptr, 16);

    return result;
}

GasPriceResult *Getter::GasPrice()
{
    Json::Value buffer;
    wrapper->SendJson("eth_gasPrice", &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    GasPriceResult *result = new GasPriceResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->gasPrice = std::stoul(buffer["result"].asString(), nullptr, 16);

    return result;
}

AccountsResult *Getter::Accounts()
{
    Json::Value buffer;
    wrapper->SendJson("eth_accounts", &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    AccountsResult *result = new AccountsResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->accounts = buffer["result"];

    return result;
}

BlockNumberResult *Getter::BlockNumber()
{
    Json::Value buffer;
    wrapper->SendJson("eth_blockNumber", &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    BlockNumberResult *result = new BlockNumberResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->blockNumber = std::stoul(buffer["result"].asString(), nullptr, 16);

    return result;
}

BalanceResult *Getter::Balance(std::string address, std::string tag)
{
    Json::Value params(Json::arrayValue);
    params.append(address);
    params.append(tag);

    Json::Value buffer;
    wrapper->SendJson("eth_getBalance", params, &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    BalanceResult *result = new BalanceResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->balance = InfInt(buffer["result"].asString());

    return result;
}

StorageAtResult *Getter::StorageAt(std::string address, int pos, std::string tag)
{
    Json::Value params(Json::arrayValue);
    params.append(address);
      
    std::stringstream stream;
    stream << "0x" 
         << std::setfill ('0') << std::setw(sizeof(pos)*2) 
         << std::hex << pos;
    params.append(stream.str());

    params.append(tag);

    Json::Value buffer;
    wrapper->SendJson("eth_getStorageAt", params, &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    StorageAtResult *result = new StorageAtResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    result->storageValue = buffer["result"].asString();

    return result;
}

// BlockResult *Getter::BlockByHash(std::string hash, bool full)
// {
//     Json::Value params(Json::arrayValue);
//     params.append(hash);
//     params.append(full);

//     Json::Value buffer;
//     wrapper->SendJson("eth_getBlockByHash", params, &buffer);

//     if (buffer.empty())
//     {
//         return NULL;
//     }

//     if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
//     {
//         return NULL;
//     }

//     BlockResult *result = new BlockResult();
//     if (result == NULL)
//     {
//         return NULL;
//     }

//     result->jsonrpc = buffer["jsonrpc"].asString();
//     result->id = buffer["id"].asInt();

//     result->block.hash = buffer["result"]["hash"].asString();

//     result->block.baseFeePerGas = std::stoul(buffer["result"]["baseFeePerGas"].asString(), nullptr, 16);
//     result->block.difficulty = buffer["result"]["difficulty"].asString();
//     result->block.extraData = buffer["result"]["extraData"].asString();
//     result->block.gasLimit = std::stoul(buffer["result"]["gasLimit"].asString(), nullptr, 16);
//     result->block.gasUsed = std::stoul(buffer["result"]["gasUsed"].asString(), nullptr, 16);
//     result->block.hash = buffer["result"]["hash"].asString();
//     result->block.logsBloom = buffer["result"]["logsBloom"].asString();
//     result->block.miner = buffer["result"]["miner"].asString();
//     result->block.mixHash = buffer["result"]["mixHash"].asString();
//     result->block.nonce = buffer["result"]["nonce"].asString();
//     result->block.number = std::stoul(buffer["result"]["number"].asString(), nullptr, 16);
//     result->block.parentHash = buffer["result"]["parentHash"].asString();
//     result->block.receiptsRoot = buffer["result"]["receiptsRoot"].asString();
//     result->block.sha3Uncles = buffer["result"]["sha3Uncles"].asString();
//     result->block.size = std::stoul(buffer["result"]["size"].asString(), nullptr, 16);
//     result->block.stateRoot = buffer["result"]["stateRoot"].asString();
//     result->block.timestamp = std::stoul(buffer["result"]["timestamp"].asString(), nullptr, 16);
//     result->block.totalDifficulty = buffer["result"]["totalDifficulty"].asString();
//     result->block.transactions = buffer["result"]["transactions"];
//     result->block.transactionsRoot = buffer["result"]["transactionsRoot"].asString();
//     result->block.uncles = buffer["result"]["uncles"];

//     return result;
// }

// BlockResult *Getter::BlockByNumber(std::string tag, bool full)
// {
//     Json::Value params(Json::arrayValue);
//     params.append(tag);
//     params.append(full);

//     Json::Value buffer;
//     wrapper->SendJson("eth_getBlockByNumber", params, &buffer);

//     if (buffer.empty())
//     {
//         return NULL;
//     }

//     if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
//     {
//         return NULL;
//     }

//     BlockResult *result = new BlockResult();
//     if (result == NULL)
//     {
//         return NULL;
//     }

//     result->jsonrpc = buffer["jsonrpc"].asString();
//     result->id = buffer["id"].asInt();

//     result->block.hash = buffer["result"]["hash"].asString();
//     result->block.baseFeePerGas = std::stoul(buffer["result"]["baseFeePerGas"].asString(), nullptr, 16);
//     result->block.difficulty = buffer["result"]["difficulty"].asString();
//     result->block.extraData = buffer["result"]["extraData"].asString();
//     result->block.gasLimit = std::stoul(buffer["result"]["gasLimit"].asString(), nullptr, 16);
//     result->block.gasUsed = std::stoul(buffer["result"]["gasUsed"].asString(), nullptr, 16);
//     result->block.hash = buffer["result"]["hash"].asString();
//     result->block.logsBloom = buffer["result"]["logsBloom"].asString();
//     result->block.miner = buffer["result"]["miner"].asString();
//     result->block.mixHash = buffer["result"]["mixHash"].asString();
//     result->block.nonce = buffer["result"]["nonce"].asString();
//     result->block.number = std::stoul(buffer["result"]["number"].asString(), nullptr, 16);
//     result->block.parentHash = buffer["result"]["parentHash"].asString();
//     result->block.receiptsRoot = buffer["result"]["receiptsRoot"].asString();
//     result->block.sha3Uncles = buffer["result"]["sha3Uncles"].asString();
//     result->block.size = std::stoul(buffer["result"]["size"].asString(), nullptr, 16);
//     result->block.stateRoot = buffer["result"]["stateRoot"].asString();
//     result->block.timestamp = std::stoul(buffer["result"]["timestamp"].asString(), nullptr, 16);
//     result->block.totalDifficulty = buffer["result"]["totalDifficulty"].asString();
//     result->block.transactions = buffer["result"]["transactions"];
//     result->block.transactionsRoot = buffer["result"]["transactionsRoot"].asString();
//     result->block.uncles = buffer["result"]["uncles"];

//     return result;
// }

// TransactionResult *Getter::TransactionByHash(std::string hash)
// {
//     Json::Value params(Json::arrayValue);
//     params.append(hash);

//     Json::Value buffer;
//     wrapper->SendJson("eth_getTransactionByHash", params, &buffer);

//     if (buffer.empty())
//     {
//         return NULL;
//     }

//     if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
//     {
//         return NULL;
//     }

//     TransactionResult *result = new TransactionResult();
//     if (result == NULL)
//     {
//         return NULL;
//     }

//     result->jsonrpc = buffer["jsonrpc"].asString();
//     result->id = buffer["id"].asInt();
    
//     result->transaction.hash = buffer["result"]["hash"].asString();
//     result->transaction.blockHash = buffer["result"]["blockHash"].asString();
//     result->transaction.blockNumber = std::stoul(buffer["result"]["blockNumber"].asString(), nullptr, 16);
//     result->transaction.from = buffer["result"]["from"].asString();
//     result->transaction.gas = std::stoul(buffer["result"]["gas"].asString(), nullptr, 16);
//     result->transaction.gasPrice = buffer["result"]["gasPrice"].asString();
//     result->transaction.input = buffer["result"]["input"].asString();
//     result->transaction.nonce = std::stoul(buffer["result"]["nonce"].asString(), nullptr, 16);
//     result->transaction.r = buffer["result"]["r"].asString();
//     result->transaction.s = buffer["result"]["s"].asString();
//     result->transaction.to = buffer["result"]["to"].asString();
//     result->transaction.transactionIndex = std::stoul(buffer["result"]["transactionIndex"].asString(), nullptr, 16);
//     result->transaction.v = std::stoul(buffer["result"]["v"].asString(), nullptr, 16);
//     result->transaction.value = buffer["result"]["value"].asString();

//     return result;
// }

// TransactionCountResult *Getter::TransactionCount(std::string address, std::string tag)
// {
//     Json::Value params(Json::arrayValue);
//     params.append(address);
//     params.append(tag);

//     Json::Value buffer;
//     wrapper->SendJson("eth_getTransactionCount", params, &buffer);

//     if (buffer.empty())
//     {
//         return NULL;
//     }

//     if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
//     {
//         return NULL;
//     }

//     TransactionCountResult *result = new TransactionCountResult();
//     if (result == NULL)
//     {
//         return NULL;
//     }

//     result->jsonrpc = buffer["jsonrpc"].asString();
//     result->id = buffer["id"].asInt();

//     result->count = std::stoul(buffer["result"].asString(), nullptr, 16);;
// }
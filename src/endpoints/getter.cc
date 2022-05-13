#include "getter.hh"

Getter::Getter(Wrapper *wr)
{
    wrapper = wr;
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
    result->data = std::stoul(buffer["result"].asString(), nullptr, 16);

    return result;
}

BlockResult *Getter::BlockByHash(std::string hash, bool full)
{
    Json::Value params(Json::arrayValue);
    params.append(hash);
    params.append(full);

    Json::Value buffer;
    wrapper->SendJson("eth_getBlockByHash", params, &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    BlockResult *result = new BlockResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();

    result->block.hash = buffer["result"]["hash"].asString();

    result->block.baseFeePerGas = std::stoul(buffer["result"]["baseFeePerGas"].asString(), nullptr, 16);
    result->block.difficulty = buffer["result"]["difficulty"].asString();
    result->block.extraData = buffer["result"]["extraData"].asString();
    result->block.gasLimit = std::stoul(buffer["result"]["gasLimit"].asString(), nullptr, 16);
    result->block.gasUsed = std::stoul(buffer["result"]["gasUsed"].asString(), nullptr, 16);
    result->block.hash = buffer["result"]["hash"].asString();
    result->block.logsBloom = buffer["result"]["logsBloom"].asString();
    result->block.miner = buffer["result"]["miner"].asString();
    result->block.mixHash = buffer["result"]["mixHash"].asString();
    result->block.nonce = buffer["result"]["nonce"].asString();
    result->block.number = std::stoul(buffer["result"]["number"].asString(), nullptr, 16);
    result->block.parentHash = buffer["result"]["parentHash"].asString();
    result->block.receiptsRoot = buffer["result"]["receiptsRoot"].asString();
    result->block.sha3Uncles = buffer["result"]["sha3Uncles"].asString();
    result->block.size = std::stoul(buffer["result"]["size"].asString(), nullptr, 16);
    result->block.stateRoot = buffer["result"]["stateRoot"].asString();
    result->block.timestamp = std::stoul(buffer["result"]["timestamp"].asString(), nullptr, 16);
    result->block.totalDifficulty = buffer["result"]["totalDifficulty"].asString();
    result->block.transactions = buffer["result"]["transactions"];
    result->block.transactionsRoot = buffer["result"]["transactionsRoot"].asString();
    result->block.uncles = buffer["result"]["uncles"];

    return result;
}

BlockResult *Getter::BlockByNumber(std::string tag, bool full)
{
    Json::Value params(Json::arrayValue);
    params.append(tag);
    params.append(full);

    Json::Value buffer;
    wrapper->SendJson("eth_getBlockByNumber", params, &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    BlockResult *result = new BlockResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();

    result->block.hash = buffer["result"]["hash"].asString();
    result->block.baseFeePerGas = std::stoul(buffer["result"]["baseFeePerGas"].asString(), nullptr, 16);
    result->block.difficulty = buffer["result"]["difficulty"].asString();
    result->block.extraData = buffer["result"]["extraData"].asString();
    result->block.gasLimit = std::stoul(buffer["result"]["gasLimit"].asString(), nullptr, 16);
    result->block.gasUsed = std::stoul(buffer["result"]["gasUsed"].asString(), nullptr, 16);
    result->block.hash = buffer["result"]["hash"].asString();
    result->block.logsBloom = buffer["result"]["logsBloom"].asString();
    result->block.miner = buffer["result"]["miner"].asString();
    result->block.mixHash = buffer["result"]["mixHash"].asString();
    result->block.nonce = buffer["result"]["nonce"].asString();
    result->block.number = std::stoul(buffer["result"]["number"].asString(), nullptr, 16);
    result->block.parentHash = buffer["result"]["parentHash"].asString();
    result->block.receiptsRoot = buffer["result"]["receiptsRoot"].asString();
    result->block.sha3Uncles = buffer["result"]["sha3Uncles"].asString();
    result->block.size = std::stoul(buffer["result"]["size"].asString(), nullptr, 16);
    result->block.stateRoot = buffer["result"]["stateRoot"].asString();
    result->block.timestamp = std::stoul(buffer["result"]["timestamp"].asString(), nullptr, 16);
    result->block.totalDifficulty = buffer["result"]["totalDifficulty"].asString();
    result->block.transactions = buffer["result"]["transactions"];
    result->block.transactionsRoot = buffer["result"]["transactionsRoot"].asString();
    result->block.uncles = buffer["result"]["uncles"];

    return result;
}

TransactionResult *Getter::TransactionByHash(std::string hash)
{
    Json::Value params(Json::arrayValue);
    params.append(hash);

    Json::Value buffer;
    wrapper->SendJson("eth_getTransactionByHash", params, &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    TransactionResult *result = new TransactionResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();
    
    result->transaction.hash = buffer["result"]["hash"].asString();
    result->transaction.blockHash = buffer["result"]["blockHash"].asString();
    result->transaction.blockNumber = std::stoul(buffer["result"]["blockNumber"].asString(), nullptr, 16);
    result->transaction.from = buffer["result"]["from"].asString();
    result->transaction.gas = std::stoul(buffer["result"]["gas"].asString(), nullptr, 16);
    result->transaction.gasPrice = buffer["result"]["gasPrice"].asString();
    result->transaction.input = buffer["result"]["input"].asString();
    result->transaction.nonce = std::stoul(buffer["result"]["nonce"].asString(), nullptr, 16);
    result->transaction.r = buffer["result"]["r"].asString();
    result->transaction.s = buffer["result"]["s"].asString();
    result->transaction.to = buffer["result"]["to"].asString();
    result->transaction.transactionIndex = std::stoul(buffer["result"]["transactionIndex"].asString(), nullptr, 16);
    result->transaction.v = std::stoul(buffer["result"]["v"].asString(), nullptr, 16);
    result->transaction.value = buffer["result"]["value"].asString();

    return result;
}

TransactionCountResult *Getter::TransactionCount(std::string address, std::string tag)
{
    Json::Value params(Json::arrayValue);
    params.append(address);
    params.append(tag);

    Json::Value buffer;
    wrapper->SendJson("eth_getTransactionCount", params, &buffer);

    if (buffer.empty())
    {
        return NULL;
    }

    if (buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull())
    {
        return NULL;
    }

    TransactionCountResult *result = new TransactionCountResult();
    if (result == NULL)
    {
        return NULL;
    }

    result->jsonrpc = buffer["jsonrpc"].asString();
    result->id = buffer["id"].asInt();

    result->count = std::stoul(buffer["result"].asString(), nullptr, 16);;
}
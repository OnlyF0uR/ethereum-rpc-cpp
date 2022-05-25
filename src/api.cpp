#include "api.hpp"

Api::Api(Wrapper* wr)
{
	wrapper = wr;
}

NetVersionResult* Api::NetVersion()
{
	Json::Value buffer;
	wrapper->SendJson("net_version", &buffer);

	VALIDATE_RESPONSE(buffer);

	NetVersionResult* result = new NetVersionResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->netVersion = buffer["result"].asInt();

	return result;
}

NetListingResult* Api::NetListing()
{
	Json::Value buffer;
	wrapper->SendJson("net_listening", &buffer);

	VALIDATE_RESPONSE(buffer);

	NetListingResult* result = new NetListingResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->listing = buffer["result"].asBool();

	return result;
}

NetPeerCountResult* Api::NetPeerCount()
{
	Json::Value buffer;
	wrapper->SendJson("net_peerCount", &buffer);

	VALIDATE_RESPONSE(buffer);

	NetPeerCountResult* result = new NetPeerCountResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->peerCount = wrapper->HexToDec(buffer["result"].asString());

	return result;
}

ProtocolVersionResult* Api::ProtocolVersion()
{
	Json::Value buffer;
	wrapper->SendJson("eth_protocolVersion", &buffer);

	VALIDATE_RESPONSE(buffer);

	ProtocolVersionResult* result = new ProtocolVersionResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->protocolVersion = buffer["result"].asInt();

	return result;
}

SyncingResult* Api::Syncing()
{
	Json::Value buffer;
	wrapper->SendJson("eth_syncing", &buffer);

	VALIDATE_RESPONSE(buffer);

	SyncingResult* result = new SyncingResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();

	result->startingBlock = wrapper->HexToDec(buffer["result"]["startingBlock"].asString());
	result->currentBlock = wrapper->HexToDec(buffer["result"]["currentBlock"].asString());
	result->highestBlock = wrapper->HexToDec(buffer["result"]["highestBlock"].asString());

	return result;
}

CoinbaseResult* Api::Coinbase()
{
	Json::Value buffer;
	wrapper->SendJson("eth_coinbase", &buffer);

	VALIDATE_RESPONSE(buffer);

	CoinbaseResult* result = new CoinbaseResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->coinbaseAddress = buffer["result"].asString();

	return result;
}

MiningResult* Api::Mining()
{
	Json::Value buffer;
	wrapper->SendJson("eth_mining", &buffer);

	VALIDATE_RESPONSE(buffer);

	MiningResult* result = new MiningResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->mining = buffer["result"].asBool();

	return result;
}

HashrateResult* Api::Hashrate()
{
	Json::Value buffer;
	wrapper->SendJson("eth_hashrate", &buffer);

	VALIDATE_RESPONSE(buffer);

	HashrateResult* result = new HashrateResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->hashrate = wrapper->HexToDec(buffer["result"].asString());

	return result;
}

GasPriceResult* Api::GasPrice()
{
	Json::Value buffer;
	wrapper->SendJson("eth_gasPrice", &buffer);

	VALIDATE_RESPONSE(buffer);

	GasPriceResult* result = new GasPriceResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->gasPrice = wrapper->HexToDec(buffer["result"].asString());

	return result;
}

AccountsResult* Api::Accounts()
{
	Json::Value buffer;
	wrapper->SendJson("eth_accounts", &buffer);

	VALIDATE_RESPONSE(buffer);

	AccountsResult* result = new AccountsResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->accounts = buffer["result"];

	return result;
}

BlockNumberResult* Api::BlockNumber()
{
	Json::Value buffer;
	wrapper->SendJson("eth_blockNumber", &buffer);

	VALIDATE_RESPONSE(buffer);

	BlockNumberResult* result = new BlockNumberResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->blockNumber = wrapper->HexToDec(buffer["result"].asString());

	return result;
}

BalanceResult* Api::Balance(std::string& address, const std::string& tag)
{
	Json::Value params(Json::arrayValue);
	params.append(address);
	params.append(tag);

	Json::Value buffer;
	wrapper->SendJson("eth_getBalance", params, &buffer);

	VALIDATE_RESPONSE(buffer);

	BalanceResult* result = new BalanceResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();

	boost::multiprecision::uint256_t n(buffer["result"].asString());
	result->balance = n;

	return result;
}

StorageAtResult* Api::StorageAt(std::string& address, int pos, const std::string& tag)
{
	Json::Value params(Json::arrayValue);
	params.append(address);
	params.append(wrapper->ToHexString(pos));
	params.append(tag);

	Json::Value buffer;
	wrapper->SendJson("eth_getStorageAt", params, &buffer);

	VALIDATE_RESPONSE(buffer);

	StorageAtResult* result = new StorageAtResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->storageValue = buffer["result"].asString();

	return result;
}

TransactionCountResult* Api::TransactionCount(std::string& address, const std::string& tag)
{
	Json::Value params(Json::arrayValue);
	params.append(address);
	params.append(tag);

	Json::Value buffer;
	wrapper->SendJson("eth_getTransactionCount", params, &buffer);

	VALIDATE_RESPONSE(buffer);

	TransactionCountResult* result = new TransactionCountResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->transactionCount = wrapper->HexToDec(buffer["result"].asString());

	return result;
}

TransactionCountResult* Api::BlockTransactionCountByHash(std::string& blockHash)
{
	Json::Value params(Json::arrayValue);
	params.append(blockHash);

	Json::Value buffer;
	wrapper->SendJson("eth_getBlockTransactionCountByHash", &buffer);

	VALIDATE_RESPONSE(buffer);

	TransactionCountResult* result = new TransactionCountResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->transactionCount = wrapper->HexToDec(buffer["result"].asString());

	return result;
}

TransactionCountResult* Api::BlockTransactionCountByNumber(int blockNumber)
{
	Json::Value params(Json::arrayValue);
	params.append(wrapper->ToHexString(blockNumber));

	Json::Value buffer;
	wrapper->SendJson("eth_getBlockTransactionCountByNumber", &buffer);

	VALIDATE_RESPONSE(buffer);

	TransactionCountResult* result = new TransactionCountResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->transactionCount = wrapper->HexToDec(buffer["result"].asString());

	return result;
}

UncleCountResult* Api::UncleCountByBlockHash(std::string& blockHash)
{
	Json::Value params(Json::arrayValue);
	params.append(blockHash);

	Json::Value buffer;
	wrapper->SendJson("eth_getUncleCountByBlockHash", &buffer);

	VALIDATE_RESPONSE(buffer);

	UncleCountResult* result = new UncleCountResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->uncleCount = wrapper->HexToDec(buffer["result"].asString());

	return result;
}

UncleCountResult* Api::UncleCountByBlockNumber(int blockNumber)
{
	Json::Value params(Json::arrayValue);
	params.append(wrapper->ToHexString(blockNumber));

	Json::Value buffer;
	wrapper->SendJson("eth_getUncleCountByBlockNumber", &buffer);

	VALIDATE_RESPONSE(buffer);

	UncleCountResult* result = new UncleCountResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->uncleCount = wrapper->HexToDec(buffer["result"].asString());

	return result;
}

CodeResult* Api::Code(std::string& address, const std::string& tag)
{
	Json::Value params(Json::arrayValue);
	params.append(address);
	params.append(tag);

	Json::Value buffer;
	wrapper->SendJson("eth_getCode", &buffer);

	VALIDATE_RESPONSE(buffer);

	CodeResult* result = new CodeResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->code = buffer["result"].asString();

	return result;
}

RawTransactionResult* Api::RawTransaction(std::string& rawTx)
{
	Json::Value params(Json::arrayValue);
	params.append(rawTx);

	Json::Value buffer;
	wrapper->SendJson("eth_sendRawTransaction", &buffer);

	VALIDATE_RESPONSE(buffer);

	RawTransactionResult* result = new RawTransactionResult();
	result->jsonrpc = buffer["jsonrpc"].asString();
	result->id = buffer["id"].asInt();
	result->receipt = buffer["result"].asString();
}
#include "getter.hpp"
#include "InfInt.h"

Getter::Getter(Wrapper* wr)
{
	wrapper = wr;
}

NetVersionResult* Getter::NetVersion()
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

NetListingResult* Getter::NetListing()
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

NetPeerCountResult* Getter::NetPeerCount()
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

ProtocolVersionResult* Getter::ProtocolVersion()
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

SyncingResult* Getter::Syncing()
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

CoinbaseResult* Getter::Coinbase()
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

MiningResult* Getter::Mining()
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

HashrateResult* Getter::Hashrate()
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

GasPriceResult* Getter::GasPrice()
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

AccountsResult* Getter::Accounts()
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

BlockNumberResult* Getter::BlockNumber()
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

void Hex2Char(const char* szHex, unsigned char& rch)
{
	rch = 0;
	for (int i = 0; i < 2; i++)
	{
		if (*(szHex + i) >= '0' && *(szHex + i) <= '9')
			rch = (rch << 4) + (*(szHex + i) - '0');
		else if (*(szHex + i) >= 'A' && *(szHex + i) <= 'F')
			rch = (rch << 4) + (*(szHex + i) - 'A' + 10);
		else
			break;
	}
}

void HexStrToCharStr(const char* hexStr, unsigned char* decStr, int n)
{
	unsigned char d_ch;
	for (int i = 0; i < n; i++)
	{
		Hex2Char(hexStr + 2 * i, d_ch);
		decStr[i] = d_ch;
	}
}

BalanceResult* Getter::Balance(std::string address, std::string tag)
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
	result->balance = buffer["result"].asString();

	return result;
}

StorageAtResult* Getter::StorageAt(std::string address, int pos, std::string tag)
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

TransactionCountResult* Getter::TransactionCount(std::string address, std::string tag)
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

TransactionCountResult* Getter::BlockTransactionCountByHash(std::string blockHash)
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

TransactionCountResult* Getter::BlockTransactionCountByNumber(int blockNumber)
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

UncleCountResult* Getter::UncleCountByBlockHash(std::string blockHash)
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

UncleCountResult* Getter::UncleCountByBlockNumber(int blockNumber)
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

CodeResult* Getter::Code(std::string address, std::string tag)
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
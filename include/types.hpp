#ifndef TYPES_DOT_H
#define TYPES_DOT_H
#include "InfInt.hpp"
#include <iostream>

// ===============================
struct Default
{
	std::string jsonrpc;
	int id;
};

// ==============================
// Metas
struct Block
{
	int number;
	std::string hash;
	std::string parentHash;
	int nonce;
	std::string sha3Uncles;
	std::string logsBloom;
	std::string transactionsRoot;
	std::string stateRoot;
	std::string receiptsRoot;
	std::string miner;
	InfInt difficulty;
	InfInt totalDifficulty;
	std::string extraData;
	int size;
	InfInt gasLimit;
	InfInt gasUsed;
	InfInt timestamp;
	Json::Value transactions;
	Json::Value uncles;
};

struct Transaction
{
	std::string blockHash;
	int blockNumber;
	std::string from;
	InfInt gas;
	InfInt gasPrice;
	std::string hash;
	std::string input;
	int nonce;
	std::string to;
	int transactionIndex;
	InfInt value;
	int ecdsaRecoveryId;         // v
	std::string ecdsaSignatureR; // r
	std::string ecdsaSignatureS; // s
};

struct Receipt
{
	std::string transactionHash;
	int transactionIndex;
	std::string blockHash;
	std::string from;
	std::string to;
	InfInt cumulativeGasUsed;
	InfInt gasUsed;
	std::string contractAddress;
	Json::Value logs;
	std::string logsBloom;
	// std::string root (pre Byzantium)
	int status;
};

struct CompileInfo
{
	std::string source;
	std::string language;
	std::string languageVersion;
	std::string compilerVersion;
	Json::Value abiDefinition;
	Json::Value userDoc;
	Json::Value developerDoc;
};

// ==============================
// Results
struct NetVersionResult : Default
{
	int netVersion;
};

struct NetPeerCountResult : Default
{
	int peerCount;
};

struct NetListingResult : Default
{
	bool listing;
};

struct ProtocolVersionResult : Default
{
	int protocolVersion;
};

struct SyncingResult : Default
{
	int startingBlock;
	int currentBlock;
	int highestBlock;
};

struct CoinbaseResult : Default
{
	std::string coinbaseAddress;
};

struct MiningResult : Default
{
	bool mining;
};

struct HashrateResult : Default
{
	int hashrate;
};

struct GasPriceResult : Default
{
	InfInt gasPrice;
};

struct AccountsResult : Default
{
	Json::Value accounts; // String array
};

struct BlockNumberResult : Default
{
	int blockNumber;
};

struct BalanceResult : Default
{
	InfInt balance;
};

struct StorageAtResult : Default
{
	std::string storageValue;
};

struct TransactionCountResult : Default
{
	int transactionCount;
};

struct UncleCountResult : Default
{
	int uncleCount;
};

struct CodeResult : Default
{
	std::string code;
};

struct SignResult : Default
{
	std::string signature;
};

struct SendResult : Default
{
	std::string hash;
};

struct CallResult : Default
{
	std::string value;
};

struct EstimateGas : Default
{
	InfInt gasEstimate;
};

struct BlockResult : Default
{
	Block block;
};

struct TransactionResult : Default
{
	Transaction transaction;
};

struct ReceiptResult : Default
{
	Receipt receipt;
};

struct CompilersResult : Default
{
	Json::Value compilers;
};

struct CompileResult : Default
{
	std::string code;
	CompileInfo info;
};

struct CompileLLLResult : Default
{
	std::string compiledSourceCode;
};

struct CompileSerpentResult : CompileLLLResult
{
};

struct FilterResult : Default
{
	int filterId;
};

struct UninstallFilterResult : Default
{
	bool ok;
};

struct FilterChangesResult : Default
{
	Json::Value logObjects;
};

struct WorkResult : Default
{
	std::string blockHeader;
	std::string seedHash;
	std::string boundary;
};

struct SubmitWorkResult : Default
{
	bool valid;
};

struct SubmitHashrateResult : Default
{
	bool ok;
};

struct PutResult : Default
{
	bool ok;
};

struct GetResult : Default
{
	std::string data;
};

struct SSHVersionResult : Default
{
	std::string sshVersion;
};

struct SSHPostResult : Default
{
	bool ok;
};

struct SSHIdentityResult : Default
{
	bool ok;
};

struct SSHAddGroupResult : Default
{
	std::string groupAddress;
};

#endif
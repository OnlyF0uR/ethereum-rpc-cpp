#ifndef TYPES_DOT_H
#define TYPES_DOT_H
#include <iostream>

using hex_string = std::string;

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
	hex_string difficulty;
	hex_string totalDifficulty;
	std::string extraData;
	int size;
	hex_string gasLimit;
	hex_string gasUsed;
	hex_string timestamp;
	Json::Value transactions;
	Json::Value uncles;
};

struct Transaction
{
	std::string blockHash;
	int blockNumber;
	std::string from;
	hex_string gas;
	hex_string gasPrice;
	std::string hash;
	std::string input;
	int nonce;
	std::string to;
	int transactionIndex;
	hex_string value;
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
	hex_string cumulativeGasUsed;
	hex_string gasUsed;
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
	hex_string gasPrice;
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
	hex_string balance;
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
	hex_string gasEstimate;
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
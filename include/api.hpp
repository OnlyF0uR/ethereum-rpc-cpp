#ifndef API_DOT_H
#define API_DOT_H
#include "wrapper.hpp"
#include "jsoncpp/json/json.h"
#include "types.hpp"

class Wrapper;

class Api
{
public:
	Api(Wrapper* wr);

	NetVersionResult* NetVersion();
	NetListingResult* NetListing();
	NetPeerCountResult* NetPeerCount();

	ProtocolVersionResult* ProtocolVersion();
	SyncingResult*				Syncing();
	CoinbaseResult*				Coinbase();
	MiningResult*				Mining();
	HashrateResult*				Hashrate();
	GasPriceResult*				GasPrice();
	AccountsResult*				Accounts();
	BlockNumberResult*			BlockNumber();
	BalanceResult*				Balance(std::string& address, const std::string& tag);
	StorageAtResult*			StorageAt(std::string& address, int pos, const std::string& tag);
	TransactionCountResult*		TransactionCount(std::string& address, const std::string& tag);
	TransactionCountResult*		BlockTransactionCountByHash(std::string& blockHash);
	TransactionCountResult*		BlockTransactionCountByNumber(int blockNumber);
	UncleCountResult*			UncleCountByBlockHash(std::string& blockHash);
	UncleCountResult*			UncleCountByBlockNumber(int blockNumber);
	CodeResult*					Code(std::string& address, const std::string& tag);
	RawTransactionResult*		RawTransaction(std::string& rawTx);

private:
	Wrapper* wrapper;
};

#endif

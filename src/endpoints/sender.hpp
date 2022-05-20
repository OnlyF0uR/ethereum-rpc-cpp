#ifndef SENDER_DOT_H
#define SENDER_DOT_H
#include "wrapper.hpp"
#include "json/json.h"
#include "rlp/RLP.hpp"

class Wrapper;

class Sender
{
public:
	Sender(Wrapper* wr, std::string privateKey);
	~Sender();

	std::string CreateRawTransaction(
		std::string nonce,
		std::string gasPrice,
		std::string gasLimit,
		std::string to,
		std::string value,
		std::string data
	);
	std::string WalletAddress();
	std::string PublicKey();

	std::string HashMessage(std::string msg);
	std::string SignMessage(std::string msgHash);
	bool VerifyMessage(std::string publicKey, std::string msgHash, std::string signature);

private:
	Wrapper* wrapper;
	uint8_t* privateKey;

	// Some utilities
	uint8_t* CharArrayToByteArray(char* string);
	void SplitArray(uint8_t src[], uint8_t dest[], uint8_t from, uint8_t to);
	char* ByteArrayToCharArray(uint8_t* bytes, uint8_t len, char* buffer);
	uint8_t* GetPublicKey();
	uint8_t* GetAddress(uint8_t* publickey);
	std::string AssembleTransaction(TX tx);
};

#endif
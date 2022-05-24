#ifndef SENDER_DOT_H
#define SENDER_DOT_H
#include "wrapper.hpp"
#include "json/json.h"

class Wrapper;

struct Keypair
{
	std::string publicKey, privateKey;
};

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
	Keypair Sender::CreatePair();

private:
	Wrapper* wrapper;
	uint8_t* privateKey;

	// Some utilities
	uint8_t* InBytes(char* string);
	void GetAddress(uint8_t* publicKey, uint8_t* buffer);
};

#endif
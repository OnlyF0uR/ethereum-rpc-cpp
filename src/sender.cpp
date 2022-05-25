#include "sender.hpp"
#include "crypto/keccak256.h"
#include "crypto/uECC.h"
#include "rlp/tx.h"

constexpr unsigned int HASH_LENGTH = 32;
constexpr unsigned int SIGNATURE_LENGTH = 64;
constexpr unsigned int ADDRESS_LENGTH = 20;

Sender::Sender(Wrapper* wr, std::string privateKey) {
	this->wrapper = wr;
	this->privateKey = this->InBytes(const_cast<char*>(privateKey.c_str()));
}

Sender::~Sender()
{
	delete[] this->privateKey;
}

std::string Sender::CreateRawTransaction(
	std::string& nonce,
	std::string& gasPrice,
	std::string& gasLimit,
	std::string& to,
	std::string& value,
	std::string& data
)
{
	char* rawTx = assemble_transaction(
		nonce.c_str(),
		gasPrice.c_str(),
		gasLimit.c_str(),
		to.c_str(),
		value.c_str(),
		data.c_str(),
		1,
		this->privateKey
	);

	std::string s(rawTx);
	return "0x" + s;
}

std::string Sender::HashMessage(std::string& msg)
{
	SHA3_CTX context;
	uint8_t* buffer = new uint8_t[HASH_LENGTH];

	keccak_init(&context);
	keccak_update(&context, (const unsigned char*)(uint8_t*)msg.c_str(), (size_t)msg.size());
	keccak_final(&context, (unsigned char*)buffer);
	memset((char*)&context, 0, sizeof(SHA3_CTX));

	char* cbuf = new char[HASH_LENGTH * 2 + 1];
	byte_array_2_char_array(buffer, HASH_LENGTH, cbuf);

	std::string s(cbuf);

	delete[] buffer;
	delete[] cbuf;

	return s;
}

std::string Sender::SignMessage(std::string& msgHash)
{
	// Convert the hash
	uint8_t* hash = this->InBytes(const_cast<char*>(msgHash.c_str()));

	// Create a signature
	uint8_t* sig = new uint8_t[SIGNATURE_LENGTH];
	uECC_sign(this->privateKey, hash, HASH_LENGTH, sig, uECC_secp256k1());

	char* cbuf = new char[SIGNATURE_LENGTH * 2 + 1];
	byte_array_2_char_array(sig, SIGNATURE_LENGTH, cbuf);

	// Convert the result back to a std::string
	std::string s(cbuf);

	delete[] hash;
	delete[] sig;
	delete[] cbuf;

	return s;
}

bool Sender::VerifyMessage(std::string& publicKey, std::string& msgHash, std::string& signature)
{
	// Hash
	uint8_t* pubKey = new uint8_t[64];
	uECC_compute_public_key(this->privateKey, pubKey, uECC_secp256k1());

	uint8_t* hash = this->InBytes(const_cast<char*>(msgHash.c_str()));
	uint8_t* sig = this->InBytes(const_cast<char*>(signature.c_str()));

	int result = uECC_verify(pubKey, hash, HASH_LENGTH, sig, uECC_secp256k1());

	// Cleanup
	delete[] pubKey;
	delete[] hash;
	delete[] sig;

	return result;
}

std::string Sender::WalletAddress()
{
	// Public key
	uint8_t* publicKey = new uint8_t[64];
	uECC_compute_public_key(this->privateKey, publicKey, uECC_secp256k1());

	// Wallet address
	uint8_t* address = new uint8_t[20];
	this->GetAddress(publicKey, address);

	// Address char
	char* addrChar = new char[20 * 2 + 1];
	byte_array_2_char_array(address, ADDRESS_LENGTH, addrChar);

	std::string s(addrChar);

	// Cleanup
	delete[] publicKey;
	delete[] address;
	delete[] addrChar;

	return "0x" + s;
}

std::string Sender::PublicKey() {
	uint8_t* publicKey = new uint8_t[64];
	uECC_compute_public_key(this->privateKey, publicKey, uECC_secp256k1());

	char* cbuf = new char[64 * 2 + 1];
	byte_array_2_char_array(publicKey, 64, cbuf);

	std::string s(cbuf);

	// Cleanup
	delete[] publicKey;
	delete[] cbuf;
	return s;
}

Keypair Sender::CreatePair()
{
	uint8_t* pub = new uint8_t[64];
	uint8_t* priv = new uint8_t[32];

	uECC_make_key(pub, priv, uECC_secp256k1());

	char* pubBuf = new char[64 * 2 + 1];
	byte_array_2_char_array(pub, 32, pubBuf);

	char* privBuf = new char[32 * 2 + 1];
	byte_array_2_char_array(priv, 32, privBuf);

	std::string publicKey(pubBuf);
	std::string privateKey(privBuf);

	return Keypair{
		publicKey, privateKey
	};
}

void Sender::GetAddress(uint8_t* publicKey, uint8_t* buffer) {
	uint8_t* pubHash = new uint8_t[64];
	SHA3_CTX context;

	keccak_init(&context);
	keccak_update(&context, (const unsigned char*)publicKey, (size_t)64);
	keccak_final(&context, (unsigned char*)pubHash);
	memset((char*)&context, 0, sizeof(SHA3_CTX));

	memcpy(buffer, &pubHash[12], 20);

	// Cleanup
	delete[] pubHash;
}

uint8_t* Sender::InBytes(char* string) {
	if (string == NULL)
		return NULL;

	size_t slength = strlen(string);
	if ((slength % 2) != 0)
		return NULL;

	size_t dlength = slength / 2;

	uint8_t* data = new uint8_t[dlength];
	memset(data, 0, dlength);

	size_t index = 0;
	while (index < slength) {
		char c = string[index];
		int value = 0;
		if (c >= '0' && c <= '9')
			value = (c - '0');
		else if (c >= 'A' && c <= 'F')
			value = (10 + (c - 'A'));
		else if (c >= 'a' && c <= 'f')
			value = (10 + (c - 'a'));
		else {
			delete[] data;
			return NULL;
		}

		data[(index / 2)] += value << (((index + 1) % 2) * 4);

		index++;
	}

	return data;
}
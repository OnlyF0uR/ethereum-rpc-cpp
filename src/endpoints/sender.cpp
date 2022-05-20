#include "sender.hpp"
#include "rlp/RLP.hpp"
#include "crypto/keccak256.hpp"
#include "crypto/uECC.hpp"

#define HASH_LENGTH 32
#define SIGNATURE_LENGTH 64

Sender::Sender(Wrapper* wr, std::string privateKey) {
	this->wrapper = wr;
	this->privateKey = this->CharArrayToByteArray(const_cast<char*>(privateKey.c_str()));
}

//Sender::Sender(Wrapper* wr, char* privateKey) {
//	this->wrapper = wr;
//	this->privateKey = this->CharArrayToByteArray(privateKey);
//}

Sender::~Sender()
{
	delete this->privateKey;
}

std::string Sender::CreateRawTransaction(
	std::string nonce,
	std::string gasPrice,
	std::string gasLimit,
	std::string to,
	std::string value,
	std::string data
)
{
	TX tx;
	tx.nonce = nonce;
	tx.gasPrice = gasPrice;
	tx.gasLimit = gasLimit;
	tx.to = to;
	tx.value = value;
	tx.data = data;

	// nonce    gasPrice           gasLimit   to                                             value                data
	// 0x00     0x09184e72a000     0x5208     0x0000000000000000000000000000000000000000     0x11c37937e08000     0x
	//std::cout << "Transaction: " << tx.nonce << " " << tx.gasPrice << " " << tx.gasLimit << " " << tx.to << " " << tx.value << " " << tx.data << "\n";

	return this->AssembleTransaction(tx);

}

std::string Sender::AssembleTransaction(TX tx)
{
	// Predefine some variables
	RLP rlp;
	SHA3_CTX context;

	// First layer of encoding
	std::string enc = rlp.encode(tx, true);
	//printf("Raw TX encode: %s\n", rlp.bytesToHex(enc).c_str());

	// Hash the actual transaction
	uint8_t* hashval = new uint8_t[HASH_LENGTH];
	keccak_init(&context);
	keccak_update(&context, (const unsigned char*)(uint8_t*)enc.c_str(), (size_t)enc.size());
	keccak_final(&context, (unsigned char*)hashval);
	memset((char*)&context, 0, sizeof(SHA3_CTX));
	printf("Hash: %s\n", this->ByteArrayToCharArray(hashval, HASH_LENGTH));

	// Create the signature for the transaction
	uint8_t* signature = new uint8_t[SIGNATURE_LENGTH];
	uECC_sign(this->privateKey, hashval, HASH_LENGTH, signature, uECC_secp256k1());
	printf("Signature: %s\n", this->ByteArrayToCharArray(signature, SIGNATURE_LENGTH));

	// Obtain the r and s values for the transaction
	uint8_t* r = new uint8_t[32];
	uint8_t* s = new uint8_t[32];
	this->SplitArray(signature, r, 0, 32);
	this->SplitArray(signature, s, 32, 64);

	// Re-set the r, s and v variables for the transaction
	tx.r = std::string("0x") + this->ByteArrayToCharArray(r, 32);
	tx.s = std::string("0x") + this->ByteArrayToCharArray(s, 32);
	tx.v = "0x1b"; // 27
	//printf("R: %s\n", tx.r.c_str());
	//printf("S: %s\n", tx.s.c_str());

	// Get the public key
	uint8_t* pubKey = this->GetPublicKey();

	int result = uECC_verify(pubKey, hashval, HASH_LENGTH, signature, uECC_secp256k1());
	printf("Sig match: %s", result ? "true" : "false");

	// Lastly encode the transaction once more
	std::string encoded = rlp.bytesToHex(rlp.encode(tx, false));
	//printf("\nTX length: %ld\n\nTX: 0x%s\n", encoded.size(), encoded.c_str());

	return encoded;
}

std::string Sender::HashMessage(std::string msg)
{
	SHA3_CTX context;
	uint8_t* buffer = new uint8_t[HASH_LENGTH];

	keccak_init(&context);
	keccak_update(&context, (const unsigned char*)(uint8_t*)msg.c_str(), (size_t)msg.size());
	keccak_final(&context, (unsigned char*)buffer);
	memset((char*)&context, 0, sizeof(SHA3_CTX));

	std::string s(this->ByteArrayToCharArray(buffer, HASH_LENGTH));
	return s;
}

std::string Sender::SignMessage(std::string msgHash)
{
	// Convert the hash
	uint8_t* hash = this->CharArrayToByteArray(const_cast<char*>(msgHash.c_str()));

	// Create a signature
	uint8_t* signature = new uint8_t[SIGNATURE_LENGTH];
	uECC_sign(this->privateKey, hash, HASH_LENGTH, signature, uECC_secp256k1());

	// Convert the result back to a std::string
	std::string s(this->ByteArrayToCharArray(signature, SIGNATURE_LENGTH));
	return s;
}

bool Sender::VerifyMessage(std::string publicKey, std::string msgHash, std::string signature)
{
	// Hash
	uint8_t* pubKey = this->GetPublicKey();
	printf("Key: %s\n", this->ByteArrayToCharArray(pubKey, HASH_LENGTH));

	//uint8_t* pubKey = this->CharArrayToByteArray(const_cast<char*>(publicKey.c_str()));
	uint8_t* hash = this->CharArrayToByteArray(const_cast<char*>(msgHash.c_str()));
	uint8_t* sig = this->CharArrayToByteArray(const_cast<char*>(signature.c_str()));

	int result = uECC_verify(pubKey, hash, HASH_LENGTH, sig, uECC_secp256k1());
	return result;
}

std::string Sender::WalletAddress()
{
	std::string s(this->ByteArrayToCharArray(this->GetAddress(this->GetPublicKey()), 20));
	return "0x" + s;
}

std::string Sender::PublicKey() {
	uint8_t* publickey = new uint8_t[64];
	uECC_compute_public_key(this->privateKey, publickey, uECC_secp256k1());

	return this->ByteArrayToCharArray(this->GetPublicKey(), 64);
}

uint8_t* Sender::GetAddress(uint8_t* publickey) {

	uint8_t* address = new uint8_t[20];
	uint8_t* pubhash = new uint8_t[64];

	SHA3_CTX context;

	keccak_init(&context);
	keccak_update(&context, (const unsigned char*)publickey, (size_t)64);
	keccak_final(&context, (unsigned char*)pubhash);
	memset((char*)&context, 0, sizeof(SHA3_CTX));

	memcpy(address, &pubhash[12], 20);
	return address;
}

uint8_t* Sender::GetPublicKey() {
	uint8_t* publickey = new uint8_t[64];
	uECC_compute_public_key(this->privateKey, publickey, uECC_secp256k1());

	return publickey;
}

uint8_t* Sender::CharArrayToByteArray(char* string) {

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

void Sender::SplitArray(uint8_t src[], uint8_t dest[], uint8_t from, uint8_t to)
{
	int i = 0;
	for (int ctr = from; ctr < to; ctr++)
	{
		dest[i] = src[ctr];
		i++;
	}
}

char* Sender::ByteArrayToCharArray(uint8_t* bytes, uint8_t len) {

	char* ret = new char[len * 2 + 1];
	char hexval[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	for (int j = 0; j < len; j++) {
		ret[j * 2] = hexval[((bytes[j] >> 4) & 0xF)];
		ret[(j * 2) + 1] = hexval[(bytes[j]) & 0x0F];
	}
	ret[len * 2] = '\0';
	return ret;
}

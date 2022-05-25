#include "tx.h"
#include "../utils.h"
#include "../crypto/keccak256.h"
#include "../crypto/uECC.h"

int encode_a(EthereumSignTx* msg, EthereumSig* tx, uint64_t* rawTx) {
	EncodeEthereumSignTx new_msg;
	EncodeEthereumTxRequest new_tx;
	memset(&new_msg, 0, sizeof(new_msg));
	memset(&new_tx, 0, sizeof(new_tx));

	wallet_encode_element(msg->nonce.bytes, msg->nonce.size, new_msg.nonce.bytes, &(new_msg.nonce.size), false);
	wallet_encode_element(msg->gas_price.bytes, msg->gas_price.size, new_msg.gas_price.bytes, &(new_msg.gas_price.size), false);
	wallet_encode_element(msg->gas_limit.bytes, msg->gas_limit.size, new_msg.gas_limit.bytes, &(new_msg.gas_limit.size), false);
	wallet_encode_element(msg->to.bytes, msg->to.size, new_msg.to.bytes, &(new_msg.to.size), false);
	wallet_encode_element(msg->value.bytes, msg->value.size, new_msg.value.bytes, &(new_msg.value.size), false);
	wallet_encode_element(msg->data_initial_chunk.bytes, msg->data_initial_chunk.size, new_msg.data_initial_chunk.bytes, &(new_msg.data_initial_chunk.size), false);
	wallet_encode_int(tx->signature_v, &(new_tx.signature_v));

	int length = wallet_encode_list(&new_msg, &new_tx, rawTx);
	return length;
}

int encode_b(EthereumSignTx* msg, EthereumSig* tx, uint64_t* rawTx) {
	EncodeEthereumSignTx new_msg;
	EncodeEthereumTxRequest new_tx;
	memset(&new_msg, 0, sizeof(new_msg));
	memset(&new_tx, 0, sizeof(new_tx));

	wallet_encode_element(msg->nonce.bytes, msg->nonce.size, new_msg.nonce.bytes, &(new_msg.nonce.size), false);
	wallet_encode_element(msg->gas_price.bytes, msg->gas_price.size, new_msg.gas_price.bytes, &(new_msg.gas_price.size), false);
	wallet_encode_element(msg->gas_limit.bytes, msg->gas_limit.size, new_msg.gas_limit.bytes, &(new_msg.gas_limit.size), false);
	wallet_encode_element(msg->to.bytes, msg->to.size, new_msg.to.bytes, &(new_msg.to.size), false);
	wallet_encode_element(msg->value.bytes, msg->value.size, new_msg.value.bytes, &(new_msg.value.size), false);
	wallet_encode_element(msg->data_initial_chunk.bytes, msg->data_initial_chunk.size, new_msg.data_initial_chunk.bytes, &(new_msg.data_initial_chunk.size), false);
	wallet_encode_int(tx->signature_v, &(new_tx.signature_v));
	wallet_encode_element(tx->signature_r.bytes, tx->signature_r.size, new_tx.signature_r.bytes, &(new_tx.signature_r.size), true);
	wallet_encode_element(tx->signature_s.bytes, tx->signature_s.size, new_tx.signature_s.bytes, &(new_tx.signature_s.size), true);

	int length = wallet_encode_list(&new_msg, &new_tx, rawTx);
	return length;
}

char* assemble_transaction(
	const char* nonce,
	const char* gas_price,
	const char* gas_limit,
	const char* to,
	const char* value,
	const char* data,
	int chainId,
	uint8_t* privateKey
) {
	char rawTx[256];
	EthereumSignTx tx;
	EthereumSig signature;
	uint64_t raw_tx_bytes[24];

	// First layer of encoding
	tx.nonce.size = size_of_bytes(strlen(nonce));
	hex2byte_arr(nonce, strlen(nonce), tx.nonce.bytes, tx.nonce.size);
	tx.gas_price.size = size_of_bytes(strlen(gas_price));
	hex2byte_arr(gas_price, strlen(gas_price), tx.gas_price.bytes, tx.gas_price.size);
	tx.gas_limit.size = size_of_bytes(strlen(gas_limit));
	hex2byte_arr(gas_limit, strlen(gas_limit), tx.gas_limit.bytes, tx.gas_limit.size);
	tx.to.size = size_of_bytes(strlen(to));
	hex2byte_arr(to, strlen(to), tx.to.bytes, tx.to.size);
	tx.value.size = size_of_bytes(strlen(value));
	hex2byte_arr(value, strlen(value), tx.value.bytes, tx.value.size);
	tx.data_initial_chunk.size = size_of_bytes(strlen(data));
	hex2byte_arr(data, strlen(data), tx.data_initial_chunk.bytes, tx.data_initial_chunk.size);

	signature.signature_v = chainId;

	int length = encode_a(&tx, &signature, raw_tx_bytes);
	int8_to_char((uint8_t*)raw_tx_bytes, length, rawTx);
	printf("Before signing: %s\n", rawTx);

	// Signature stuff
	SHA3_CTX context;

	uint8_t* hashval[32];
	keccak_init(&context);
	keccak_update(&context, (const unsigned char*)(uint8_t*)rawTx, (size_t)strlen(rawTx));
	keccak_final(&context, (unsigned char*)hashval);
	memset((char*)&context, 0, sizeof(SHA3_CTX));

	uint8_t* sig[64];
	uECC_sign(privateKey, hashval, 32, sig, uECC_secp256k1());

	uint8_t* tmp_r[32];
	uint8_t* tmp_s[32];
	split_array(sig, tmp_r, 0, 32);
	split_array(sig, tmp_s, 32, 64);

	// Allocate memory for the char arrays
	char* r[32 * 2 + 1];
	char* s[32 * 2 + 1];
	// Write to the buffers
	byte_array_2_char_array(tmp_r, 32, r);
	byte_array_2_char_array(tmp_s, 32, s);

	uint8_t* publicKey[64];
	uECC_compute_public_key(privateKey, publicKey, uECC_secp256k1());

	int result = uECC_verify(publicKey, hashval, 32, sig, uECC_secp256k1());
	printf("Sig match: %s\n", result ? "true" : "false");

	signature.signature_v = (chainId << 1) + 35;

	signature.signature_r.size = size_of_bytes(strlen(r));
	hex2byte_arr(r, strlen(r), signature.signature_r.bytes, signature.signature_r.size);

	signature.signature_s.size = size_of_bytes(strlen(s));
	hex2byte_arr(s, strlen(s), signature.signature_s.bytes, signature.signature_s.size);

	int l = encode_b(&tx, &signature, raw_tx_bytes);
	int8_to_char((uint8_t*)raw_tx_bytes, l, rawTx);

	return rawTx;
}
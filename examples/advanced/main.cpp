#include <iostream>
#include "wrapper.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Please provided a private key.\n";
		return 0;
	}
	std::string privKey(argv[1]);

	Wrapper wr = Wrapper();
	Sender sender = Sender(&wr, privKey);

	// Hashing, signing and verifying a message
	std::string hash = sender.HashMessage("Hello world!");
	std::string sig = sender.SignMessage(hash);
	std::string pubKey = sender.PublicKey(); // Note, pubkey != wallet address

	bool result = sender.VerifyMessage(pubKey, hash, sig);
	if (result)
	{
		std::cout << "Match!\n";
	}
	else
	{
		std::cout << "No match!\n";
	}

	// Crafting a raw transaction
	std::string rawTx = sender.CreateRawTransaction(
		"0x00",                                            // nonce
		"0x09184e72a000",                                  // gasPrice
		"0x5208",                                          // gasLimit
		"0x0000000000000000000000000000000000000000",      // to
		"0x11c37937e08000",                                // value
		"0x"                                               // data
	);
	std::cout << "Raw transaction: " << rawTx << "\n";

	return 0;
}
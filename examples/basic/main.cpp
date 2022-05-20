#include <iostream>
#include "wrapper.hpp"

int main(int argc, char** argv)
{
	// Handle the arguments
	std::string uri = "http://localhost:8545";
	if (argc == 2)
	{
		uri = argv[1];
	}

	// Initialize the required classes
	Wrapper wr = Wrapper(uri);
	Getter getter = Getter(&wr);

	// Get the latest block number
	{
		BlockNumberResult* res = getter.BlockNumber();
		if (res == nullptr)
		{
			std::cout << "An error occurred.\n";
		}
		else
		{
			std::cout << "Current block number: " << res->blockNumber << "\n";
			delete res;
		}
	}

	// Get the transaction count of a given address
	{
		TransactionCountResult* res = getter.TransactionCount("0x0000000000000000000000000000000000000000", "latest");
		if (res == nullptr)
		{
			std::cout << "An error occurred.\n";
		}
		else
		{
			std::cout << "Transaction count: " << res->transactionCount << "\n";
			delete res;
		}
	}

	return 0;
}
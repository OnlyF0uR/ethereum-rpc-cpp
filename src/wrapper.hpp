#ifndef WRAPPER_DOT_H
#define WRAPPER_DOT_H

#include "endpoints/getter.hpp"
#include "endpoints/sender.hpp"
#include "json/json.h"
#include <string>

struct MemoryStruct
{
	char* memory;
	size_t size;
};

#ifndef VALIDATE_RESPONSE
#define VALIDATE_RESPONSE(BUFFER) \
    if (buffer.empty() || buffer["jsonrpc"].isNull() || buffer["id"].isNull() || buffer["result"].isNull()) return nullptr;
#endif

class Wrapper
{
public:
	Wrapper();
	Wrapper(std::string);
	Wrapper(std::string, std::string v);
	void SendJson(std::string method, Json::Value* buffer);
	void SendJson(std::string method, Json::Value body, Json::Value* buffer);

	std::string ToHexString(int i);
	int HexToDec(std::string hex);

private:
	std::string rpc = "http://localhost:8545";
	std::string rpc_v = "2.0";
	int req_id = 0;
};

#endif
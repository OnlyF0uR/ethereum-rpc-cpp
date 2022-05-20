#include <curl/curl.h>
#include <iostream>
#include <memory>
#include <string.h>
#include <sstream>
#include <iomanip>
#include "wrapper.hpp"

Wrapper::Wrapper()
{
}

Wrapper::Wrapper(std::string uri)
{
	rpc = uri;
}

Wrapper::Wrapper(std::string uri, std::string v)
{
	rpc = uri;
	rpc_v = v;
}

size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)userp;

	char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if (!ptr)
	{
		printf("Could not allocate memory to the uri variable.\n");
		fflush(stdout);
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

void Wrapper::SendJson(std::string method, Json::Value* buffer)
{
	CURL* curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl)
	{
		struct MemoryStruct chunk;
		chunk.memory = (char*)malloc(1);
		chunk.size = 0;

		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charsets: utf-8");

		Json::Value body;
		body["jsonrpc"] = rpc_v;
		body["method"] = method;
		body["params"] = Json::arrayValue;
		body["id"] = req_id;

		Json::FastWriter fastwriter;
		std::string message = fastwriter.write(body);

		curl_easy_setopt(curl, CURLOPT_URL, rpc.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message.c_str());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

		res = curl_easy_perform(curl);

		if (res == CURLE_OK)
		{
			JSONCPP_STRING err;
			Json::CharReaderBuilder builder;

			const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
			if (!reader->parse(chunk.memory, chunk.memory + chunk.size, buffer, &err))
			{
				std::cout << "eth-rpc: Failed to parse JSON response: " << err << std::endl;
			}
		}
		else
		{
			std::cout << "eth-rpc: Request failed." << std::endl;
		}

		if (chunk.memory != NULL)
		{
			free(chunk.memory);
		}

		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
	}
	else
	{
		std::cout << "eth-rpc: Failed to initialize CURL." << std::endl;
	}

	curl_global_cleanup();
}

void Wrapper::SendJson(std::string method, Json::Value params, Json::Value* buffer)
{
	CURL* curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl)
	{
		struct MemoryStruct chunk;
		chunk.memory = (char*)malloc(1);
		chunk.size = 0;

		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charsets: utf-8");

		Json::Value body;
		body["jsonrpc"] = rpc_v;
		body["method"] = method;
		body["params"] = params;
		body["id"] = req_id;

		Json::FastWriter fastwriter;
		std::string message = fastwriter.write(body);

		curl_easy_setopt(curl, CURLOPT_URL, rpc.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message.c_str());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

		res = curl_easy_perform(curl);

		if (res == CURLE_OK)
		{
			JSONCPP_STRING err;
			Json::CharReaderBuilder builder;

			const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
			if (!reader->parse(chunk.memory, chunk.memory + chunk.size, buffer, &err))
			{
				std::cout << "eth-rpc: Failed to parse JSON response: " << err << std::endl;
			}
		}
		else
		{
			std::cout << "eth-rpc: Request failed." << std::endl;
		}

		if (chunk.memory != NULL)
		{
			free(chunk.memory);
		}

		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
	}
	else
	{
		std::cout << "eth-rpc: Failed to initialize CURL." << std::endl;
	}

	curl_global_cleanup();
}

std::string Wrapper::ToHexString(int i)
{
	std::stringstream stream;
	stream << "0x"
		<< std::setfill('0') << std::setw(sizeof(i) * 2)
		<< std::hex << i;
	return stream.str();
}

int Wrapper::HexToDec(std::string hex)
{
	return std::stoul(hex, nullptr, 16);
}
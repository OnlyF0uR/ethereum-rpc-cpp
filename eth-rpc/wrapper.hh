#pragma once
#include <string>
#include <json/json.h>

struct MemoryStruct {
  char *memory;
  size_t size;
};

class Wrapper
{
public:
    Wrapper(std::string *url);
private:
    std::string *rpc;
    void SendJson(std::string url, Json::Value body, Json::Value *buffer);
    size_t Wrapper::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};
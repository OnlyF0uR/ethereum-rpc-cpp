#pragma once
#include "endpoints/getter.hh"
#include "endpoints/sender.hh"
#include <json/json.h>
#include <string>

struct MemoryStruct
{
    char *memory;
    size_t size;
};

class Wrapper
{
  public:
    Wrapper(char *uri);
    Getter Getter();
    Sender Sender();
    void SendJson(char *endpt, Json::Value *buffer);
    void SendJson(char *endpt, Json::Value body, Json::Value *buffer);

  private:
    char *rpc;
    size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};
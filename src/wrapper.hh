#ifndef WRAPPER_DOT_H
#define WRAPPER_DOT_H

#include "endpoints/getter.hh"
#include "endpoints/sender.hh"
#include "json/json.h"
#include <string>

struct MemoryStruct
{
    char *memory;
    size_t size;
};

class Wrapper
{
  public:
    Wrapper();
    Wrapper(std::string);
    Wrapper(std::string, std::string v);
    void SendJson(std::string method, Json::Value *buffer);
    void SendJson(std::string method, Json::Value body, Json::Value *buffer);

  private:
    std::string rpc = "http://localhost:8545";
    std::string rpc_v = "2.0";
    int req_id = 0;
};

#endif
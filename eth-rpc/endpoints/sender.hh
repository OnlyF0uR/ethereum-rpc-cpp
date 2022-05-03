#pragma once
#include "../wrapper.hh"

class Sender : public Wrapper
{
  public:
    Json::Value RawTransaction(std::string txData);
    // TODO: Call
};
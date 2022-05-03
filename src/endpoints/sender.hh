#ifndef SENDER_DOT_H
#define SENDER_DOT_H
#include "wrapper.hh"
#include "json/json.h"

class Wrapper;

class Sender
{
  public:
    Sender(Wrapper *wr);

    Json::Value RawTransaction(std::string txData);
    // TODO: Call

  private:
    Wrapper *wrapper;
};

#endif
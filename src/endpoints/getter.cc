#include "getter.hh"
#include <iostream>

Getter::Getter(Wrapper *wr) {
    wrapper = wr;
}

int Getter::BlockNumber()
{
    Json::Value buffer;
    wrapper->SendJson("eth_blockNumber", &buffer);

    if (buffer.empty()) {
        return -1;
    }
    
    return std::stoul(buffer["result"].asString(), nullptr, 16);;
}
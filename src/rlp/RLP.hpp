/*
  RLP.hpp - RLP library for RLP functions
*/
#ifndef RLP_DOT_H
#define RLP_DOT_H

#include <stdio.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <memory.h>

class TX
{
public:
	std::string nonce;
	std::string gasPrice;
	std::string gasLimit;
	std::string to;
	std::string value;
	std::string data;
	std::string v;
	std::string r;
	std::string s;
private:

};

class RLP
{
public:
	std::string encode(std::string);
	std::string encode(TX, bool);
	std::string encodeLength(int, int);
	std::string intToHex(int);
	std::string bytesToHex(std::string);
	std::string removeHexFormatting(std::string);
	std::string hexToRlpEncode(std::string);
	std::string hexToBytes(std::string);
	int char2int(char);
	void hex2bin(const char*, char*);
	void testPub();

private:

};

#endif
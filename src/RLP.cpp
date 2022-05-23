/*
  RLP.cpp - RLP library for RLP functions
*/
#include "RLP.hpp"
using namespace std;

string rlp::encode(string s)
{
	if (s.size() == 1 && (unsigned char)s[0] < 128)
		return s;
	else {
		return encodeLength(s.size(), 128) + s;
	}
}

string rlp::encode(TX tx, bool initial)
{
	string serialized = hexToRlpEncode(tx.nonce) +
		hexToRlpEncode(tx.gasPrice) +
		hexToRlpEncode(tx.gasLimit) +
		hexToRlpEncode(tx.to) +
		hexToRlpEncode(tx.value) +
		hexToRlpEncode(tx.data);

	if (!initial) {
		serialized += hexToRlpEncode(tx.v) +
			hexToRlpEncode(tx.r) +
			hexToRlpEncode(tx.s);
	}

	return encodeLength(serialized.length(), 192) + serialized;
}

string rlp::hexToBytes(string s) {
	char* inp = new char[s.length()];
	memcpy(inp, s.c_str(), s.length());

	char* dest = new char[sizeof(inp) / 2];
	hex2bin(inp, dest);

	string res(dest);

	delete[] inp;
	delete[] dest;

	return res;
}

string rlp::hexToRlpEncode(string s) {
	s = removeHexFormatting(s);
	return encode(hexToBytes(s));
}

string rlp::removeHexFormatting(string s) {
	if (s[0] == '0' && s[1] == 'x')
		return s.substr(2, s.length() - 2);
	return s;
}

string rlp::encodeLength(int len, int offset)
{
	string temp;
	if (len < 56) {
		temp = (char)(len + offset);
		return temp;
	}
	else {
		string hexLength = intToHex(len);
		int	lLength = hexLength.length() / 2;
		string fByte = intToHex(offset + 55 + lLength);
		return hexToBytes(fByte + hexLength);
	}
}

string rlp::intToHex(int n) {
	stringstream stream;
	stream << std::hex << n;
	string result(stream.str());
	if (result.size() % 2)
		result = "0x" + result;
	return result;
}

string rlp::bytesToHex(string input)
{
	static const char* const lut = "0123456789ABCDEF";
	size_t len = input.length();
	std::string output;
	output.reserve(2 * len);
	for (size_t i = 0; i < len; ++i)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}
	return output;
}

int rlp::char2int(char input)
{
	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;

	return 0;
}

void rlp::hex2bin(const char* src, char* target)
{
	while (*src && src[1])
	{
		*(target++) = char2int(*src) * 16 + char2int(src[1]);
		src += 2;
	}
}
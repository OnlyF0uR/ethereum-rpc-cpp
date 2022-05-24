/*
 * Copyright (c) 2016-2018 . All Rights Reserved.
 */

#include "utils.h"

int size_of_bytes(int str_len) {
	int out_len = (str_len & 1) ? (str_len + 1) / 2 : str_len / 2;
	return out_len;
}

uint8_t strtohex(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	return 255;
}

int hex2byte_arr(char* buf, int len, uint8_t* out, int outbuf_size) {
	int i = len - 1;
	int out_len = (len & 1) ? (len + 1) / 2 : len / 2;
	int j = out_len - 1;

	if (j > outbuf_size)
		return -1; /* Output buffer is smaller than need */

	while (i >= 0) {
		out[j] = strtohex(buf[i--]);
		if (i >= 0) {
			out[j--] |= strtohex(buf[i--]) << 4;
		}
	}

	return out_len;
}

void int8_to_char(uint8_t* buffer, int len, char* out) {
	const char hex[] = "0123456789abcdef";
	int max = 2 * len;
	int i = 0;
	int j = 0;
	while (j < len) {
		out[i++] = hex[(buffer[j] >> 4) & 0xF];
		out[i++] = hex[buffer[j] & 0xF];
		j++;
	}
	out[i] = '\0';
}

void split_array(uint8_t src[], uint8_t dest[], uint8_t from, uint8_t to)
{
	int i = 0;
	for (int ctr = from; ctr < to; ctr++)
	{
		dest[i] = src[ctr];
		i++;
	}
}

void byte_array_2_char_array(uint8_t* bytes, uint8_t len, char* buffer) {
	char hexval[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	for (int j = 0; j < len; j++) {
		buffer[j * 2] = hexval[((bytes[j] >> 4) & 0xF)];
		buffer[(j * 2) + 1] = hexval[(bytes[j]) & 0x0F];
	}
	buffer[len * 2] = '\0';
}
/*
 * Copyright (c) 2016-2018 . All Rights Reserved.
 */

#ifndef RLP_UTILS_H
#define RLP_UTILS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef uint32_t pb_size_t;
	typedef uint_least8_t pb_byte_t;

	int size_of_bytes(int str_len);
	uint8_t strtohex(char c);
	int hex2byte_arr(char* buf, int len, uint8_t* out, int outbuf_size);
	void int8_to_char(uint8_t* buffer, int len, char* out);
	void split_array(uint8_t src[], uint8_t dest[], uint8_t from, uint8_t to);
	void byte_array_2_char_array(uint8_t* bytes, uint8_t len, char* buffer);

#ifdef __cplusplus
}
#endif

#endif //RLP_UTİLS_H

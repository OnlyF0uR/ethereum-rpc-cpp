#ifndef TX_H
#define TX_H

#include "rlp.h"

#ifdef __cplusplus
extern "C" {
#endif
	char* assemble_transaction(
		const char* nonce,
		const char* gas_price,
		const char* gas_limit,
		const char* to,
		const char* value,
		const char* data,
		int chainId,
		uint8_t* privateKey
	);
#ifdef __cplusplus
}
#endif

#endif
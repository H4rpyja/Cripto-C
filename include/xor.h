#ifndef XOR_H
#define XOR_H

#include <stddef.h>
#include <stdint.h>


void xor_cipher(const uint8_t *in, size_t len,
                const uint8_t *key, size_t key_len,
                uint8_t *out);

#endif

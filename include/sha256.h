#ifndef SHA256_H
#define SHA256_H

#include <stddef.h>
#include <stdint.h>

/*
 * Calcula el hash SHA-256 (FIPS 180-4) de un mensaje.
 *
 *   data : mensaje (len bytes). Si len == 0 no se lee.
 *   len  : longitud en BYTES.
 *   out  : buffer de 32 bytes donde se escribe el resultado.
 */
void sha256(const uint8_t *data, size_t len, uint8_t out[32]);

#endif

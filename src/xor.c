#include "xor.h"

void xor_cipher(const uint8_t *in, size_t len,const uint8_t *key, size_t key_len,uint8_t *out){

    size_t i = 0;
    while(i < len){
        out[i] = len ? in[i] ^ key[i % key_len] : in[i];
        i++;
    }
    
}

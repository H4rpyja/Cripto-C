#include <stdio.h>
#include <string.h>
#include "xor.h"

static int fallos = 0;
#define CHECK(c) do { if (!(c)) { \
    printf("  FALLO: %s (línea %d)\n", #c, __LINE__); fallos++; } } while (0)

static void a_hex(const uint8_t *b, size_t n, char *out){
    for (size_t i = 0; i < n; i++) sprintf(out + 2 * i, "%02x", b[i]);
    out[2 * n] = '\0';
}

/* Vector de Cryptopals, Set 1, reto 5 */
static void test_vector_cryptopals(void){
    printf("test_vector_cryptopals\n");
    const char *txt =
        "Burning 'em, if you ain't quick and nimble\n"
        "I go crazy when I hear a cymbal";
    const char *esperado =
        "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a2622"
        "6324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b"
        "20283165286326302e27282f";
    uint8_t out[128];
    char hex[300];
    size_t n = strlen(txt);

    xor_cipher((const uint8_t *)txt, n, (const uint8_t *)"ICE", 3, out);
    a_hex(out, n, hex);
    CHECK(strcmp(hex, esperado) == 0);
}

static void test_ida_y_vuelta(void){
    printf("test_ida_y_vuelta\n");
    const char *msg = "Mensaje secreto";
    size_t n = strlen(msg);
    uint8_t cif[64], dec[64];

    xor_cipher((const uint8_t *)msg, n, (const uint8_t *)"clave", 5, cif);
    xor_cipher(cif, n, (const uint8_t *)"clave", 5, dec);
    CHECK(memcmp(dec, msg, n) == 0);
}

static void test_clave_de_un_byte(void){
    printf("test_clave_de_un_byte\n");
    const uint8_t in[3] = { 0x00, 0xFF, 0x0F };
    const uint8_t key[1] = { 0xFF };
    uint8_t out[3];

    xor_cipher(in, 3, key, 1, out);
    CHECK(out[0] == 0xFF && out[1] == 0x00 && out[2] == 0xF0);
}

int main(void){
    test_vector_cryptopals();
    test_ida_y_vuelta();
    test_clave_de_un_byte();

    if (fallos) { printf("\n%d fallo(s)\n", fallos); return 1; }
    printf("\nTodo OK\n");
    return 0;
}

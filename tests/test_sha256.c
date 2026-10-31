#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

static int fallos = 0;

static void a_hex(const uint8_t *b, size_t n, char *out){
    for (size_t i = 0; i < n; i++) sprintf(out + 2 * i, "%02x", b[i]);
    out[2 * n] = '\0';
}

static void probar(const char *nombre, const uint8_t *datos, size_t len,
                   const char *esperado){
    uint8_t digest[32] = {0};
    char hex[65];

    sha256(datos, len, digest);
    a_hex(digest, 32, hex);
    if (strcmp(hex, esperado) != 0) {
        printf("FALLO: %s (len = %zu)\n  obtenido: %s\n  esperado: %s\n",
               nombre, len, hex, esperado);
        fallos++;
    } else {
        printf("ok:    %s\n", nombre);
    }
}

/* n bytes 'a' en un buffer temporal */
static void probar_repetido(const char *nombre, size_t n, const char *esperado){
    uint8_t *buf = malloc(n > 0 ? n : 1);
    if (!buf) { printf("sin memoria\n"); exit(2); }
    memset(buf, 'a', n);
    probar(nombre, buf, n, esperado);
    free(buf);
}

int main(void){
    /* --- Vectores clásicos --- */
    probar("cadena vacia", (const uint8_t *)"", 0,
           "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    probar("abc", (const uint8_t *)"abc", 3,
           "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    probar("NIST 56 bytes", (const uint8_t *)"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 56,
           "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
    probar("zorro", (const uint8_t *)"The quick brown fox jumps over the lazy dog", 43,
           "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592");

    /* --- Casos límite del padding (el mensaje se rellena a múltiplos de 64
     *     bytes; en 55/56 y 119/120 el relleno cambia de 1 a 2 bloques) --- */
    probar_repetido("1 bytes 'a'", 1,
                    "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb");
    probar_repetido("55 bytes 'a'", 55,
                    "9f4390f8d30c2dd92ec9f095b65e2b9ae9b0a925a5258e241c9f1e910f734318");
    probar_repetido("56 bytes 'a'", 56,
                    "b35439a4ac6f0948b6d6f9e3c6af0f5f590ce20f1bde7090ef7970686ec6738a");
    probar_repetido("57 bytes 'a'", 57,
                    "f13b2d724659eb3bf47f2dd6af1accc87b81f09f59f2b75e5c0bed6589dfe8c6");
    probar_repetido("63 bytes 'a'", 63,
                    "7d3e74a05d7db15bce4ad9ec0658ea98e3f06eeecf16b4c6fff2da457ddc2f34");
    probar_repetido("64 bytes 'a'", 64,
                    "ffe054fe7ae0cb6dc65c3af9b61d5209f439851db43d0ba5997337df154668eb");
    probar_repetido("65 bytes 'a'", 65,
                    "635361c48bb9eab14198e76ea8ab7f1a41685d6ad62aa9146d301d4f17eb0ae0");
    probar_repetido("119 bytes 'a'", 119,
                    "31eba51c313a5c08226adf18d4a359cfdfd8d2e816b13f4af952f7ea6584dcfb");
    probar_repetido("120 bytes 'a'", 120,
                    "2f3d335432c70b580af0e8e1b3674a7c020d683aa5f73aaaedfdc55af904c21c");
    probar_repetido("121 bytes 'a'", 121,
                    "e9615320128cc7a3d6078e9af05603188e5ccbf0d07d8b735d3df5e8e0c1281f");
    probar_repetido("127 bytes 'a'", 127,
                    "c57e9278af78fa3cab38667bef4ce29d783787a2f731d4e12200270f0c32320a");
    probar_repetido("128 bytes 'a'", 128,
                    "6836cf13bac400e9105071cd6af47084dfacad4e5e302c94bfed24e013afb73e");
    probar_repetido("129 bytes 'a'", 129,
                    "c12cb024a2e5551cca0e08fce8f1c5e314555cc3fef6329ee994a3db752166ae");
    probar_repetido("1000 bytes 'a'", 1000,
                    "41edece42d63e8d9bf515a9ba6932e1c20cbc9f5a5d134645adb5db1b9737ea3");

    /* --- Un millón de 'a' (vector oficial del NIST) --- */
    probar_repetido("un millon de 'a'", 1000000,
                    "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0");

    if (fallos) { printf("\n%d fallo(s)\n", fallos); return 1; }
    printf("\nTodo OK\n");
    return 0;
}

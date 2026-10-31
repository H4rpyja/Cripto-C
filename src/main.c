/* Uso: ./xor_tool <archivo_entrada> <archivo_salida> <clave> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xor.h"

static uint8_t *leer_archivo(const char *ruta, size_t *len){
    FILE *f = fopen(ruta, "rb");
    if (!f) { perror(ruta); return NULL; }

    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (n < 0) { fclose(f); return NULL; }

    uint8_t *buf = malloc(n > 0 ? (size_t)n : 1);
    if (!buf) { fclose(f); return NULL; }

    if (fread(buf, 1, (size_t)n, f) != (size_t)n) {
        perror("fread"); free(buf); fclose(f); return NULL;
    }
    fclose(f);
    *len = (size_t)n;
    return buf;
}

int main(int argc, char **argv){
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <entrada> <salida> <clave>\n", argv[0]);
        return 1;
    }

    size_t len = 0;
    uint8_t *in = leer_archivo(argv[1], &len);
    if (!in) return 1;

    uint8_t *out = malloc(len > 0 ? len : 1);
    if (!out) { free(in); return 1; }

    xor_cipher(in, len, (const uint8_t *)argv[3], strlen(argv[3]), out);

    FILE *f = fopen(argv[2], "wb");
    if (!f) { perror(argv[2]); free(in); free(out); return 1; }
    fwrite(out, 1, len, f);
    fclose(f);

    free(in);
    free(out);
    return 0;
}

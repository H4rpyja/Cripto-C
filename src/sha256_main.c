/* Uso: ./sha256_tool <archivo>
 * Imprime "<hash>  <archivo>", igual que el comando sha256sum, para que
 * puedas comparar tu resultado con el de una implementación de referencia. */
#include <stdio.h>
#include <stdlib.h>
#include "sha256.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror(argv[1]); return 1; }

    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (n < 0) { fclose(f); return 1; }

    uint8_t *buf = malloc(n > 0 ? (size_t)n : 1);
    if (!buf) { fclose(f); return 1; }
    if (fread(buf, 1, (size_t)n, f) != (size_t)n) {
        perror("fread"); free(buf); fclose(f); return 1;
    }
    fclose(f);

    uint8_t digest[32];
    sha256(buf, (size_t)n, digest);
    free(buf);

    for (int i = 0; i < 32; i++) printf("%02x", digest[i]);
    printf("  %s\n", argv[1]);
    return 0;
}

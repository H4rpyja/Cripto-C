#include <stdio.h>
#include <string.h>
#include "caesar.h"

static int fallos = 0;
#define CHECK_STR(obtenido, esperado) do { \
    if (strcmp((obtenido), (esperado)) != 0) { \
        printf("  FALLO (línea %d): obtenido \"%s\", esperado \"%s\"\n", \
               __LINE__, (obtenido), (esperado)); fallos++; } } while (0)

static void test_basico(void){
    printf("test_basico\n");
    char out[64] = "";
    caesar_encrypt("HELLO", 3, out);
    CHECK_STR(out, "KHOOR");
    caesar_encrypt("Hello, World!", 3, out);
    CHECK_STR(out, "Khoor, Zruog!");
}

static void test_vuelta_al_alfabeto(void){
    printf("test_vuelta_al_alfabeto\n");
    char out[64] = "";
    caesar_encrypt("xyz XYZ", 3, out);
    CHECK_STR(out, "abc ABC");
}

static void test_desplazamientos_raros(void){
    printf("test_desplazamientos_raros\n");
    char out[64] = "";
    caesar_encrypt("abc", 0, out);   CHECK_STR(out, "abc");
    caesar_encrypt("abc", 26, out);  CHECK_STR(out, "abc");
    caesar_encrypt("abc", 29, out);  CHECK_STR(out, "def");
    caesar_encrypt("abc", -3, out);  CHECK_STR(out, "xyz");
    caesar_encrypt("abc", -29, out); CHECK_STR(out, "xyz");
}

static void test_no_letras(void){
    printf("test_no_letras\n");
    char out[64] = "";
    caesar_encrypt("a1 b2-c3!", 1, out);
    CHECK_STR(out, "b1 c2-d3!");
    /* La "ñ" ocupa 2 bytes en UTF-8; ninguno es una letra A-Z/a-z. */
    caesar_encrypt("Año", 1, out);
    CHECK_STR(out, "Bñp"); /* A->B, ñ intacta, o->p */
}

static void test_cadena_vacia(void){
    printf("test_cadena_vacia\n");
    char out[8] = "xxxxxxx";
    caesar_encrypt("", 5, out);
    CHECK_STR(out, "");
}

static void test_ida_y_vuelta(void){
    printf("test_ida_y_vuelta\n");
    const char *msg = "Mensaje Secreto, número 42!";
    char cif[64] = "", dec[64] = "";
    for (int s = -30; s <= 30; s++) {
        caesar_encrypt(msg, s, cif);
        caesar_decrypt(cif, s, dec);
        if (strcmp(dec, msg) != 0) {
            printf("  FALLO: la ida y vuelta falla con shift = %d\n", s);
            fallos++;
            break;
        }
    }
    caesar_decrypt("Khoor, Zruog!", 3, dec);
    CHECK_STR(dec, "Hello, World!");
}

int main(void){
    test_basico();
    test_vuelta_al_alfabeto();
    test_desplazamientos_raros();
    test_no_letras();
    test_cadena_vacia();
    test_ida_y_vuelta();

    if (fallos) { printf("\n%d fallo(s)\n", fallos); return 1; }
    printf("\nTodo OK\n");
    return 0;
}

#include <stdio.h>
#include <string.h>
#include "vigenere.h"

static int fallos = 0;
#define CHECK(c) do { if (!(c)) { \
    printf("  FALLO: %s (línea %d)\n", #c, __LINE__); fallos++; } } while (0)
#define CHECK_STR(obtenido, esperado) do { \
    if (strcmp((obtenido), (esperado)) != 0) { \
        printf("  FALLO (línea %d): obtenido \"%s\", esperado \"%s\"\n", \
               __LINE__, (obtenido), (esperado)); fallos++; } } while (0)

static void test_clasico(void){
    printf("test_clasico\n");
    char out[64] = "";
    /* Ejemplo clásico de Wikipedia */
    CHECK(vigenere_encrypt("ATTACKATDAWN", "LEMON", out) == 0);
    CHECK_STR(out, "LXFOPVEFRNHR");
    CHECK(vigenere_decrypt("LXFOPVEFRNHR", "LEMON", out) == 0);
    CHECK_STR(out, "ATTACKATDAWN");
}

static void test_mayusculas_y_signos(void){
    printf("test_mayusculas_y_signos\n");
    char out[64] = "";
    /* Los espacios y signos no consumen letras de la clave */
    CHECK(vigenere_encrypt("Attack at dawn!", "LEMON", out) == 0);
    CHECK_STR(out, "Lxfopv ef rnhr!");
}

static void test_clave_en_minusculas(void){
    printf("test_clave_en_minusculas\n");
    char a[64] = "", b[64] = "";
    CHECK(vigenere_encrypt("Attack at dawn!", "lemon", a) == 0);
    CHECK(vigenere_encrypt("Attack at dawn!", "LeMoN", b) == 0);
    CHECK_STR(a, "Lxfopv ef rnhr!");
    CHECK_STR(b, "Lxfopv ef rnhr!");
}

static void test_clave_a_es_identidad(void){
    printf("test_clave_a_es_identidad\n");
    char out[64] = "";
    CHECK(vigenere_encrypt("Hola, Mundo", "A", out) == 0);
    CHECK_STR(out, "Hola, Mundo");
}

static void test_clave_invalida(void){
    printf("test_clave_invalida\n");
    char out[64] = "";
    CHECK(vigenere_encrypt("hola", "", out) == -1);
    CHECK(vigenere_encrypt("hola", "abc1", out) == -1);
    CHECK(vigenere_decrypt("hola", "a b", out) == -1);
}

static void test_ida_y_vuelta(void){
    printf("test_ida_y_vuelta\n");
    const char *msg = "Mensaje Secreto, número 42!";
    const char *claves[] = { "a", "clave", "ZEBRA", "UnaClaveMuyLargaParaProbar" };
    char cif[64] = "", dec[64] = "";
    for (size_t i = 0; i < sizeof claves / sizeof claves[0]; i++) {
        CHECK(vigenere_encrypt(msg, claves[i], cif) == 0);
        CHECK(vigenere_decrypt(cif, claves[i], dec) == 0);
        CHECK_STR(dec, msg);
    }
}

int main(void){
    test_clasico();
    test_mayusculas_y_signos();
    test_clave_en_minusculas();
    test_clave_a_es_identidad();
    test_clave_invalida();
    test_ida_y_vuelta();

    if (fallos) { printf("\n%d fallo(s)\n", fallos); return 1; }
    printf("\nTodo OK\n");
    return 0;
}

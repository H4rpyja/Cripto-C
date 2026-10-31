#ifndef VIGENERE_H
#define VIGENERE_H

/*
 * Cifrado Vigenère sobre letras ASCII.
 *
 *  - key solo puede contener letras (A-Z, a-z) y no puede estar vacía;
 *    mayúsculas y minúsculas en la clave son equivalentes ('A' = 0 ... 'Z' = 25).
 *  - Solo se cifran las letras del mensaje, conservando mayúsculas/minúsculas.
 *    Los demás caracteres pasan sin cambios y NO consumen letras de la clave
 *    (la clave avanza únicamente cuando se cifra una letra).
 *  - out debe tener al menos strlen(in) + 1 bytes.
 *
 * Devuelve 0 si todo va bien y -1 si la clave no es válida.
 */
int vigenere_encrypt(const char *in, const char *key, char *out);
int vigenere_decrypt(const char *in, const char *key, char *out);

#endif

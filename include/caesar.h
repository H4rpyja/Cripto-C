#ifndef CAESAR_H
#define CAESAR_H

/*
 * Cifrado César sobre letras ASCII.
 *
 *  - Solo se desplazan las letras A-Z y a-z; mayúsculas y minúsculas se
 *    conservan. Cualquier otro byte (espacios, dígitos, signos, bytes de
 *    UTF-8 como la "ñ") pasa sin cambios.
 *  - shift puede ser negativo o mayor que 26 (-29 y 23 son equivalentes).
 *  - in es una cadena terminada en '\0'.
 *  - out debe tener al menos strlen(in) + 1 bytes; se escribe el '\0' final.
 */
void caesar_encrypt(const char *in, int shift, char *out);
void caesar_decrypt(const char *in, int shift, char *out);

#endif

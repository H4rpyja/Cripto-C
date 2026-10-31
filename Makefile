CC      = gcc
CFLAGS  = -Wall -Wextra -g -fsanitize=address,undefined -Iinclude

all: xor_tool sha256_tool

xor_tool: src/main.c src/xor.c include/xor.h
	$(CC) $(CFLAGS) src/main.c src/xor.c -o $@

sha256_tool: src/sha256_main.c src/sha256.c include/sha256.h
	$(CC) $(CFLAGS) src/sha256_main.c src/sha256.c -o $@

test_xor: tests/test_xor.c src/xor.c include/xor.h
	$(CC) $(CFLAGS) tests/test_xor.c src/xor.c -o $@

test_caesar: tests/test_caesar.c src/caesar.c include/caesar.h
	$(CC) $(CFLAGS) tests/test_caesar.c src/caesar.c -o $@

test_vigenere: tests/test_vigenere.c src/vigenere.c include/vigenere.h
	$(CC) $(CFLAGS) tests/test_vigenere.c src/vigenere.c -o $@

test_sha256: tests/test_sha256.c src/sha256.c include/sha256.h
	$(CC) $(CFLAGS) tests/test_sha256.c src/sha256.c -o $@


# Un objetivo por algoritmo: make test-xor, test-caesar, test-vigenere, test-sha256
test-xor: test_xor
	./test_xor

test-caesar: test_caesar
	./test_caesar

test-vigenere: test_vigenere
	./test_vigenere

test-sha256: test_sha256
	./test_sha256

# Ejecuta todos los tests aunque alguno falle, y falla si alguno falló
test: test_xor test_caesar test_vigenere test_sha256
	fail=0; for t in test_xor test_caesar test_vigenere test_sha256; do ./$$t || fail=1; done; exit $$fail

clean:
	rm -f xor_tool sha256_tool test_xor test_caesar test_vigenere test_sha256

.PHONY: all test test-xor test-caesar test-vigenere test-sha256 clean

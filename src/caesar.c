#include "caesar.h"

void caesar_encrypt(const char *in, int shift, char *out){

    int i = 0;
    while(in[i] != '\0'){
        if( in[i] >= 'A' && in[i] <= 'Z'){
            out[i] = 'A'+ ((((in[i] - 'A' + shift)%26)+26)%26);
        }else if(in[i] >= 'a' && in[i] <= 'z'){
            out[i] = 'a' + ((((in[i] - 'a' + shift)%26)+26)%26);
        }else{
            out[i] = in[i];
        }
        i++;
    }
    out[i] = '\0';
}

void caesar_decrypt(const char *in, int shift, char *out){
    caesar_encrypt(in,-shift,out);
}

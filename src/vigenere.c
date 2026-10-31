#include "vigenere.h"
#include <string.h>
static int valor_letra(char c){
    if(c>='a'&& c<='z'){
        return c - 'a';
    }else{
        return c - 'A';
    }
}

int vigenere_encrypt(const char *in, const char *key, char *out){

    
    int i = 0;
    int keylen = strlen(key);
    if(keylen == 0 ){
        return -1;
    }
    for(i=0;i<keylen;i++){
        if(!((key[i]>='a' && key[i]<='z') || (key[i]>= 'A' && key[i]<= 'Z'))){
            return -1;
        }
    }
    i=0;
    int j = 0;
    while(in[i]!='\0'){
        if(in[i]>='a' && in[i]<='z'){
            out[i] = 'a'+(((in[i] - 'a') + valor_letra(key[j%keylen]))%26);
            j++;
        }else if(in[i]>='A' && in[i]<='Z'){
            out[i] = 'A'+(((in[i] - 'A') + valor_letra(key[j%keylen]))%26);
            j++;
        }else{
            out[i]=in[i];
        }
        i++;
    }
    out[i]='\0';
    return 0;
        
}

int vigenere_decrypt(const char *in, const char *key, char *out){
    int i = 0;
    int keylen = strlen(key);
    if(keylen == 0 ){
        return -1;
    }
    for(i=0;i<keylen;i++){
        if(!((key[i]>='a' && key[i]<='z') || (key[i]>= 'A' && key[i]<= 'Z'))){
            return -1;
        }
    }
    i=0;
    int j = 0;
    while(in[i]!='\0'){
        if(in[i]>='a' && in[i]<='z'){
            out[i] = 'a'+(((((in[i] - 'a') - valor_letra(key[j%keylen]))%26)+26)%26);
            j++;
        }else if(in[i]>='A' && in[i]<='Z'){
            out[i] = 'A'+(((((in[i] - 'A') - valor_letra(key[j%keylen]))%26)+26)%26);
            j++;
        }else{
            out[i]=in[i];
        }
        i++;
    }
    out[i]='\0';
    return 0;
}

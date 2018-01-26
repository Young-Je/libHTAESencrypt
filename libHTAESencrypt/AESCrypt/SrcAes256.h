#include <stdlib.h> // pulls in declaration of malloc, free
#include <string.h> // pulls in declaration for strlen.
#ifndef uint8_t
#define uint8_t unsigned char
#endif
#ifdef __cplusplus
extern "C" { 
#endif
  typedef struct {
    uint8_t key[32]; 
    uint8_t enckey[32]; 
    uint8_t deckey[32];
  } aes256_context; 
  void aes256_init(aes256_context *, uint8_t * );
  void aes256_done(aes256_context *);
  void aes256_encrypt_ecb(aes256_context *, uint8_t * );
  void aes256_decrypt_ecb(aes256_context *, uint8_t * );
  int Do_Aes256(unsigned char* Src, unsigned char* Key, unsigned char* Dest, unsigned char flag);
#ifdef __cplusplus
}
#endif

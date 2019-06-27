#pragma once
#define AES_ROUNDKEYLEN 44
#define AES_KEYLEN 16


typedef unsigned char uint8_t;
typedef unsigned int uint32_t;


#define ltob(X) { \
   X = ((X & 0xFF000000) >> 24) ^ ((X & 0x00FF0000) >> 8) ^ ((X & 0x0000FF00) << 8) ^ ((X & 0x000000FF) << 24); \
}

typedef struct
{
	int nr;
	uint32_t rk[60];
} AES_RK;

#define SUBWORD(X) ((uint32_t)s[(X & 0xFF000000) >> 24] << 24) ^ ((uint32_t)s[(X & 0x00FF0000) >> 16] << 16) ^ ((uint32_t)s[(X & 0x0000FF00) >> 8] << 8) ^ ((uint32_t)s[(X & 0x000000FF)])
#define ROTWORD(X) ((X & 0xFF000000) >> 24) ^ ((X & 0x00FFFFFF) << 8)
#define AES_BXOR(X, Y) X[0] ^= *Y++; X[1] ^= *Y++; X[2] ^= *Y++; X[3] ^= *Y++;
#define AES_BCOPY(X, Y) X[0] = Y[0]; X[1] = Y[1]; X[2] = Y[2]; X[3] = Y[3];

int aes_keyschedule(uint8_t* key, AES_RK* aes_rk, int keyLen, int encType);
int aes_setkey_enc(const uint8_t* key, AES_RK* aes_rk);
int aes_setkey_dec(const uint8_t* key, AES_RK* aes_rk);
int aes_enc_block(uint32_t data[4], const AES_RK* aes_rk);
int aes_dec_block(uint32_t data[4], const AES_RK* aes_rk);

/*#######################################################################################*/

//8,16,24
#define downbyte(x, y) ((x) >> ((y) << 3)) & 0x000000FFU
#define upbyte(x, y) ((x) << ((y) << 3))

void Key_Schedule(uint32_t key[4], uint32_t AES_KEY[44]);
void AES_Encrypt(uint32_t* Encrypt_text, uint32_t* AES_KEY);
void AES_Decrypt(uint32_t* Decrypt_text, uint32_t* AES_KEY);
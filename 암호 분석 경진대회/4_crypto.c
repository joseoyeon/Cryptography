/*---------------2019 암호경진대회---------------*/
/*---------4번 문제 : 압축함수 충돌쌍 찾기---------*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "AES_Hash.h"

void lookuptable_make();

/*Round*/
void Round(uint32_t rk, uint32_t* X)
{
	uint32_t plainText[4]; // tmp array

	plainText[0] = (t0[downbyte(rk ^ X[0], 3)] ^ t1[downbyte(rk ^ X[0], 2)] ^ t2[downbyte(rk ^ X[0], 1)] ^ t3[downbyte(rk ^ X[0], 0)]) ^ X[1];
	plainText[1] = X[2] ;
	plainText[2] = X[3] ;
	plainText[3] = X[0] ;
 printf("%08x %08x %08x %08x \n", (plainText[0]),(plainText[1]),(plainText[2]),(plainText[3]));
	memcpy(X, plainText, 16);
}

/*Round_*/
void Round_(uint32_t rk, uint32_t* X,uint32_t* X_)
{
	X_[0] = X[0] ;
	X_[1] = (t0[downbyte(rk ^ X[0], 3)] ^ t1[downbyte(rk ^ X[0], 2)] ^ t2[downbyte(rk ^ X[0], 1)] ^ t3[downbyte(rk ^ X[0], 0)]) ^ X[1];
	X_[2] = X[2] ;
	X_[3] = X[3] ;
    
//  printf("X_ : %08x %08x %08x %08x \n", (X_[0]),(X_[1]),(X_[2]),(X_[3]));
}

int main()
{ 
	uint32_t X[4] = {0, };
	uint32_t X_[4] = {0, };
    uint32_t K[4] = {0, };
    uint32_t H[4] = {0, };
	// uint32_t m[32] = {0x00010203, 0x04050607,0x08090a0b,0x0c0d0e0f, 0x0a1a2a3a, 0x4a5a6a7a, 0x8a9aaaba, 0xcadaeafa}; //32bit 씩 8개
    uint32_t m1[32] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}; // %256 tmp key 상쇄
    uint32_t m2[32] = { 0x02040204, 0x00000000, 0x00000000, 0x00000000, 0x02040204, 0x00000000, 0x00000000, 0x00000000}; // %256 tmp key 상쇄

 	uint32_t rk;
    unsigned long long j,i; 
// 	lookuptable_make();

//    printf("static const uint32_t t0[256] = {");
//    for(uint32_t i=0; i<0x100; i++){
//       if(i%16 == 0) printf("\n");
//       printf("0x%08x, ", t0[i]);
//    }
//    printf("};\n");   
 

 //lookup
//    printf("static const uint32_t tmp[256] = {");
//    for(uint32_t i=0; i<=0x100; i++){
//       if(i%16 == 0) printf("\n");
//       printf("0x%08x, ", (upbyte(i,3) | upbyte(i+1,2) | upbyte(i+2,1) | upbyte(i+3,0)));
//    }
//    printf("};\n");

// FILE*fp=fopen("text.txt", "at+");

    for (uint32_t p=2; p<10; p++)
    {
		// m[0]=p;	
        memcpy(X, m1, 16);
        memcpy(K, m1+4, 16);
        printf(" m1 : %08x %08x %08x %08x %08x %08x %08x %08x\n", m1[0], m1[1], m1[2], m1[3], m1[4], m1[5], m1[6], m1[7]);
        // printf(" X : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	    // printf(" K : %08x %08x %08x %08x\n", K[0], K[1], K[2], K[3]); 

        for (i = 0; i <p-2; i++)
        {
            rk = K[0];
            // printf("rk + X, now key: ");
            Round(rk, X);
            printf("tmp + K, next key: ");
            Round(tmp[i%265],K);
            // printf("\n\n");
        }
		
        rk = K[0];
        Round_(rk, X,X_);

        printf("%08X, ", p);
        printf("%08x %08x %08x %08x \n\n\n", (X_[0] ^ m1[0] ^ m1[4]),( X_[1] ^ m1[1] ^ m1[5]),(X_[2] ^ m1[2] ^ m1[6]),(X_[3] ^ m1[3] ^ m1[7]));
        // fprintf(fp, "%08X, %08x %08x %08x %08x \n", j, X[0] ^ m[0] ^ m[4], X[1] ^ m[1] ^ m[5],X[2] ^ m[2] ^ m[6],X[3] ^ m[3] ^ m[7]);
        //}
        // fclose (fp);
    }

   for (uint32_t p=2; p<10; p++)
    {
		// m[0]=p;	
        memcpy(X, m2, 16);
        memcpy(K, m2+4, 16);
        printf(" m2 : %08x %08x %08x %08x %08x %08x %08x %08x\n", m2[0], m2[1], m2[2], m2[3], m2[4], m2[5], m2[6], m2[7]);
        // printf(" X : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	    // printf(" K : %08x %08x %08x %08x\n", K[0], K[1], K[2], K[3]); 

        for (i = 0; i < p-2; i++)
        {
            rk = K[0];
            // printf("rk + X, now key: ");
            Round(rk, X);
            printf("tmp + K, next key: ");
            Round(tmp[i%265],K);
            // printf("\n\n");
			
			// printf("round %d, %08x %08x %08x %08x %08x %08x %08x %08x\n", i,  m2[0], m2[1], m2[2], m2[3], m2[4], m2[5], m2[6], m2[7]);
        }
        rk = K[0];
        Round_(rk, X,X_);

        printf("%08X, ", p);
        printf("%08x %08x %08x %08x \n\n\n", (X_[0] ^ m2[0] ^ m2[4]),( X_[1] ^ m2[1] ^ m2[5]),(X_[2] ^ m2[2] ^ m2[6]),(X_[3] ^ m2[3] ^ m2[7]));
        // fprintf(fp, "%08X, %08x %08x %08x %08x \n", j, X[0] ^ m[0] ^ m[4], X[1] ^ m[1] ^ m[5],X[2] ^ m[2] ^ m[6],X[3] ^ m[3] ^ m[7]);
        //}
        // fclose (fp);
    }

	system("pause");
	return 0;
}
// void lookuptable_make()
// {
// 	uint8_t MC_Lookup_2[256];  //2
// 	uint8_t MC_Lookup_3[256];  //2+1
// 	uint8_t MC_Lookup_09[256]; //8+1
// 	uint8_t MC_Lookup_0b[256]; // 8+2+1
// 	uint8_t MC_Lookup_0d[256]; //8+4+1
// 	uint8_t MC_Lookup_0e[256]; // 8+4+2

// 	uint32_t i, j;
// 	uint8_t src;
// 	uint8_t tmp[4];

// 	/*----mc lookup table----*/
// 	for (j = 0; j < 0x100; j++)
// 	{
// 		src = j;
// 		tmp[0] = src;
// 		for (i = 1; i < 4; i++)
// 		{
// 			src = (src * 2) ^ (src & 0x80 ? 0x1b : 0);
// 			tmp[i] = src;
// 		}
// 		MC_Lookup_2[j] = tmp[1];                    //2
// 		MC_Lookup_3[j] = tmp[1] ^ tmp[0];           //2+1
// 		MC_Lookup_09[j] = tmp[3] ^ tmp[0];          //8+1
// 		MC_Lookup_0b[j] = tmp[3] ^ tmp[1] ^ tmp[0]; // 8+2+1
// 		MC_Lookup_0d[j] = tmp[3] ^ tmp[2] ^ tmp[0]; //8+4+1
// 		MC_Lookup_0e[j] = tmp[3] ^ tmp[2] ^ tmp[1]; // 8+4+2
// 	}
//  /*------- t0 table -----*/
//    for (unsigned int i = 0; i < 0x100; i++)
//    {
//       t0[i] = (MC_Lookup_2[sbox[i]] << 24) ^ (sbox[i] << 16) ^ (sbox[i] << 8) ^ MC_Lookup_3[sbox[i]];
//       t1[i] = (MC_Lookup_3[sbox[i]] << 24) ^ (MC_Lookup_2[sbox[i]] << 16) ^ (sbox[i] << 8) ^ sbox[i];
//       t2[i] = (sbox[i] << 24) ^ (MC_Lookup_3[sbox[i]] << 16) ^ (MC_Lookup_2[sbox[i]] << 8) ^ sbox[i];
//       t3[i] = (sbox[i] << 24) ^ (sbox[i] << 16) ^ (MC_Lookup_3[sbox[i]] << 8) ^ MC_Lookup_2[sbox[i]];
//       //   if(i%16==0) printf("\n");
//       //     printf("%08x ", t0[i]);
//    }
//    /*------- inv_t0 table ------*/
//    for (unsigned int i = 0; i < 0x100; i++)
//    {
//       inv_t0[i] = (MC_Lookup_0e[Inv_s[i]] << 24) ^ (MC_Lookup_09[Inv_s[i]] << 16) ^ (MC_Lookup_0d[Inv_s[i]] << 8) ^ MC_Lookup_0b[Inv_s[i]];
//       inv_t1[i] = (MC_Lookup_0b[Inv_s[i]] << 24) ^ (MC_Lookup_0e[Inv_s[i]] << 16) ^ (MC_Lookup_09[Inv_s[i]] << 8) ^ MC_Lookup_0d[Inv_s[i]];
//       inv_t2[i] = (MC_Lookup_0d[Inv_s[i]] << 24) ^ (MC_Lookup_0b[Inv_s[i]] << 16) ^ (MC_Lookup_0e[Inv_s[i]] << 8) ^ MC_Lookup_09[Inv_s[i]];
//       inv_t3[i] = (MC_Lookup_09[Inv_s[i]] << 24) ^ (MC_Lookup_0d[Inv_s[i]] << 16) ^ (MC_Lookup_0b[Inv_s[i]] << 8) ^ MC_Lookup_0e[Inv_s[i]];
//    }
// 	/*------- Table0_key_dec table ------*/
// 	for (i = 0; i < 0x100; i++)
// 	{
// 		Table0_key_dec[i] = (MC_Lookup_0e[i] << 24) ^ (MC_Lookup_09[i] << 16) ^ (MC_Lookup_0d[i] << 8) ^ MC_Lookup_0b[i];
// 		Table1_key_dec[i] = (MC_Lookup_0b[i] << 24) ^ (MC_Lookup_0e[i] << 16) ^ (MC_Lookup_09[i] << 8) ^ MC_Lookup_0d[i];
// 		Table2_key_dec[i] = (MC_Lookup_0d[i] << 24) ^ (MC_Lookup_0b[i] << 16) ^ (MC_Lookup_0e[i] << 8) ^ MC_Lookup_09[i];
// 		Table3_key_dec[i] = (MC_Lookup_09[i] << 24) ^ (MC_Lookup_0d[i] << 16) ^ (MC_Lookup_0b[i] << 8) ^ MC_Lookup_0e[i];
// 	}
// 	return;
// }
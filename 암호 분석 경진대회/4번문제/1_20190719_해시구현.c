/*---------------2019 암호경진대회---------------*/
/*---------4번 문제 : 압축함수 충돌쌍 찾기---------*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "1_AES_Hash.h"


/*Round*/
void Round(uint32_t rk, uint32_t* X)
{
	uint32_t plainText[4]; // tmp array

	plainText[0] = (t0[downbyte(rk ^ X[0], 3)] ^ t1[downbyte(rk ^ X[0], 2)] ^ t2[downbyte(rk ^ X[0], 1)] ^ t3[downbyte(rk ^ X[0], 0)]) ^ X[1];
	plainText[1] = X[2] ;
	plainText[2] = X[3] ;
	plainText[3] = X[0] ;
//  printf("%08x %08x %08x %08x \n", (plainText[0]),(plainText[1]),(plainText[2]),(plainText[3]));
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
	uint32_t m[32] = {0x00010203, 0x04050607,0x08090a0b,0x0c0d0e0f, 0x0a1a2a3a, 0x4a5a6a7a, 0x8a9aaaba, 0xcadaeafa}; //32bit 씩 8개
 	uint32_t rk;
    unsigned long long j,i, p =10; 


    for (p=2; p<=10; p++)
    {
		// m[0]=p;	
        memcpy(X, m, 16);
        memcpy(K, m+4, 16);
        printf(" m : %08x %08x %08x %08x %08x %08x %08x %08x\n", m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7]);
        // printf(" X : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	    // printf(" K : %08x %08x %08x %08x\n", K[0], K[1], K[2], K[3]); 

        for (i = 0; i <=p-2; i++)
        {
            rk = K[0];
            // printf("rk + X, now key: ");
            Round(rk, X);
            // printf("tmp + K, next key: ");
            Round(tmp[i%265],K);
            // printf("\n\n");
        }
		
        rk = K[0];
        Round_(rk, X,X_);

        printf("%08X, ", p);
        printf("%08x %08x %08x %08x \n\n\n", (X_[0] ^ m[0] ^ m[4]),( X_[1] ^ m[1] ^ m[5]),(X_[2] ^ m[2] ^ m[6]),(X_[3] ^ m[3] ^ m[7]));

    }

	system("pause");
	return 0;
}
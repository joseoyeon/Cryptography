/*---------------2019 암호경진대회---------------*/
/*---------4번 문제 : 압축함수 충돌쌍 찾기---------*/
/*---------해당 코드는 j =10  ---------*/
/*---------해당 코드는 32bit 키에 대한 충돌 쌍을 찾는 코드 입니다.---------*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "4.h"

int main()
{ 
    uint32_t K[4] = { 0x00000000 , 0x4a5a6a7a , 0x8a9aaaba , 0xcadaeafa }; // 이거에 앞에 32비트 대한 충돌 쌍을 찾는 게 목표!!
    uint32_t K_[4] = { 0x00000000 , 0x4a5a6a7a , 0x8a9aaaba , 0xcadaeafa }; // 이거에 앞에 32비트 대한 충돌 쌍을 찾는 게 목표!!

    // uint32_t m[32] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}; // %256 tmp key 상쇄
    uint32_t j=10, i; 

    for(uint32_t p=0x0a1a2a3a ; p<0x0a1a2a40; p++)
    {   
        K[0] = p;
        K[1] = 0x4a5a6a7a;  K[2] = 0x8a9aaaba;  K[3] = 0xcadaeafa; 
        printf("K[0] : %08x\n", K[0]);

        for (i = 0; i <= j-2; i++)
        {
    K_[0] = (t0[downbyte(tmp[(i%256)] ^ K[0], 3)] ^ t1[downbyte(tmp[(i%256)] ^ K[0], 2)] ^ t2[downbyte(tmp[(i%256)] ^ K[0], 1)] ^ t3[downbyte(tmp[(i%256)] ^ K[0], 0)]) ^ K[1];
	K_[1] = K[2] ;
	K_[2] = K[3] ;
	K_[3] = K[0] ;
	memcpy(K, K_, 16);
    printf("%08x\n", K[0]);    
        }
        printf("\n");
   }
	system("pause");
	return 0;
}

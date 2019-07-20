/*---------------2019 암호경진대회---------------*/
/*---------4번 문제 : 압축함수 충돌쌍 찾기---------*/
/*--------- 맨 처음 F함수 하나를 통과할 때 변화를 보는 코드---------*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "1_AES_Hash.h"

int main()
{ 
    uint32_t K[8] = { 0x00000000 , 0x00000000 , 0x00000000 , 0x00000000}; 
    uint32_t X[4] = { 0x00000000 , 0x00000000 , 0x00000000 , 0x00000000}; 

    uint32_t m[8] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}; // %256 tmp key 상쇄
    uint32_t H;
    uint32_t j=10, i=0x00000001; 

    for(uint32_t p = 1; p<33; p++)
    {   j = i << p;
        printf("H[0](X[0]) : %08x\n", j);
 // plainText[0] = (t0[downbyte(rk ^ X[0], 3)] ^ t1[downbyte(rk ^ X[0], 2)] ^ t2[downbyte(rk ^ X[0], 1)] ^ t3[downbyte(rk ^ X[0], 0)]) ^ X[1];
    H =  (t0[downbyte(K[0] ^ j, 3)] ^ t1[downbyte(K[0] ^ j, 2)] ^ t2[downbyte(K[0] ^ j, 1)] ^ t3[downbyte(K[0] ^ j, 0)]) ^ X[1];
    
    printf("%08X\n", H);    
    printf("\n");
   }
   printf("the end\n");
	system("pause");
	return 0;
}

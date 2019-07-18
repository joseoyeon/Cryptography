/*---------------2019 암호경진대회---------------*/
/*---------4번 문제 : 압축함수 충돌쌍 찾기---------*/
/*--------- F함수 하나에 대한 충돌쌍을 찾는 문제 입니다. ---------*/
/*---------해당 코드는 32bit 키에 대한 충돌 쌍을 찾는 코드 입니다.---------*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "AES_Hash.h"

int main()
{ 
    uint32_t K[8] = { 0x00000000 , 0x00000000 , 0x00000000 , 0x00000000}; // 이거에 앞에 32비트 대한 충돌 쌍을 찾는 게 목표!!
    uint32_t X[4] = { 0x00000000 , 0x00000000 , 0x00000000 , 0x00000000}; // 이거에 앞에 32비트 대한 충돌 쌍을 찾는 게 목표!!

    uint32_t m[8] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}; // %256 tmp key 상쇄
    uint32_t H;
    uint32_t j=10, i=0x01020102; 
// p=0 이면 1번째 들어간다 .
    FILE*fp=fopen("HASH_32bit_F.xlsx", "at+");

    for(uint32_t p = 1; p<33; p++)
    {   j = i << p;
        printf("H[0](X[0]) : %08x\n", j);
 // plainText[0] = (t0[downbyte(rk ^ X[0], 3)] ^ t1[downbyte(rk ^ X[0], 2)] ^ t2[downbyte(rk ^ X[0], 1)] ^ t3[downbyte(rk ^ X[0], 0)]) ^ X[1];
    H =  (t0[downbyte(K[0] ^ j, 3)] ^ t1[downbyte(K[0] ^ j, 2)] ^ t2[downbyte(K[0] ^ j, 1)] ^ t3[downbyte(K[0] ^ j, 0)]) ^ X[1];
    
    fprintf(fp, "%08X\n", H);
    printf("%08X\n", H);    
    printf("\n");
   }
   fclose (fp);
   printf("the end\n");
	system("pause");
	return 0;
}

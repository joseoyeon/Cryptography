#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

  unsigned long long KEY;
  unsigned C , D;

  void print_binary(const unsigned long long t) { //size 는 원래 없어ok 수정하다 보니 생긴 변수 
   int i,b = 0;
   unsigned long long tmp =1LL;
 
   for (i=63; i>=0; i--,b++) {
		printf("%d",(t) & ((tmp << i) )? 1:0); 
		
		if(b%4 == 3){printf(" ");}
		if(b%32== 31){printf("\n");};
	}
	printf("\n\n");
}

void print_hex(unsigned long long t)
{
  int i=0;
  for(i = 15; i>=0; i--)
  {
    printf("%x", ((t >> (i*4))&0x000000F));
  }
  printf("\n\n");
}
void print_char(unsigned long long t)
{
  int i=0;
  for(i = 7; i>=0; i--)
  {
    printf("%c", ((t >> (i*8))&0x000000FF));
  }
  printf("\n\n\n");
}
unsigned long long PC1(unsigned long long source)
{
  char i;
  unsigned long long tmp = (1LL<<55), res = 0LL;
  static char perm[] = {57,49,41,33,25,17, 
  9,1,58,50,42,34,26,18,
  10, 2,59,51,43,35,27,
  19,11, 3,60,52,44,36,
  63,55,47,39,31,23,15,
  7,62,54,46,38,30,22,
  14, 6,61,53,45,37,29,
  21,13, 5,28,20,12, 4};
                         
  for(i = 0; i < 56; i++, tmp = tmp >> 1LL)
    if (source & (1LL << (64-perm[i]))) res |= tmp;
  return res;
}

unsigned long long PC2()
{
  char i;
  unsigned long long tmp = (1LL<<47), res = 0LL;
  static char perm[] = {14,17,11,24, 1, 5,
  3,28,15, 6,21,10,
  23,19,12, 4,26, 8,
  16, 7,27,20,13, 2,
41,52,31,37,47,55,
30,40,51,45,33,48,
44,49,39,56,34,53,
46,42,50,36,29,32};

  for(i = 0; i < 48; i++, tmp = tmp >> 1LL) 
  	if (KEY & (1LL << (56-perm[i]))) res |= tmp; //전치 
    /*
	printf("PC2 후\n");
   print_hex(res);
   */
  return res;
}
 
unsigned long long IP(unsigned long long source)
{
  char i;
  unsigned long long tmp = (1LL<<63), res = 0LL;
  
  static char perm[] = {58, 50, 42, 34, 26 ,18 ,10, 2,
60, 52, 44, 36, 28, 20, 12, 4,
62, 54, 46, 38, 30, 22, 14, 6,
64, 56, 48, 40, 32, 24, 16, 8,
57, 49, 41, 33, 25, 17,  9, 1,
59, 51, 43, 35, 27, 19, 11, 3,
61, 53, 45, 37, 29, 21, 13, 5,
 63, 55, 47, 39, 31, 23, 15, 7};

  for(i = 0; i < 64; i++, tmp = tmp >> 1LL) 
  	if (source & (1LL << (64-perm[i]))) res |= tmp; //전 치 
  return res;
}

unsigned long long FP(unsigned long long source)
{
  char i;
   unsigned long long tmp = (1LL<<63), res = 0LL;
  static char perm[] =  {40, 8, 48, 16, 56, 24, 64, 32,

                                                       39, 7, 47, 15, 55, 23, 63, 31,

                                                       38, 6, 46, 14, 54, 22, 62, 30,

                                                       37, 5, 45, 13, 53, 21, 61, 29,

                                                       36, 4, 44, 12, 52, 20, 60, 28,

                                                       35, 3, 43, 11, 51, 19, 59, 27,

                                                       34, 2, 42, 10, 50, 18, 58, 26,

                                                       33, 1, 41,  9, 49, 17, 57, 25};

    for(i = 0; i < 64; i++, tmp = tmp >> 1LL) 
		if (source & (1LL << (64-perm[i]))) res |= tmp; //전 치 
  return res;
}

unsigned long long EX(unsigned source)
{
  char i;
  unsigned long long tmp = (1LL<<47), res = 0LL;
  static char perm[] = {32, 1, 2, 3, 4, 5,

                                      4, 5, 6, 7, 8, 9,

                                      8, 9,10,11,12,13,

                                     12,13,14,15,16,17,

                                      16,17,18,19,20,21,

                                     20,21,22,23,24,25,

                                     24,25,26,27,28,29,

                                     28,29,30,31,32, 1};

  for(i = 0; i < 48; i++, tmp = tmp >> 1LL) 
  	if (source & (1 << (32-perm[i]))) res |= tmp;
  return res;
}

unsigned P(unsigned source)
{
  char i;
  unsigned tmp = (1<<31), res = 0;
  static char perm[] = {16, 7,20,21,

                                     29,12,28,17,

                                      1,15,23,26,

                                      5,18,31,10,

                                      2, 8,24,14,

                                     32,27, 3, 9,

                                     19,13,30, 6,

                                     22,11, 4,25};


  for(i = 0; i < 32; i++, tmp = tmp >> 1) 
  	if (source & (1 << (32-perm[i]))) res |= tmp;
  
  /*
  printf("평문 P\n");
print_binary((unsigned long long)res, 4);
  */
  return res;
}

unsigned S(unsigned long long source){ //32bit out 
  static char perm[8][64] = { { 14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
                                 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
                                 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
                                15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13 },
                              { 15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
                                 3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
                                 0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
                                13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9 },
                              { 10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
                                13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
                                13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
                                 1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12 },
                              {  7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
                                13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
                                10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
                                 3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14 },
                              {  2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
                                14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
                                 4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
                                11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3 },
                              { 12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
                                10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8,
                                 9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
                                 4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13 },
                              {  4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
                                13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6,
                                 1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
                                 6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12 },
                              { 13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
                                 1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
                                 7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
                                 2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11 } };

  int i;
  unsigned int z=0; //저장 
  unsigned res=0;
  /*
   printf("평문 S- source \n");
   print_binary(source, 8);
*/
  for(i = 0, res = 0; i < 8; i++)
  {
    z = ((source >> (((7-i)* 6))) & 0x3F);
	(res |= (perm[i][((z&0x20)|((z<<4)&0x10)|(z>>1)&0x0F)]));
    (i!=7)? res <<=4 : 0;
 } 
  /*
   printf("평문 S\n");
print_binary((unsigned long long)res, 4);
 */
  return res; 
}

unsigned rotation(unsigned source, char c, char f)
{
  static char rotation_sheet[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

  c = rotation_sheet[c];
  
  if (f) while(c-- > 0) source = (source >> 1) | ((source & 1) << 27); 
  else   while(c-- > 0) source = ((source << 1) & 0x0FFFFFFF) | (source >> 27); // 0, 암호화 
  return source;
}

unsigned long long EN(unsigned long long source)
{
  int i = -1;
  unsigned Ln, L, R;

  source = IP(source);
  /* 
   printf("평문 IP \n");
   print_binary(&source, 8);
    */
    
  L = (unsigned)((source) >> 32);
  R = ((unsigned)source);
    
   /*  
    printf("평문 L\n");
    print_binary((unsigned long long)L);//4
    printf("평문  R \n");
    print_binary((unsigned long long)R);//4
    
   unsigned long long tmp= EX(L);
	printf("L EX \n");
    print_binary((unsigned long long*)&tmp, 6);
  */
  
   C = (KEY>>28); 
   D = (KEY&0x0FFFFFFF);
   
/*라운드 함수 실행*/  
  while(++i < 16)
  {
    Ln = R;

  C = rotation(C, i, 0);
  D = rotation(D, i, 0);
  KEY = ((unsigned long long)C <<28| D);
  
   /* printf("KEY C \n");
    print_binary((unsigned long long*)&C, 4);
    printf("KEY D \n");
    print_binary((unsigned long long*)&D, 4);
  
    printf("KEY K \n");
    print_binary(&K, 8);
  
   unsigned long long PC= PC2();
    printf("KEY PC2 \n");
     puts_hex(&PC);
    print_binary(&PC, 8);
    */
   
    R = (L^P(S(EX(R)^PC2())));
    L = Ln;
    
   /* unsigned long long tmp = (((unsigned long long)L << 32) | R);
  printf("[L + R] ");
  print_binary(&tmp, 8);
  
  /*printf("[L] ");
  print_binary((unsigned long long *)&L, 4);
  
  /*
   unsigned long long tmp = FP(((unsigned long long)R<< 32) | L);
  printf("[FP] ");
  print_binary(&tmp, 8);
  
  unsigned long long tmp = (((unsigned long long)L << 32) | R);
  printf("[L + R] ");
  print_hex(tmp);
  print_binary(tmp);*/
  }
 
  return FP(((unsigned long long)R<< 32) | L);
}

unsigned long long DE(unsigned long long source)
{
  char i = 16;
  unsigned Ln, L, R;

  source = IP(source);
  
  L = (unsigned)((source) >> 32);
  R = ((unsigned)source);
  
   C = (KEY>>28); 
   D = (KEY&0x0FFFFFFF);
   
  while(--i >= 0)
  {
    Ln = R; 
    
	R = L^P(S(EX(R)^PC2()));
    L = Ln;
   /* 
    printf("KEY C \n");
    print_binary((unsigned long long*)&C, 4);
    printf("KEY D \n");
    print_binary((unsigned long long*)&D, 4);
    printf("KEY K \n");
    print_binary(&K, 8);
    */
    C = rotation(C, i, 1);
    D = rotation(D, i, 1);
    KEY = ((unsigned long long)C <<28| D);
//printf("%d \n",16-i);	
/*	printf("rotation 후\n");
   print_hex(KEY);
  */}
  return FP(((unsigned long long)R << 32) | L);
}

void encryption(unsigned long long src, unsigned long long*encrypted_str, unsigned long long key)
{
  KEY = PC1(key);
  
  /*
  printf("KEY PC1 \n");
  print_binary(KEY,8);
  */
  
  *(encrypted_str) = EN(src);
  return;
}

void decryption(unsigned long long src, unsigned long long*decrypted_str, unsigned long long key)
{
  KEY = PC1(key);
 /*
  printf("PC1 후\n");
   print_hex(KEY);
 */
  *(decrypted_str) = DE(src);
  return;
}

int main(){  
unsigned long long decrypted_source_str= 0x9d96ce27e370975c;
  unsigned long long source_key= 0LL;
  unsigned long long  encrypted_str, decrypted_str= 0LL;
  unsigned int i,j,d=0;
  
     printf("[암호] : ");
   print_hex(decrypted_source_str);
   print_binary(decrypted_source_str);
   
 /*   printf("[키] : ");
   print_hex(source_key);
   print_binary(source_key);*/
for(i=10000; i>1000; i-=2){  
source_key =i;
 decryption(decrypted_source_str, &decrypted_str, source_key);
	//printf("[복호] : ");
   //print_hex(decrypted_str);
  //print_binary(decrypted_str);

//  printf("%d. ",i);
if( 
 (((i&0xFF000000)>=48)|((i&0xFF000000)<=57)) & (((i&0xFF000000)>=65)|((i&0xFF000000)<=90)) & (((i&0xFF000000)>=97)|(i&0xFF000000)<=122)&
 (((i&0x00FF0000)>=48)|((i&0x00FF0000)<=57)) & (((i&0x00FF0000)>=65)|((i&0x00FF0000)<=90)) & (((i&0x00FF0000)>=97)|(i&0x00FF0000)<=122)&
 (((i&0x0000FF00)>=48)|((i&0x0000FF00)<=57)) & (((i&0x0000FF00)>=65)|((i&0x0000FF00)<=90)) & (((i&0x0000FF00)>=97)|(i&0x0000FF00)<=122)&
 (((i&0x000000FF)>=48)|((i&0x000000FF)<=57)) & (((i&0x000000FF)>=65)|((i&0x000000FF)<=90)) & (((i&0x000000FF)>=97)|(i&0x000000FF)<=122))
   {  
printf("%d ",i);
print_char(decrypted_str);
  }}
      encryption(decrypted_str, &encrypted_str, source_key);
  encryption(decrypted_str, &encrypted_str, source_key);
	printf("[다시 암호] : ");
   print_hex(encrypted_str);
  print_binary(encrypted_str); 
  
  system("pause");         
  return 0;         
}

/*unsigned long long decrypted_source_str= 0xda02ce3a89ecac3b;
   unsigned long long source_key= 0x0f1571c947d9e859;
  unsigned long long  encrypted_str, decrypted_str= 0LL;*/
  
  /*unsigned long long decrypted_source_str= 0x9d96ce27e370975c;
  unsigned long long source_key= 0LL;
  unsigned long long  encrypted_str, decrypted_str= 0LL;
  unsigned int i=0; */

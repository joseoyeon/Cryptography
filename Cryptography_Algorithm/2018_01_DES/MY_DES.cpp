#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int KEY;
unsigned int L_key;
unsigned int R_key;

  void print_binary(const unsigned long long* t, int size) {
  int i,j,b = 0;
  int d;
   unsigned long long tmp =1LL;
   unsigned long long *T;
  
  if(size >= 8 | size==0) {d=8;}
  else {d = size; size +=8;}
  
   for (j=0; j<(size/8); j++){
	for (i=d*8-1; i>=0; i--,b++) {
		printf("%d",*(t+j) & ((tmp << i) )? 1:0); 
		
		if(b%4 == 3){printf(" ");}
		if(b%32== 31){printf("\n");};
	}
   }
	printf("\n\n");
}

 unsigned int IP(unsigned int*  src) {
  unsigned int tmp = 1, text = 0;
  
  static char perm[] = { 57,49,41,33,25,17, 9, 1,59,51,43,35,27,19,11, 3,
                         61,53,45,37,29,21,13, 5,63,55,47,39,31,23,15, 7,
                         56,48,40,32,24,16, 8, 0,58,50,42,34,26,18,10, 2,
                         60,52,44,36,28,20,12, 4,62,54,46,38,30,22,14, 6 };
                       
  for(char i = 0; i < 64; i++, tmp = tmp << 1L) if (*src& (1L << perm[i])) text |= tmp;
  return text;}

unsigned int FP(unsigned int* src){
  unsigned int tmp = 1, text = 0;
  
  static char perm[] =  {39, 7,47,15,55,23,63,31,38, 6,46,14,54,22,62,30,
                         37, 5,45,13,53,21,61,29,36, 4,44,12,52,20,60,28,
                         35, 3,43,11,51,19,59,27,34, 2,42,10,50,18,58,26,
                         33, 1,41, 9,49,17,57,25,32, 0,40, 8,48,16,56,24 };
                       
  for(char i = 0; i < 64; i++, tmp = tmp << 1) if (*src & (1 << perm[i])) text |= tmp; 
  return text;}

void created_key(const char* key){
	unsigned long tmp = 1L, k=0L;
	  static char PC1[] = { 56,48,40,32,24,16, 8, 0,57,49,41,33,25,17,
  						  9, 1,58,50,42,34,26,18,10, 2,59,51,43,35,
                         62,54,46,38,30,22,14, 6,61,53,45,37,29,21,
						 13, 5,60,52,44,36,28,20,12, 4,27,19,11, 3 };

	for (char i=0; i<56; i++, tmp = tmp << 1L){
		if(*(unsigned long *)key & (1L << PC1[i])){ KEY |= tmp; }
		printf("%d ", KEY);
	}
}

void print_str(const char* str, int n){
	for(int i=0; i<n;i++){
		printf("%02x",(unsigned char)str[i]);
		if(i%8 == 7){printf(" ");}
		else if(i%32==31){printf("\n");}
	}
	printf("\n\n");
}
void des_Encryption (char* plain_text,char * key,char *emcryption_str){
	
	created_key(key);
	IP((unsigned int *)plain_text);



	FP((unsigned int *)plain_text);
}
int main() {
	char* plain_text= "HELLO WORLD!!!!!";
	char secreat_key[] = "1234567";
	char emcryption_str[256], decryption_str[256]; //암호문이랑 복호문 저장할 배열
	int n = strlen(plain_text);
	int r = n%8;

	if(r){
		printf("%d만큼 줄이거나 %d만큼 늘리세요!",r, 8-r);
		/*plain_text = (char *)realloc(plain_text, sizeof(char)*(8-r));
		if(plain_text ==NULL){
		printf("8의 배수로 입력하세요");
		exit(1);
		}
		for (int i=0; i<8-r; i++){
		plain_text[n+i] =1;
		}
		print_str(plain_text,n);
		*/}
	else{
	printf("%s\n",plain_text);
	print_str(plain_text,n);

    des_Encryption (plain_text, secreat_key,emcryption_str);
	print_str(plain_text,n);
	printf("%s\n",plain_text);
	}

	system("pause");
return 0;
}



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
 static const unsigned int Inverse_sbox[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
 };
    static const unsigned char sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

void print_hex(unsigned char *t, unsigned long long j, unsigned long long k )
{
  unsigned int i=0;

  for(i = 0; i<j; i++){
    printf("%02x ", t[i]);
    if(i % k == k-1){printf("\n");}  
  }
  printf("\n");
}

void Sub_Byte(unsigned char* source){
   char i,j;

for (j=0; j<4; j++)
   for(i=0; i<4; i++){
      source[i*4+j] = sbox[(source[i*4+j])];
   }
}//여기서의 source 가 lookup

void Inverse_Sub_Byte(unsigned char* source){
   
   char i,j;

for (j=0; j<4; j++)
   for(i=0; i<4; i++){
      source[i*4+j] = Inverse_sbox[(source[i*4+j])];
   }
}

void Shift_Row(unsigned char * source,int p){
 char i,j,k;
 unsigned int tmp;

for (i=1; i<4; i++){
   for (k=0; k<i; k++){
   
   if(p==0){
     tmp = source[i*4];   
     for(j=0; j<3; j++){source[i*4+j] = source [i*4+j+1];}
      source[i*4 + 3] = tmp;
    }
   else if(p ==1){
     tmp = source[i*4+3];   
     for(j=2; j>=0; j--){
      source[i*4+j+1] = source [i*4+j];}
      source[i*4] = tmp;
   }
   }
   }
} //여기서의 soruce 가 shiftrow의 lookup

unsigned char MC(unsigned char src, unsigned int p){
   /*(source[0*4+j]*2)^(source[0*4+j] & 0x80 ? 0x1b : 0);//*2
  (source[0*4+j])^((source[0*4+j]*2)^(source[0*4+j] & 0x80 ? 0x1b : 0));//a+a*2
*/
   int i;
   unsigned char tmp[4];
   tmp [0] = src;
   
   for (i=1; i<4; i++){
      src = (src*2)^(src& 0x80 ? 0x1b : 0);
      tmp [i] = src;
   }
   
   switch (p) {
      case 2 : src = tmp[1]; break; //2
      case 3 : src = tmp[1]^tmp[0]; break; //2+1
      case 9 : src = tmp[3]^tmp[0]; break; //8+1
      case 0x0b : src = tmp[3] ^ tmp[1] ^ tmp[0] ;break; // 8+2+1
      case 0x0d : src = tmp[3]^tmp[2]^tmp[0]; break; //8+4+1
      case 0x0e : src = tmp[3]^tmp[2]^tmp[1]; break; // 8+4+2
   }
   
   return src;
}

void Mix_Column(unsigned char * source){
   
char i,j;
unsigned char tmp[16];

/*    printf("Mix_Column\n");
   print_hex(source);
*/   

for (j=0; j<4; j++){
   tmp[0*4+j] = MC(source[0*4+j],2) ^ MC(source[1*4+j],3) ^   (source[2*4+j])   ^   (source[3*4+j]);
   tmp[1*4+j] =   (source[0*4+j])   ^ MC(source[1*4+j],2) ^ MC(source[2*4+j],3) ^   (source[3*4+j]);   
   tmp[2*4+j] =   (source[0*4+j])   ^   (source[1*4+j])   ^ MC(source[2*4+j],2) ^ MC(source[3*4+j],3);
   tmp[3*4+j] = MC(source[0*4+j],3) ^   (source[1*4+j])   ^   (source[2*4+j])   ^ MC(source[3*4+j],2);
}

  for (j=0; j<4; j++){
  source[0*4+j] = tmp[0*4+j];
  source[1*4+j] = tmp[1*4+j];
  source[2*4+j] = tmp[2*4+j];
  source[3*4+j] = tmp[3*4+j];
  }
}//여기서의 source 가 lookup

void Inverse_Mix_Column(unsigned char * source){
char i,j;
/*unsigned char perm[16] = {0x02, 0x03, 0x01, 0x01,
0x01, 0x02, 0x03, 0x01,
0x01, 0x01, 0x02, 0x03,
0x03, 0x01, 0x01, 0x02
};
*/
printf("inverse_mix_column\n");
printf("%02x %02x %02x %02x, %02x %02x %02x %02x, %02x\n" ,source[0*4+j] , source[1*4+j] , source[2*4+j] , source[3*4+j], MC(source[0*4+j],0x0E) , MC(source[1*4+j],0x0B) , MC(source[2*4+j],0x0D) , MC(source[3*4+j],0x09), MC(source[0*4+j],0x0E) ^ MC(source[1*4+j],0x0B) ^ MC(source[2*4+j],0x0D) ^ MC(source[3*4+j],0x09));
unsigned char tmp[16];

for (j=0; j<4; j++){
   tmp[0*4+j] = MC(source[0*4+j],0x0E) ^ MC(source[1*4+j],0x0B) ^ MC(source[2*4+j],0x0D) ^ MC(source[3*4+j],0x09);
   tmp[1*4+j] = MC(source[0*4+j],0x09) ^ MC(source[1*4+j],0x0E) ^ MC(source[2*4+j],0x0B) ^ MC(source[3*4+j],0x0D);   
   tmp[2*4+j] = MC(source[0*4+j],0x0D) ^ MC(source[1*4+j],0x09) ^ MC(source[2*4+j],0x0E) ^ MC(source[3*4+j],0x0B);
   tmp[3*4+j] = MC(source[0*4+j],0x0B) ^ MC(source[1*4+j],0x0D) ^ MC(source[2*4+j],0x09) ^ MC(source[3*4+j],0x0E);
   }
    
/*
for (j=0; j<4; j++){
   tmp[0*4+j] = MC(perm[0*4+j],0x0E) ^ MC(perm[1*4+j],0x0B) ^ MC(perm[2*4+j],0x0D) ^ MC(perm[3*4+j],0x09);
   tmp[1*4+j] = MC(perm[0*4+j],0x09) ^ MC(perm[1*4+j],0x0E) ^ MC(perm[2*4+j],0x0B) ^ MC(perm[3*4+j],0x0D);   
   tmp[2*4+j] = MC(perm[0*4+j],0x0D) ^ MC(perm[1*4+j],0x09) ^ MC(perm[2*4+j],0x0E) ^ MC(perm[3*4+j],0x0B);
   tmp[3*4+j] = MC(perm[0*4+j],0x0B) ^ MC(perm[1*4+j],0x0D) ^ MC(perm[2*4+j],0x09) ^ MC(perm[3*4+j],0x0E);
   }
   
   printf("이거\n");
   print_hex(tmp);
*/ 
   
  for (j=0; j<4; j++){
  source[0*4+j] = tmp[0*4+j];
  source[1*4+j] = tmp[1*4+j];
  source[2*4+j] = tmp[2*4+j];
  source[3*4+j] = tmp[3*4+j];
  }
}

unsigned char W[176];
void Key_Schedule(unsigned char* source){
unsigned char Rcon[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  };

char j;
for(j=0; j<=3; j++){
   W[0*11*4+j] = source[0*4+j];
   W[1*11*4+j] = source[1*4+j];    
   W[2*11*4+j] = source[2*4+j];
   W[3*11*4+j] = source[3*4+j];
}//4개를 집어 넣고 

for (j=4; j<44; j++){
   if(j%4 ==0){
   W[0*11*4+j] = W[0*11*4+j-4]^sbox[W[1*11*4+j-1]]^Rcon[0*10+j/4-1];
   W[1*11*4+j] = W[1*11*4+j-4]^sbox[W[2*11*4+j-1]]^Rcon[1*10+j/4-1];    
   W[2*11*4+j] = W[2*11*4+j-4]^sbox[W[3*11*4+j-1]]^Rcon[2*10+j/4-1];
   W[3*11*4+j] = W[3*11*4+j-4]^sbox[W[0*11*4+j-1]]^Rcon[3*10+j/4-1];
   }
   else {
   W[0*11*4+j] = W[0*11*4+j-4]^ W[0*11*4+j-1];
   W[1*11*4+j] = W[1*11*4+j-4]^ W[1*11*4+j-1];    
   W[2*11*4+j] = W[2*11*4+j-4]^ W[2*11*4+j-1];
   W[3*11*4+j] = W[3*11*4+j-4]^ W[3*11*4+j-1];
   }
   }
   
   printf("key \n");
   print_hex(W,176,44);
}

void Add_Round_Key(unsigned char* source, int i){
   char j;
   unsigned char tmp[16];
   /*for print*/
   for (j=0; j<4; j++){
   tmp[0*4+j] = W[0*4*11+i*4+j];
   tmp[1*4+j] = W[1*4*11+i*4+j];   
   tmp[2*4+j] = W[2*4*11+i*4+j];
   tmp[3*4+j] = W[3*4*11+i*4+j];
   }
   
   printf("%dth round key\n",i);
   print_hex(tmp,16LL,4LL);
   
for (j=0; j<4; j++){
   source[0*4+j] = source[0*4+j]^W[0*4*11+i*4+j];
   source[1*4+j] = source[1*4+j]^W[1*4*11+i*4+j];   
   source[2*4+j] = source[2*4+j]^W[2*4*11+i*4+j];
   source[3*4+j] = source[3*4+j]^W[3*4*11+i*4+j];
   }
}
/*암호화 과정*/
void AES_Encrypt(unsigned char * plainText, unsigned char * cipher_key, unsigned char*Encrypt_text){
int i=0;

   Key_Schedule(cipher_key);

   Add_Round_Key(plainText,0);
   printf("Add Round Key\n");
   print_hex(plainText,16LL,4LL);
   
   for (i=1; i<10; i++){
   printf ("%dth \n",i);
   Sub_Byte(plainText); //Sub_Byte
   printf("Sub_Byte\n");
   print_hex(plainText,16LL,4LL);
   
   Shift_Row(plainText,0);
   printf("Shift_Row\n");
   print_hex(plainText,16LL,4LL);
   
   Mix_Column(plainText);
   printf("Mix_Column\n");
   print_hex(plainText,16LL,4LL);
   
   Add_Round_Key(plainText,i);
   printf("Add Round Key\n");
   print_hex(plainText,16LL,4LL);
}

/*9번째*/   
    printf ("10th \n");
    Sub_Byte(plainText); //Sub_Byte
   printf("Sub_Byte\n");
   print_hex(plainText,16LL,4LL);

   Shift_Row(plainText,0);
   printf("Shift_Row\n");
   print_hex(plainText,16LL,4LL);
   
   Add_Round_Key(plainText,10);
   printf("Add Round Key\n");
   print_hex(plainText,16LL,4LL);
}

/*복호화  과정*/
void AES_Decrypt(unsigned char * plainText, unsigned char * cipher_key,unsigned char*Encrypt_text){
int i;
   printf("plainText\n");
   print_hex(plainText,16LL,4LL);
   
   Add_Round_Key(plainText,10);
   printf("Add Round Key\n");
   print_hex(plainText,16LL,4LL);
   
   Shift_Row(plainText,1);
   printf("Shift_Row\n");
   print_hex(plainText,16LL,4LL);
   
   Inverse_Sub_Byte(plainText); //Sub_Byte
   printf("Inverse_Sub_Byte\n");
   print_hex(plainText,16LL,4LL);
   
   for (i=9; i>0; i--){
   
   Add_Round_Key(plainText,i);
   printf("Add Round Key\n");
   print_hex(plainText,16LL,4LL);
   
   Inverse_Mix_Column(plainText);
   printf("Mix_Column\n");
   print_hex(plainText,16LL,4LL);
   
   Shift_Row(plainText,1);
   printf("Shift_Row\n");
   print_hex(plainText,16LL,4LL);
   
   printf ("%d번째 \n",i);
   Inverse_Sub_Byte(plainText); //Sub_Byte
   printf("Inverse_Sub_Byte\n");
   print_hex(plainText,16LL,4LL);

}
   Add_Round_Key(plainText,0);
   printf("Add Round Key\n");
   print_hex(plainText,16LL,4LL);
}

int main(){  
    unsigned char plainText[16]  /*= {0x01, 0x89, 0xfe, 0x76,
                          0x23, 0xab, 0xdc, 0x54,
                          0x45, 0xcd, 0xba, 0x32,
                          0x67, 0xef, 0x98, 0x10
                         }*/; 
                      
    unsigned char cipher_key[16] = {0x0f, 0x47, 0x0c, 0xaf,
                          0x15, 0xd9, 0xb7, 0x7f,
                          0x71, 0xe8, 0xad, 0x67,
                          0xc9, 0x59, 0xd6, 0x98
                         }; 
   unsigned char Encrypt_text[16], Decrypt_text[16];
    unsigned long long text[2] = {0x0123456789abcdef,0xfedcba9876543210};
    unsigned long long key[2] = {0x0f1571c947d9e859,0x0cb7add6af7f6798};
    
    
    printf("Encrypt_text\n");
//    printf("암호화할 문장을 써주세요1/2(8문자)");
//   scanf("%ull",&text[0]);    
   plainText[0]= (unsigned char)(text[0]>>(8*7)); plainText[1]= (unsigned char)(text[0]>>8*3); 
   plainText[4]= (unsigned char)(text[0]>>8*6); plainText[5]= (unsigned char)(text[0]>>8*2);
   plainText[8]= (unsigned char)(text[0]>>8*5); plainText[9]= (unsigned char)(text[0]>>8*1);
   plainText[12]= (unsigned char)(text[0]>>8*4); plainText[13]= (unsigned char)(text[0]>>(8*0));
   
//   printf("\n암호화할 문장을 써주세요2/2(8문자)\n");
//   scanf("%ull",&text[1]);
   plainText[2]= (unsigned char)(text[1]>>(8*7)); plainText[3]= (unsigned char)(text[1]>>8*3); 
   plainText[6]= (unsigned char)(text[1]>>8*6); plainText[7]= (unsigned char)(text[1]>>8*2);
   plainText[10]= (unsigned char)(text[1]>>8*5); plainText[11]= (unsigned char)(text[1]>>8*1);
   plainText[14]= (unsigned char)(text[1]>>8*4); plainText[15]= (unsigned char)(text[1]>>(8*0));
       
   print_hex(plainText,16LL,4LL);
    printf("KEY\n");
//    printf("암호화할 키를 써주세요1/2(8문자)");
//   scanf("%ull",&key[0]);    
   cipher_key[0]= (unsigned char)(key[0]>>(8*7)); cipher_key[1]= (unsigned char)(key[0]>>8*3); 
   cipher_key[4]= (unsigned char)(key[0]>>8*6); cipher_key[5]= (unsigned char)(key[0]>>8*2);
   cipher_key[8]= (unsigned char)(key[0]>>8*5); cipher_key[9]= (unsigned char)(key[0]>>8*1);
   cipher_key[12]= (unsigned char)(key[0]>>8*4); cipher_key[13]= (unsigned char)(key[0]>>(8*0));
   
//   printf("\n암호화할 키을 써주세요(8문자)2/2\n");
//   scanf("%ull",&key[1]);
   cipher_key[2]= (unsigned char)(key[1]>>(8*7)); cipher_key[3]= (unsigned char)(key[1]>>8*3); 
   cipher_key[6]= (unsigned char)(key[1]>>8*6); cipher_key[7]= (unsigned char)(key[1]>>8*2);
   cipher_key[10]= (unsigned char)(key[1]>>8*5); cipher_key[11]= (unsigned char)(key[1]>>8*1);
   cipher_key[14]= (unsigned char)(key[1]>>8*4); cipher_key[15]= (unsigned char)(key[1]>>(8*0));
   
   print_hex(cipher_key,16LL,4LL);
    
    printf("AES_Encrypt\n");
   AES_Encrypt(plainText, cipher_key,Encrypt_text);
    
    printf("AES_Decrypt.\n");
    AES_Decrypt(plainText, cipher_key,Encrypt_text);

   system("pause");         
  return 0;         
}
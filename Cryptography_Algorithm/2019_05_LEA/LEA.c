#include<stdio.h>
#include <string.h>

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define ROL(x,i) (((x) << (i)) | ((x) >> (32-(i))))
#define ROR(x,i) (((x) >> (i)) | ((x) << (32-(i))))
#define BitToInt(x) 
#define IntToBit(n)
// K 비트 128비트라고 하자
// 라운드 키 : NR 개, 192 bit
// 암호화 키 스케줄링
// 라운드 함수 Round : feistal 구조로 이거 하나 필요

void LEA_enc_KeySchedule(uint8_t* K, uint32_t* RK, uint8_t Round);
void LEA_dec_KeySchedule(uint8_t* K, uint32_t* RK, uint8_t Round);
void LEA_Encrypt(uint32_t *X, uint32_t *RK, uint8_t Round);
void LEA_Decrypt(uint32_t *X, uint32_t *RK, uint8_t Round);

int main() {
    uint8_t K[16] = {0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0};
    uint8_t P[16]=  {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
    uint32_t X[4];
    uint32_t D[4] = {0,};
    uint32_t RK[144] = {0,};
    uint8_t i=0, k=0;

    memcpy(X, P, 16);
    memcpy(RK, K, 16);

    printf("\nPlainText : ");
    for (i=0; i<16; i++) printf("%02x ", P[i]);
    printf("\nKey : ");
    for (i=0; i<16; i++) printf("%02x ", K[i]);    

    LEA_enc_KeySchedule(K, RK, 24);
    LEA_Encrypt(X, RK, 24);

    printf("\nEncrypt : ");
    memcpy(P, X, 16);
    for (i=0; i<16; i++) printf("%02x ", P[i]);
    // for (i=0; i<4; i++) printf("%08x ", X[i]);
    /*출력 바꿔서 다시 저장하는 함수 바이트 단위로*/

    LEA_dec_KeySchedule(K, RK, 24);
    LEA_Decrypt(X, RK, 24);

    printf("\nDecrypt : ");
    memcpy(P, X, 16);
    for (i=0; i<16; i++) printf("%02x ", P[i]);
    // for (i=0; i<4; i++) printf("%08x ", X[i]);

    // system("pause");
    return 0;
}

void LEA_Encrypt(uint32_t * X, uint32_t *RK, uint8_t Round){
    uint32_t X_[4]; 
    uint32_t i,j=0,q;

    for(i=0; i<Round; i++)
    {
        
        /*################출력####################*/
    // printf("\n%d, text : ",i );
    // for (q=0; q<4; q++) printf("%08x ", X[q]);
    //     printf("\n\n");
    // if(i != 25) {printf("\n%d, key : ",i +1);
    // for (q=j; q<j+6; q++){ printf("%08x ", RK[q]);}}
        /*####################################*/

        X_[0] = (X[0]^RK[j++]) + (X[1]^RK[j++]);
        X_[0] = ROL(X_[0], 9);
        
        X_[1] = (X[1]^RK[j++]) + (X[2]^RK[j++]);
        X_[1] = ROR(X_[1], 5);
        
        X_[2] = (X[2]^RK[j++]) + (X[3]^RK[j++]);
        X_[2] = ROR(X_[2], 3);

        X_[3] = X[0];
    memcpy(X, X_, 16);
    }
}

void LEA_Decrypt(uint32_t * X, uint32_t *RK, uint8_t Round){
    uint32_t X_[4]; 
    uint32_t i,j=0,q;

    for(i=0; i<Round; i++)
    {
        /*################출력####################*/
    // printf("\n%d, text : ",i );
    // for (q=0; q<4; q++) printf("%08x ", X[q]);
    //     printf("\n\n");
    // if(i != 25) {printf("\n%d, key : ",i +1);
    // for (q=j; q<j+6; q++){ printf("%08x ", RK[q]);}}
        /*####################################*/

        X_[0] = X[3];

        X_[1] = ROR(X[0], 9);
        X_[1] = (X_[1] - (X_[0]^RK[j++])) ^ RK[j++];

        X_[2] = ROL(X[1], 5);
        X_[2] = (X_[2] - (X_[1]^RK[j++])) ^ RK[j++];

        X_[3] = ROL(X[2], 3);
        X_[3] = (X_[3] - (X_[2]^RK[j++])) ^ RK[j++] ;
  
    memcpy(X, X_, 16);
    }
}

const uint32_t C[8] = {0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec, 0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957};

void LEA_enc_KeySchedule(uint8_t* K, uint32_t* RK, uint8_t Round){
    uint32_t T[4];
    uint32_t i=0,j=0,q;

    memcpy(T, K, 16);

    for(i=0; i<Round; i++)
    {
        T[0] = (T[0]+ROL(C[i % 4], i));
        T[0]  = ROL(T[0] ,1);

        T[1] = (T[1] + ROL(C[i % 4], i+1));
        T[1]  = ROL(T[1], 3);

        T[2] = (T[2] + ROL(C[i % 4], i+2));
        T[2]  = ROL(T[2] ,6);

        T[3] = (T[3] + ROL(C[i % 4], i+3));
        T[3]  = ROL(T[3] ,11);

        RK[j] = T[0];
        RK[j+1] = T[1];
        RK[j+2] = T[2];
        RK[j+3] = T[1];
        RK[j+4] = T[3];
        RK[j+5] = T[1];
        j+=6;
    }
        /*################출력####################*/
    /*키 출력*/
    // for (q=0; q<144; q++) {
    //     if(q%6 == 0) printf("\n");
    //     printf("%08x ", RK[q]);}
    // printf("\n\nend key\n\n");
            /*####################################*/

}

void LEA_dec_KeySchedule(uint8_t* K, uint32_t* RK, uint8_t Round){
    uint32_t T[4];
    uint32_t i=0,j=138,q;
    
    memcpy(T, K, 16);
    // j=138;
    for(i=0; i<Round; i++)
    {
        T[0] = (T[0]+ROL(C[i % 4], i));
        T[0]  = ROL(T[0] ,1);
    
        T[1] = (T[1] + ROL(C[i % 4], i+1));
        T[1]  = ROL(T[1], 3);

        T[2] = (T[2] + ROL(C[i % 4], i+2));
        T[2]  = ROL(T[2] ,6);

        T[3] = (T[3] + ROL(C[i % 4], i+3));
        T[3]  = ROL(T[3] ,11);

        RK[j] = T[0];
        RK[j+1] = T[1];
        RK[j+2] = T[2];
        RK[j+3] = T[1];
        RK[j+4] = T[3];
        RK[j+5] = T[1];
        // if(j-6 >0)
        j-=6;
    }
        /*################출력####################*/
    /*키 출력*/
    // for (q=0; q<144; q++) {
    //     if(q%6 == 0) printf("\n");
    //     printf("%08x ", RK[q]);}
    // printf("\n\nend key\n\n");
        /*####################################*/
}
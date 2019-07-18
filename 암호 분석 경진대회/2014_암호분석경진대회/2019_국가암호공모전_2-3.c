#include <stdio.h>
// typedef unsigned char uint8_t

unsigned char add (unsigned char* R, unsigned char* IN1, unsigned char* IN2){
//add 함수는 덧셈 코드를 구현함
 // (R) 7 함수 출력 값인 문자열 은 바이트임
 // (IN1 IN2) 7 함수 입력 값인 문자열 그리고 은 모두 바이트임
 // (1 ) 함수 리턴 값 바이트 은 덧셈에 대한 오버플로우 값 저장용으로 활용
 unsigned char i, carry;
    for(i=6; i>=0; i--){
        R[i] = IN1[i] ^ IN2[i];
        if(R[i] < IN1[i]){ carry^ 0x01;}
        carry << 1; 
    }

 return carry;
}
void mod (unsigned char* OUT, unsigned char* IN, unsigned char CARRY){
 //mod 함수는 모듈러 리덕션 코드를 구현함
 // (OUT) 7 함수 출력 값인 문자열 은 바이트임
 // (IN) 7 함수 입력 값 중 문자열 은 바이트임
 // (CARRY) 1 함수 입력 값 중 문자 는 바이트임
  unsigned char i;
  if()
      for(i=6; i>=0; i--){
        OUT[i] = IN[i] ^ CARRY;
        
    }
}

int main() {
    unsigned char A[] ={0x3C, 0x70, 0xB7, 0x25, 0x9D, 0x4F, 0x8D};
    unsigned char B[] ={0x29, 0x6B, 0x14, 0xAB, 0xD0, 0x55, 0xA5};
    unsigned char C[] ={0x2C, 0x9C, 0x09, 0x6D, 0xF0, 0x29, 0x54};
    unsigned char D[] ={0x3A, 0x54, 0x53, 0xE1, 0x66, 0x3E, 0xA7};
    unsigned char E[] ={0x39, 0x21, 0xFE, 0x57, 0x17, 0xE5, 0x1B};
    unsigned char R1[8], R2[8], R3[8],R4[8], R[8];
    unsigned char CARRY;
  unsigned char i;

    CARRY=add (R1,A,B);
    mod (R1,R1,CARRY);
    CARRY=add (R2,R1,C);
    mod (R2,R2,CARRY);
    CARRY=add (R3,R2,D);
    mod (R3,R3,CARRY);
    CARRY=add (R4,R3,E);
    mod (R,R4,CARRY);
    
    for(i=0; i<8; i++){
        printf("%08x", R[i]);
    }
    return 0;
}
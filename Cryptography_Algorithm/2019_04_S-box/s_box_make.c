#include  <stdint.h>
#include <stdio.h>

/*######################################################################*/
// https://en.wikipedia.org/wiki/Rijndael_S-box
// s-box 설계 코드 입니다.
// 2019. 07. 18
// inv-sbox는 향후의 나에게...
/*######################################################################*/


#define ROTL8(x, shift) ((uint8_t) (((x) << (shift)) | ((x) >> (8 - (shift)))))

void  initialize_aes_sbox ( uint8_t  sbox[ 256 ])  { 
	uint8_t  p  =  1 ,  q  =  1 ;
	
	// / * 루프 불변 : 갈루아 필드에서 p * q == 1 * / 
	do  { 
		// / * 3 * / 
		p  =  p  ^  ( p  <<  1 )  ^  ( p  &  0x80  ?  0x1B  :  0 );

		// // / * q를 3으로 나눕니다 (0xf6에 의한 곱셈과 같습니다) * / 
		q  ^=  q  <<  1 ; 
		q  ^=  q  <<  2 ; 
		q  ^=  q  <<  4 ; 
		q  ^=  q  &  0x80  ?  0x09  :  0 ;

		// / * 아핀 변환을 계산 * / 
		uint8_t  xformed  =  q  ^  ROTL8(q,1)  ^  ROTL8 (q,2)  ^  ROTL8 (q,3)  ^  ROTL8 (q,4);
		sbox[p]  =  xformed  ^  0x63 ; 

	}  while  ( p !=  1 );

	// / * 0은 inverse * / 
	sbox [ 0 ]  =  0x63 ;
}


// void  initialize_aes_inv_sbox ( uint8_t  inv_sbox[ 256 ])  { 
// 	uint8_t  p  =  1 ,  q  =  1 ;
	
// 	// / * 루프 불변 : 갈루아 필드에서 p * q == 1 * / 
// 	do  { 
// 		// / * 3 * / 
// 		p  =  p  ^  ( p  <<  1 )  ^  ( p  &  0x80  ?  0x1B  :  0 );

// 		// // / * q를 3으로 나눕니다 (0xf6에 의한 곱셈과 같습니다) * / 
// 		q  ^=  q  <<  1 ; 
// 		q  ^=  q  <<  2 ; 
// 		q  ^=  q  <<  4 ; 
// 		q  ^=  q  &  0x80  ?  0x09  :  0 ;

// 		// / * 아핀 변환을 계산 * / 
// 		uint8_t  xformed  =  ROTL8(q,1)  ^  ROTL8 (q,3)  ^  ROTL8 (q,6);
// 		inv_sbox[p]  =  xformed  ^  0x05 ; 

// 	}  while  ( p !=  1 );

// 	// / * 0은 inverse * / 
// 	inv_sbox [ 0 ]  =  0x52;
// }


int main() {
    uint8_t sbox[256];
    uint8_t inv_sbox[256];
    initialize_aes_sbox(sbox);
   
    // initialize_aes_inv_sbox (inv_sbox);
    for (int i=0 ;i <256; i++) {
        printf("%02x, ", sbox[i]);
        if(i%16 == 15) printf("\n");
    }
    return 0;
}
#pragma once
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

// 키 생성에 사용되는 함수 모음
char **Make_Round_Key(char *Key_Value, int Array_Size); // 키 생성함수
void Parity_Drop_Box(char *Key_Array_size, char *Return_Array); // 64비트 -> 56비트로 줄이는 함수
void Shift_Array(char *Array, int Array_Size, int Round); // 좌측 시프트 함수
void Compression_P_Function(char *Left_Array, char *Right_Array, char *Key_Array, int Round); // 키 생성 함수
void TtoB_For_Key(char *Text, char *Return_Array, int TextSize); // 키를 생성할 때 발생하는 문제를 해결하기 위한 전용함수

// 암-복호화에 사용되는 함수
char **Reshape_Array(char *Array, int File_Size); // 1차원 배열을 2차원 배열로 만드는 함수
void IP(char *Array, char *Save_Buffer); // Initial_Permutation 함수
void des_algorithm(char *Array, char **Round_Key, int File_Size); // 암-복호화 main 함수
void Encryption_Funtion(char *Array, char **Round_Key);// 실질적 암호화 함수
void Copy_Array(char *Original_Array, char *Copy_Array, int Array_Size); // 배열 복사 함수
void Expansion_Function(char *Original_Array, char *Return_Expansion_Array); // 확장 함수
void XOR_With_Key(char *Array, char *Round_Key, int round); // XOR연산 함수
char *Input_S_Box(char *Input_Array); // S 박스에 배열을 넣어주는 함수
unsigned char *S_Box_Start(unsigned char Bit_0, unsigned char Bit_1, unsigned char Bit_2, unsigned char Bit_3, unsigned char Bit_4, unsigned char Bit_5, int index); // S_BOX 실행 함수
unsigned char BtoSIndex(int value);// S_BOX 위치를 찾기위한 도움 함수
unsigned char *TenToBi(unsigned char *Array, int Size); // 10진수를 2진수로 변환하는 함수
void Straight_Function(char *Input_Array, char *Return_Array, int Array_Size); // 48비트 배열을 32비트 배열로 축소하는 함수
void Swap_Array(char *Left_Array, char *Right_Array, char *Copy_Array, char *Combine_Array, int round); // 배열을 스왑하는 함수
void FP(char *Array, char *Save_Buffer); // Final_Permutation
void Decryption_Funtion(char *Array, char **Round_Key); //복호화함수
void TtoB(char *Text, char *Return_Array, int TextSize); // 텍스트를 이진수 화 하는 함수


// 암호화와 키 함수 둘다 사용되는 함수
void TtoH(char *Array, char *Return_Array, int TextSize); //텍스트를 헥사화 시키는 함수
char Hex(char value); // 헥사로 치환하기 위해 계산하는 함수
void Divice_Array(char *Original_Text, char *Left_Array, char *Right_Array, int Original_Size); // 좌측배열 우측배열 나누어 주는 함수
void Print_Array(char *Array, int size); //배열에 저장된 값을 출력해 주는 함수
void BtoS(char *Array, int size ); // 비트를 문자화 시켜주는 함수
unsigned char Pow(char base, int n); // 제곱함수
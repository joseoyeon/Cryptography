#pragma once
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

// Ű ������ ���Ǵ� �Լ� ����
char **Make_Round_Key(char *Key_Value, int Array_Size); // Ű �����Լ�
void Parity_Drop_Box(char *Key_Array_size, char *Return_Array); // 64��Ʈ -> 56��Ʈ�� ���̴� �Լ�
void Shift_Array(char *Array, int Array_Size, int Round); // ���� ����Ʈ �Լ�
void Compression_P_Function(char *Left_Array, char *Right_Array, char *Key_Array, int Round); // Ű ���� �Լ�
void TtoB_For_Key(char *Text, char *Return_Array, int TextSize); // Ű�� ������ �� �߻��ϴ� ������ �ذ��ϱ� ���� �����Լ�

// ��-��ȣȭ�� ���Ǵ� �Լ�
char **Reshape_Array(char *Array, int File_Size); // 1���� �迭�� 2���� �迭�� ����� �Լ�
void IP(char *Array, char *Save_Buffer); // Initial_Permutation �Լ�
void des_algorithm(char *Array, char **Round_Key, int File_Size); // ��-��ȣȭ main �Լ�
void Encryption_Funtion(char *Array, char **Round_Key);// ������ ��ȣȭ �Լ�
void Copy_Array(char *Original_Array, char *Copy_Array, int Array_Size); // �迭 ���� �Լ�
void Expansion_Function(char *Original_Array, char *Return_Expansion_Array); // Ȯ�� �Լ�
void XOR_With_Key(char *Array, char *Round_Key, int round); // XOR���� �Լ�
char *Input_S_Box(char *Input_Array); // S �ڽ��� �迭�� �־��ִ� �Լ�
unsigned char *S_Box_Start(unsigned char Bit_0, unsigned char Bit_1, unsigned char Bit_2, unsigned char Bit_3, unsigned char Bit_4, unsigned char Bit_5, int index); // S_BOX ���� �Լ�
unsigned char BtoSIndex(int value);// S_BOX ��ġ�� ã������ ���� �Լ�
unsigned char *TenToBi(unsigned char *Array, int Size); // 10������ 2������ ��ȯ�ϴ� �Լ�
void Straight_Function(char *Input_Array, char *Return_Array, int Array_Size); // 48��Ʈ �迭�� 32��Ʈ �迭�� ����ϴ� �Լ�
void Swap_Array(char *Left_Array, char *Right_Array, char *Copy_Array, char *Combine_Array, int round); // �迭�� �����ϴ� �Լ�
void FP(char *Array, char *Save_Buffer); // Final_Permutation
void Decryption_Funtion(char *Array, char **Round_Key); //��ȣȭ�Լ�
void TtoB(char *Text, char *Return_Array, int TextSize); // �ؽ�Ʈ�� ������ ȭ �ϴ� �Լ�


// ��ȣȭ�� Ű �Լ� �Ѵ� ���Ǵ� �Լ�
void TtoH(char *Array, char *Return_Array, int TextSize); //�ؽ�Ʈ�� ���ȭ ��Ű�� �Լ�
char Hex(char value); // ���� ġȯ�ϱ� ���� ����ϴ� �Լ�
void Divice_Array(char *Original_Text, char *Left_Array, char *Right_Array, int Original_Size); // �����迭 �����迭 ������ �ִ� �Լ�
void Print_Array(char *Array, int size); //�迭�� ����� ���� ����� �ִ� �Լ�
void BtoS(char *Array, int size ); // ��Ʈ�� ����ȭ �����ִ� �Լ�
unsigned char Pow(char base, int n); // �����Լ�
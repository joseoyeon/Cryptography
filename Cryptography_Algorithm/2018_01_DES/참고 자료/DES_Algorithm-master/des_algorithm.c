#include "des.h"

unsigned char Initial_Permutation[64] = {
	58, 50, 42, 34, 26 ,18 ,10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

unsigned char Final_Permutation[64] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};

unsigned char Expansion_P_Box[48] = {
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

unsigned char Straight_P_Box[32] = {
	16, 7, 20, 21, 29, 12, 28, 17,
	1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9,
	19, 13, 30, 6, 22, 11, 4, 25
};

unsigned char SBOX[8][4][16] = {
	{
		{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
		{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
		{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
		{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 2, 14, 10, 0, 6, 13 }
	},{
		{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
		{ 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
		{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
		{ 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
	},{
		{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
		{ 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
		{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
		{ 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }
	},{
		{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
		{ 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
		{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
		{ 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
	},{
		{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
		{ 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
		{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
		{ 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
	},{
		{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
		{ 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
		{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },	
		{ 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
	},{
		{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
		{ 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
		{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
		{ 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
	},{
		{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
		{ 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
		{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
		{ 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
	}
};


// ��-��ȣȭ ����
void des_algorithm(char *Array, char **Round_Key , int File_Size) {
	int i = 0, j = 0;
	int block_size = (File_Size * 4/64);
	if ((File_Size * 4) % 64 == 0) { block_size -= 1; }
	char IF_Buffer[64] = { 0 ,};
	const int max_block_size = 64;
	// �迭 ����
	char *bit_array = (char *)calloc(File_Size * 4,sizeof(char));
	// �ؽ�Ʈ�� ��Ʈȭ
	TtoB(Array, bit_array, File_Size);
	//printf("�� ��Ʈȭ ��� \n");
	//Print_Array(bit_array, File_Size*4);
	printf("\n�� Hex������ ǥ�� \n");
	BtoS(bit_array, File_Size * 4);
	char **string = (char **)calloc(block_size,sizeof(char *));
	for (i = 0; i <= block_size; i++) {
		string[i] = (char *)calloc(max_block_size, sizeof(char));
	}
	// 2���� �迭�� ���·� ��ȯ
	string = Reshape_Array(bit_array, File_Size);
	free(bit_array);
	for (i = 0; i <= block_size; i++) {
		//printf("Initial Permutation ���� �� \n");
		//Print_Array(string[i], 64);
		IP(string[i], IF_Buffer);
		Encryption_Funtion(string[i], Round_Key);
		FP(string[i], IF_Buffer);
		//printf("��ȣȭ �� �� \n");
		//Print_Array(string[i], max_block_size);
		printf("\n��ȣ�� Hex ������ ǥ�� \n");
		BtoS(string[i], 64);
	}
	for (i = 0; i <= block_size; i++) {
		//printf("Initial Permutation ���� �� \n");
		//Print_Array(string[i], 64);
		IP(string[i], IF_Buffer);
		Decryption_Funtion(string[i], Round_Key);
		FP(string[i], IF_Buffer);
		//printf("��ȣȭ �� �� \n");
		//Print_Array(string[i], max_block_size);
		printf("\n��ȣȭ�� ��ȣ�� Hex ������ ǥ�� \n");
		BtoS(string[i], 64);
	}
	free(string);
}


// 1���� �迭�� 2�����迭�� �ٲپ� ���� ����
char **Reshape_Array(char *Array, int File_Size) {
	int i = 0, j = 0;
	int block_size = (File_Size * 4 / 64);
	const int max_block_size = 64;
	char **dimension = (char **)calloc(block_size, sizeof(char *));
	for(i=0;i<=block_size;i++){
		dimension[i] = (char *)calloc(max_block_size, sizeof(char));
	}
	for (j = 0; j <= block_size; j++) {
		for (i = 0; i < max_block_size; i++) {
			if ((i+j* max_block_size) < (File_Size*4)) {
				dimension[j][i] = Array[j*max_block_size + i];
			}
			else {
				dimension[j][i] = 0;
			}
		}
	}
	return dimension;
}


// 2�����迭�� �ٲپ 64���� ������� ���� ���� 64���� IP �����ϱ� initail_Permutation
void IP(char *Array,char *Save_Buffer) {
	int i = 0;
	Copy_Array(Array, Save_Buffer, 64);
	for (i = 0; i < 64; i++) {
 		Array[i] = Save_Buffer[Initial_Permutation[i] - 1];
	}
	// printf("IP ��� \n");
	// Print_Array(Array, 64);
}


// ��ȣȭ �Լ�
void Encryption_Funtion(char *Array,char **Round_Key) {
	int round = 0;
	const int max_round = 16;
	char left_array[32] = { 0 };
	char right_array[32] = { 0 };
	char copy_right_array[32] = { 0 };
	char expansion_array[48] = { 0 };

	unsigned char *s_box_array = (unsigned char *)calloc(32, sizeof(unsigned char));
	Divice_Array(Array, left_array, right_array, 64);
	//printf("LEFT_ARRAY \n");
	//Print_Array(left_array, 32);
	//printf("RIGHT_ARRAY \n");
	//Print_Array(right_array, 32);
	for (round; round < max_round; round++) {
		Copy_Array(right_array, copy_right_array, 32);		
		//printf("Right_Array \n");
		//Print_Array(right_array,32);
		//printf("Copy_Right_Array\n");
		//Print_Array(copy_right_array, 32);
		Expansion_Function(right_array, expansion_array);	
		//printf("Expansion_Function expansion_array\n");
		//Print_Array(expansion_array, 48);
		XOR_With_Key(expansion_array, Round_Key[round], round);
		//printf("Finish XOR_With_Key \n");
		//Print_Array(expansion_array,48);
		s_box_array = Input_S_Box(expansion_array);	
		//printf("s_box value \n");
		//Print_Array(s_box_array, 32);
		Straight_Function(s_box_array, right_array, 32);		
		//printf("Straight_Function in right_Array\n");
		//Print_Array(right_array, 32);
		Swap_Array(left_array, right_array, copy_right_array, Array,round);
		// printf("Swap_Array in left_Array \n");
		// Print_Array(left_array, 32);
		// printf("Swap_Array in right_Array \n");
		// Print_Array(right_array, 32);
		//
		// printf("Swap_Array in copy_right_Array \n");
		// Print_Array(copy_right_array, 32);
		// printf("Swap_Array in Array \n");
		// Print_Array(Array, 64);
 	}
}


// �迭 ���� �Լ�
void Copy_Array(char *Original_Array, char *Copy_Array,int Array_Size) {
	int i = 0;
	for (i = 0; i < Array_Size; i++) {
		Copy_Array[i] = Original_Array[i];
	}
}


// Ȯ�� ��Ʈ ���
void Expansion_Function(char *Original_Array, char *Return_Expansion_Array) {
	int i = 0;
	for (i = 0; i < 48; i++) {
		Return_Expansion_Array[i] = Original_Array[Expansion_P_Box[i]-1];
	}
}


// ���� Ű �� Ȯ��� ��Ʈ xor ����
void XOR_With_Key(char *Array,char *Round_Key,int round) {
	int i = 0;
	// printf("X0R ������ �迭 \n");
	// Print_Array(Array, 48);
	// printf("%d ���� Ű \n", round + 1);
	// Print_Array(Round_Key, 48);
	for (i = 0; i < 48; i++) {
		if (Array[i] == Round_Key[i]) {
			Array[i] = 0;
		}
		else {
			Array[i] = 1;
		}
	}
	// printf("XOR ���� ���� \n");
	// Print_Array(Array, 48);
}

// S_BOX �� �ֱ����� �Լ�
char *Input_S_Box(char *Input_Array) {
	int i = 0, j = 0;
	unsigned char *s_array = (unsigned char *)calloc(8, sizeof(unsigned char));
	for (i = 0; i < 48; i += 6,j++) {
		s_array[j]=S_Box_Start(Input_Array[i], Input_Array[i + 1], Input_Array[i + 2], Input_Array[i + 3], Input_Array[i + 4], Input_Array[i + 5],j);
	}
	//printf("S_BOX!!");
	//Print_Array(s_array, 8);
	return TenToBi(s_array, 8);
}


// �迭 ���� �Է¹޾Ƽ� �������� ������ȭ ���Ѽ� �迭�� ����
unsigned char *S_Box_Start(unsigned char Bit_0, unsigned char Bit_1, unsigned char Bit_2, unsigned char Bit_3, unsigned char Bit_4, unsigned char Bit_5,int index) {
	int x, y;
	y = Bit_0 * 10 + Bit_5 * 1;
	x = Bit_1 * 1000 + Bit_2 * 100 + Bit_3 * 10 + Bit_4;
	//printf("Index value : %d \n", index);
	//printf("X_value=%d Y_Value=%d \n", x, y);
	//printf("BtoSIndex(x) = %d   BtoSIndex(y) = %d  \n", BtoSIndex(x), BtoSIndex(y));
	//printf("######    %d    ######### \n", SBOX[index][BtoSIndex(y)][BtoSIndex(x)]);
	return SBOX[index][BtoSIndex(y)][BtoSIndex(x)];
}


// S_Box�� ��ġ�� ã�� �Լ�
unsigned char BtoSIndex(int value) {
	unsigned char result = 0;
	if (value / 1000 == 1) {
		result += 8;
		value -= 1000;
		if (value / 100 == 1) {
			result += 4;
			value -= 100;
			if (value / 10 == 1) {
				result += 2;
				value -= 10;
				if (value / 1 == 1) {
					result += 1;
					return result;
				}
				else {
					return result;
				}
			}
			else {
				if (value / 1 == 1) {
					result += 1;
					return result;
				}
				else {
					return result;
				}
			}
		}
		else {
			if (value / 10 == 1) {
				result += 2;
				value -= 10;
				if (value / 1 == 1) {
					result += 1;
					return result;
				}
				else {
					return result;
				}
			}
			else {
				if (value / 1 == 1) {
					result += 1;
					return result;
				}
				else {
					return result;
				}
			}
		}
	}
	else {
		if (value / 100 == 1) {
			result += 4;
			value -= 100;
			if (value / 10 == 1) {
				result += 2;
				value -= 10;
				if (value / 1 == 1) {
					result += 1;
					return result;
				}
				else {
					return result;
				}
			}
			else {
				if (value / 1 == 1) {
					result += 1;
					return result;
				}
				else {
					return result;
				}
			}
		}
		else {
			if (value / 10 == 1) {
				result += 2;
				value -= 10;
				if (value / 1 == 1) {
					result += 1;
					return result;
				}
				else {
					return result;
				}
			}
			else {
				if (value / 1 == 1) {
					result += 1;
					return result;
				}
				else {
					return result;
				}
			}
		}
	}
}


// S-Box���� ���� 10������ �迭�� ��Ƽ� �� ���� �迭�� ǥ���ϱ�
unsigned char *TenToBi(unsigned char *Array, int Size) {
	int i, j, count = 1;
	unsigned char *Return_Binary = (unsigned char *)calloc(32, sizeof(unsigned char));
	for (i = 0; i < Size; i++) {
		for (j = 3; j >= 0; j--) {
			Return_Binary[j + i * 4] = Array[i] % 2;
			Array[i] = Array[i] / 2;
		}
	}
	return Return_Binary;
}


// ��� �Լ�
void Straight_Function(char *Input_Array, char *Return_Array, int Array_Size) {
	int i = 0;
	for (i = 0; i < Array_Size; i++){
		Return_Array[i] = Input_Array[Straight_P_Box[i] - 1];
	}
}


// �迭 ���� �Լ�
void Swap_Array(char *Left_Array, char *Right_Array,char *Copy_Array,char *Combine_Array,int round) {
	char i = 0, temp = 0;
	for (i = 0; i < 32; i++) {
		Left_Array[i] = Left_Array[i] ^ Right_Array[i];
	}
	if (round == 15) {
		for (i = 0; i < 32; i++) {
			Combine_Array[i] = Left_Array[i];
			Combine_Array[i + 32] = Copy_Array[i];
		}
	}
	else {
		for (i = 0; i < 32; i++) {
			temp = Left_Array[i];
			Left_Array[i] = Copy_Array[i];
			Copy_Array[i] = temp;
			Right_Array[i] = Copy_Array[i];
		}
	}
}


// FP
void FP(char *Array,char *Save_Buffer) {
	int i = 0;
	Copy_Array(Array, Save_Buffer, 64);
	for (i = 0; i < 64; i++) {
		Array[i] = Save_Buffer[Final_Permutation[i] - 1];
	}
}



// ��ȣȭ �Լ�
void Decryption_Funtion(char *Array, char **Round_Key) {
	int round = 0;
	const int max_round = 16;
	char left_array[32] = { 0 };
	char right_array[32] = { 0 };
	char copy_right_array[32] = { 0 };
	char expansion_array[48] = { 0 };
	unsigned char *s_box_array = (unsigned char *)calloc(32, sizeof(unsigned char));
	Divice_Array(Array, left_array, right_array, 64);

	for (round; round < max_round; round++) {
		Copy_Array(right_array, copy_right_array, 32);
		Expansion_Function(right_array, expansion_array);		
		XOR_With_Key(expansion_array, Round_Key[15-round], (15 - round));
		s_box_array = Input_S_Box(expansion_array);		
		Straight_Function(s_box_array, right_array, 32);
		Swap_Array(left_array, right_array, copy_right_array, Array, round);
	}
}

// �迭�� �Է¹޾Ƽ� ���ڿ��� ��Ʈȭ ��Ų �迭�� ���Ͻ�Ű�� �Լ�
void TtoB(char *Text, char *Return_Array, int TextSize) {
	int index = 0, bitsize = 0, arraysize = 0;
	// ����Ȯ���� ���� ���� ��¹�
	for (index = 0; index < TextSize; index++) {
		for (bitsize = 3; bitsize >= 0; bitsize--) {
			Return_Array[bitsize + index * 4] = Text[index] % 2;
			Text[index] /= 2;
		}
	}
}
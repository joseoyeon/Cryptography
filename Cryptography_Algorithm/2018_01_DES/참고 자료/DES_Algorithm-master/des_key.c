#include "des.h"

unsigned char Round_Shift[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

unsigned char Parity_Drop[56] = {
	57 , 49 , 41 , 33 , 25 , 17 , 9 ,  1 ,
	58 , 50 , 42 , 34 , 26 , 18 , 10 , 2 ,
	59 , 51 , 43 , 35 , 27 , 19 , 11 , 3 ,
	60 , 52 , 44 , 36 , 63 , 55 , 47 , 39 ,
	31 , 23 , 15 , 7 , 62 , 54 , 46 , 38 ,
	30 , 22 , 14 , 6 , 61 , 53 , 45 , 37 ,
	29 , 21 , 13 , 5 , 28 , 20 , 12 , 4
};

unsigned char Compression_P_Box[48] = {
	14 , 17 , 11 , 24 , 1 , 5 , 3 , 28 ,
	15 , 6 , 21 , 10 , 23 , 19 , 12 , 4 ,
	26 , 8 , 16 , 7 , 27 , 20 , 13 , 2 ,
	41 , 52 , 31 , 37 , 47 , 55 , 30 , 40 ,
	51 , 45 , 33 , 48 , 44 , 49 , 39 , 56 ,
	34 , 53 , 46 , 42 , 50 , 36 , 29 , 32
};


// Ű ���� �Լ� , �����Լ�����
char **Make_Round_Key(char *Key_Value, int Array_Size) {
	int i = 0;
	const int max_round = 16;
	const int save_buffer_size = Array_Size * 8;
	const int max_size = 64;
	char parite_drop_result[56] = { 0 , };
	char left_array[28] = { 0 };
	char right_array[28] = { 0 };
	char **round_key = (char **)calloc(16, sizeof(char *));
	for (i = 0; i < 16; i++) {
		round_key[i] = (char *)calloc(48, sizeof(char));
	}
	// ���ڸ� ��Ʈȭ�ϱ����� ���� ����(���� �Ҵ�) �� ��Ʈȭ 
	char *save_buffer = (char *)calloc(save_buffer_size, sizeof(char));
	printf("\nŰ ���� ����ִ� �� ���ڷ� ǥ�� \n");
	Print_Array(Key_Value, 16);
	TtoB_For_Key(Key_Value, save_buffer, Array_Size);
	//printf("\n��� ������ ǥ���� Ű �� \n");
	//BtoS(save_buffer, save_buffer_size);
	//printf("�Է¹��� Ű �� \n");
	//Print_Array(save_buffer, 64);
	// ����Ȯ���� ���� ���
	
	// ������Ʈ ����
	Parity_Drop_Box(save_buffer, parite_drop_result);
	//printf("������Ʈ ���� \n");
	//Print_Array(parite_drop_result, 56);

	// �޸� �Ҵ� ����
	free(save_buffer);
	Divice_Array(parite_drop_result, left_array, right_array, 56);

	// ���� ������ ���� ���� ��� ���
	// printf("���� �迭 ���� ��� \n");
	// Print_Array(left_array, 28);

	// ���� ������ ���� ������ ��� ���
	// printf("������ �迭 ���� ��� \n");
	// Print_Array(right_array, 28);


	// ���� Ű ���
	// printf(" ���� Ű ��� \n");
	
	// 16���� ���ư��� �κ�
	for (i = 0; i < max_round; i++) {
		//���� ����Ʈ �ϴ� �κ�
		Shift_Array(left_array, 28, i);
		Shift_Array(right_array, 28, i);
		//printf("Left_Result [ %d ] ## SHIFT COUNT : %2d \n", i, Round_Shift[i]);
		//printf("���� �迭 ����Ʈ ��� \n");
		//Print_Array(left_array, 28);
		//printf("Right_Result [ %d ]  ## SHIFT COUNT : %2d \n", i, Round_Shift[i]);
		//printf("������ �迭 ����Ʈ ��� \n");
		//Print_Array(right_array, 28);
		Compression_P_Function(left_array, right_array, round_key[i], i);
		
		printf("\n%d ���� Ű \n", i + 1);
		//Print_Array(round_key[i], 48);
		BtoS(round_key[i],48);
	}
	return round_key;
}


// ���� ��Ʈ ����
void Parity_Drop_Box(char *Key_Array, char *Return_Array) {
	const int max_size = 56;
	int i = 0;
	for (i = 0; i < max_size; i++) {
		Return_Array[i] = Key_Array[Parity_Drop[i]-1];
		//printf("Key_Array[ %d ]= %d , i_value = %d \n", Parity_Drop[i]-1, Key_Array[Parity_Drop[i]-1],i);
	}
}


// ����Ʈ �Լ�
void Shift_Array(char *Array, int Array_Size, int Round) {
	int i = 0;
	int temp[2] = { 0, };
	if (Round_Shift[Round] == 1) {
		temp[0] = Array[0];
		for (i = 0; i < Array_Size - 1; i++) {
			Array[i] = Array[i + 1];
		}
		Array[Array_Size - 1] = temp[0];
	}
	else {
		temp[0] = Array[0];
		temp[1] = Array[1];
		for (i = 0; i < Array_Size - 2; i++) {
			Array[i] = Array[i + 2];
		}
		Array[Array_Size - 2] = temp[0];
		Array[Array_Size - 1] = temp[1];
	}
}

// ��ġ�� Compression_P_Box ��� ���ư��� �ϴ� �Լ�
void Compression_P_Function(char *Left_Array, char *Right_Array, char *Key_Array,int Round) {
	int i = 0;
	const int max_array_size = 56;
	char combine_array[56] = { 0, };
	for (i = 0; i<max_array_size / 2; i++) {
		combine_array[i] = Left_Array[i];
		combine_array[i + 28] = Right_Array[i];
	}
	for (i = 0; i < 48; i++) {
		Key_Array[i] = combine_array[Compression_P_Box[i]-1];
	}
}


// �迭�� �Է¹޾Ƽ� ���ڿ��� ��Ʈȭ ��Ų �迭�� ���Ͻ�Ű�� �Լ�
void TtoB_For_Key(char *Text, char *Return_Array, int TextSize) {
	int index = 0, bitsize = 0, arraysize = 0;
	// ����Ȯ���� ���� ���� ��¹�
	for (index = 0; index < TextSize; index++) {
		if (47 < Text[index] && Text[index] < 58) {
		Text[index] = Text[index] - 48;
		}
		else if (64 < Text[index] && Text[index] < 71) {
		Text[index] = Text[index] - 55;
		}
		for (bitsize = 3; bitsize >= 0; bitsize--) {
			Return_Array[bitsize + index * 4] = Text[index] % 2;
			Text[index] /= 2;
		}
	}
}
#include "des.h"

// ���� ������ �� ���� 16������ ��ȯ�Ͽ� �����ϴ� �Լ�
void TtoH(char *Array,char *Return_Array,int TextSize) {
	int i = 0, j = 0;
	for (i; i < TextSize; i++) {
		for (j = 1; j >= 0 ; j--) {
			Return_Array[i * 2 + j] = Array[i] % 16;
			Array[i] /= 16;
		}
	}
	for (i; i < TextSize; i++) {
		for (j = 1; j >= 0; j--) {
			Return_Array[i * 2 + j] = Hex(Return_Array[i * 2 + j]);
		}
	}
}

// ��簪�� ABCDEF�� ���·� ġȯ���ִ� �Լ�
char Hex(char value) {
	if (value == 10) {
		value = 'A';
	}
	else if (value == 11) {
		value = 'B';
	}
	else if (value == 12) {
		value = 'C';
	}
	else if (value == 13) {
		value = 'D';
	}
	else if (value == 14) {
		value = 'E';
	}
	else if (value == 15) {
		value = 'F';
	}
	else if (value < 0 || value > 15) {
		printf("ERROR VALUE !!!! \n");
	}
	else {
		value = value;
	}
	return value;
}


// �����迭 �����迭 ������
// �Էµ� ũ���� ������ �ű�� ������ �� �Ű��ش�.
void Divice_Array(char *Original_Text, char *Left_Array, char *Right_Array, int Original_Size) {
	int i = 0;
	for (i = 0; i < Original_Size; i++) {
		if (i < Original_Size / 2) {
			Left_Array[i] = Original_Text[i];
		}
		else {
			Right_Array[i - Original_Size / 2] = Original_Text[i];
		}
	}
}

// �迭 ����Լ�
void Print_Array(char *Array, int size) {
	int i = 0, count = 1;
	for (i = 0, count =1; i < size; i++, count++) {
		printf("%d ", Array[i]);
		if (count % 8 == 0) {
			printf("\n");
		}
	}
	printf("\n");
}


// 2������ ���ڷ� �ٲٴ� �Լ�
void BtoS(char *Array, int size) {
	int i = 0, multiple = 7;
	unsigned char result = 0;
	for (i = 0; i < size; i++) {
		if (i % 8 == 7) {
			result += Pow(Array[i], multiple);
			//printf("%d ^ %d = %d , result = %d \n", Array[i], multiple, Array[i] == 1 ? Pow(2, multiple) : 0, result);
			printf("%x ", result);
			result = 0;
			multiple = 7;
		}
		else {
			if (Array[i] == 1) {
				result += Pow(2, multiple);
			}
			//printf("%d ^ %d = %d , result = %d \n", Array[i], multiple,Array[i]==1? Pow(2, multiple):0, result);
			multiple--;
		}
	}
	printf("\n");
}


// �����Լ�
unsigned char Pow(char base, int n) {
	unsigned char result = 1;
	int i = 0;
	for (i = 0; i < n; i++) {
		result *= base;
	}
	return base == 0 ? 0 : result;
}
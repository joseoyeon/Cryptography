#include "des.h"

// 값이 들어오면 그 값을 16진수로 변환하여 저장하는 함수
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

// 헥사값을 ABCDEF의 형태로 치환해주는 함수
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


// 좌측배열 우측배열 나누기
// 입력된 크기의 절반을 옮기고 절반을 또 옮겨준다.
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

// 배열 출력함수
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


// 2진수를 문자로 바꾸는 함수
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


// 제곱함수
unsigned char Pow(char base, int n) {
	unsigned char result = 1;
	int i = 0;
	for (i = 0; i < n; i++) {
		result *= base;
	}
	return base == 0 ? 0 : result;
}
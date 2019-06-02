#pragma once

#define FILE_NAME "C:\\Users\\User\\Desktop\\DES\DES_algorithm\\data.txt"
#define ENCRYPTION_PATH "C:\\Users\\User\\Desktop\\DES\\DES_algorithm\\encryption.txt"
#define DECRYPTION_PATH "C:\\Users\\User\\Desktop\\DES\\DES_algorithm\\decryption.txt"

typedef struct FILE_Buffer {
	char *buffer;
	int file_size;
}FILE_Buffer;


// 파일 입출력에 해당하는 함수
FILE_Buffer File_I_O(void); // 파일 입출력 버퍼
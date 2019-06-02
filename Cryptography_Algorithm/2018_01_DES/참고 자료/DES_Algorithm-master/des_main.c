#include "des.h"
#include "file_i_o.h"

// 제  목 : 메인함수
// 생성일 : 18.05.15(화)
void main(void) {
	// 파일의 크기 , 파일을 불러오기위한 스트림
	int i = 0;
	int fsize = 0;
	FILE_Buffer fb = File_I_O();
	//키 생성 함수 진행
	// 에러 확인을 위한 출력문
	printf("\n파일에 담긴값 확인 \n");
	Print_Array(fb.buffer, fb.file_size);
	fsize = fb.file_size;
	char *hexarray = (char *)calloc(fsize * 2, sizeof(char));
	TtoH(fb.buffer, hexarray, fsize);
	char key_value[16] = { "AABB09182736CCD" };
	char **Round_key = (char **)calloc(16, sizeof(char *));
	for (i = 0; i < 16; i++) {
		Round_key[i] = (char *)calloc(48, sizeof(char));
	}
	Round_key = Make_Round_Key(key_value, 16);
	des_algorithm(hexarray, Round_key, fsize*2);
	free(Round_key);
	free(hexarray);
}

	
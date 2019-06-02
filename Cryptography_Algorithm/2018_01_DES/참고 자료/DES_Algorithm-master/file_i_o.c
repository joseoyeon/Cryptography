#include "des.h"
#include "file_i_o.h"

FILE_Buffer File_I_O(void) {
	// 파일의 크기 , 파일을 불러오기위한 스트림
	int i = 0;
	FILE *fp;
	FILE_Buffer fb;
	fp = fopen(FILE_NAME, "rt");
	// 파일 포인터를 파일의 끝까지 움직여 파일의 크기를 알아내기
	fseek(fp, 0L, SEEK_END);
	fb.file_size = ftell(fp);
	rewind(fp);
	// 파일에 담긴 값 중 저장된 크기만큼 배열을 할당하고 옮기기
	fb.buffer = (char *)calloc(fb.file_size, sizeof(char));
	fgets(fb.buffer, (fb.file_size + 1), fp);
	// 파일 열기가 끝나서 파일 연 포인터를 닫음
	fclose(fp);
	return fb;
}

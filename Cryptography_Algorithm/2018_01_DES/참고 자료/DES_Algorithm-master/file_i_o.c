#include "des.h"
#include "file_i_o.h"

FILE_Buffer File_I_O(void) {
	// ������ ũ�� , ������ �ҷ��������� ��Ʈ��
	int i = 0;
	FILE *fp;
	FILE_Buffer fb;
	fp = fopen(FILE_NAME, "rt");
	// ���� �����͸� ������ ������ ������ ������ ũ�⸦ �˾Ƴ���
	fseek(fp, 0L, SEEK_END);
	fb.file_size = ftell(fp);
	rewind(fp);
	// ���Ͽ� ��� �� �� ����� ũ�⸸ŭ �迭�� �Ҵ��ϰ� �ű��
	fb.buffer = (char *)calloc(fb.file_size, sizeof(char));
	fgets(fb.buffer, (fb.file_size + 1), fp);
	// ���� ���Ⱑ ������ ���� �� �����͸� ����
	fclose(fp);
	return fb;
}

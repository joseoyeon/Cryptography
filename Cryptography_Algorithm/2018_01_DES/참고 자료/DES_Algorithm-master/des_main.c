#include "des.h"
#include "file_i_o.h"

// ��  �� : �����Լ�
// ������ : 18.05.15(ȭ)
void main(void) {
	// ������ ũ�� , ������ �ҷ��������� ��Ʈ��
	int i = 0;
	int fsize = 0;
	FILE_Buffer fb = File_I_O();
	//Ű ���� �Լ� ����
	// ���� Ȯ���� ���� ��¹�
	printf("\n���Ͽ� ��䰪 Ȯ�� \n");
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

	
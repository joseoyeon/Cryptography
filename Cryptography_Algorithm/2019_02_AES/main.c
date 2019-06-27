#include "Reference_AES.h"
#include <intrin.h>
#include <stdio.h>
#pragma intrinsic(__rdtsc)

#define TIME

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

/*


	<!---Read me---!>

	위쪽에 #define TIME 주석 시 CPU Cycle 측정
		   #define TIME 주석 해제 시 전체 걸린 시간 측정

	Main 함수에 To Do 부분에서 자신의 변수 선언 및 함수 호출.

	측정시 Visual Studio를 제외한 무거운 프로그램 모두 종료 후 측정할 것.
	듀얼모니터 사용도 성능에 큰 영향을 미침. ( FHD = 17~23 Cpb, FHD + 4K = 35 ~ 41 Cpb)
	Release, x86 상태에서 실험 할 것.


	Iter	: 10,000,000 ~

	반복 횟수가 많을 수록 정확하게 측정. ( 모든 프로그램이 소모하는 Cycle을 측정하기 때문 )

	시간 얼마 안걸리니
		1. 키 스케줄
		2. 암호화
		4. 키 스케줄 + 암호화
	3개 경우에 대해 Cycle 각각 측정해볼 것.

	CPU마다 차이가 크므로 Ref.에 비해 얼마나 차이나는지 확인할 것.

	Cpb (Cycle Per Byte) 계산을 원할 경우 측정한 Cycle에서 16을 나누면 됨.

*/

int main()
{
	uint32_t pt[4] = { 0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f };
	uint32_t ct[4] = { 0 };
	uint8_t key[16] = { 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f };
	uint64_t start, end, ref_Cycle, usr_Cycle;
	int i;

	uint32_t my_key[4] = { 0x00010203,0x04050607,0x08090a0b,0x0c0d0e0f };
	uint32_t Wkey[44] = { 0 };

	// 비교용 참조 코드, 측정 대상에 따라 aes_keyschedule 함수 위치만 바꿀 것.
	AES_RK aes_rk;
	aes_keyschedule(key, &aes_rk, 128, 0);

	start = __rdtsc();
	for (i = 0; i < 100000000; i++)
	{
		// To Do
		//aes_enc_block(pt, &aes_rk);
		aes_keyschedule(key, &aes_rk, 128, 0);
	}
	end = __rdtsc();
	ref_Cycle = end - start;
	printf("Ref. AES Cycle : %lld\n", ref_Cycle / i);


	// 측정 대상 코드
	//100000000
	// 변수 선언 등 전처리
	//AES_RK aes_rk ..
	Key_Schedule(my_key, Wkey);
	
	start = __rdtsc();
	for (i = 0; i < 100000000; i++)
	{
		// To Do
		//AES_Encrypt(pt, Wkey);
		Key_Schedule(my_key, Wkey);
	}
	end = __rdtsc();
	usr_Cycle = end - start;
	printf("Your AES Cycle : %lld\n", usr_Cycle / i);
	
	return 0;
}
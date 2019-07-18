/*-----2014 국가암호공모전 ( 1-A ) 분야---------*/
/*----------문제 1 (배점 10)------------------*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  char answer[256];
  char ciphertext[] = "MALVVMAFBHBUQPTSOXALTGVWWRG";
  int found = 0;
  long count = strlen(ciphertext), i, j, x, y;

  for (i = 0; i < count; i++)
    ciphertext[i] -= (char) 'A'; // 암호문 정수로 만들어 버림

  for (i = 0; !found && i < 26; i++) { // 들어갈 키가 남아 있으면

//Ci = Mi + Ki mod 26 의 역과정
//Mi = Ci + ki mod 26 을 적용시킨 식이다
//문제에 보면  K1 = K이고, Ki = Mi-1(i>=2)이다. 
// 첫번째 단어만 연산을 따로 해준다. 키를 그냥 넣어주는 거다. 

    x = (ciphertext[0] - i) % 26; 
    if (x < 0) x += 26;
    printf("%c", x + 'A');

    for (j = 1; j < count; j++) {
      y = (ciphertext[j] - x) % 26;
      if (y < 0) y += 26;
      printf("%c", y + 'A');
      x = y;
    }

    printf("\n");
    printf("another key = %c (n or y)? ", i + 'A');
    scanf("%s", answer);
    found = tolower(answer[0]) == 'n';
  }
  return 0;
}
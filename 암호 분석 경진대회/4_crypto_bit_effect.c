/*-------https://nate9389.tistory.com/875----*/
/*해시함수 구현에 영향을 미치는 초기 비트열 나타내기*/

#include <stdio.h> 

int X[16]; 

void n(int N){ 
    if(N < 16){ 
        X[N] ++; 
        return; 
        } 
    
    n(N-1); 
    n(N-16); 
    } 
    
    int main(int argc, char *argv[]) { 
        int i, j; 
        
        for(i = 16; i < 80; i ++){ 
            printf("%d) ", i); 
            for(j = 0; j < 16; j ++) X[j] = 0; 
            n(i); 
            for(j = 0; j < 16; j ++) if(X[j] % 2 == 1) printf("%d ", j); 
            printf("\n"); } 
            return 0; 
        }

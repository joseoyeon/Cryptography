AES 기반 해시함수 구현

2019-07-19 19:38:30 

AES를 기반으로 한 hash 함수에서 충돌쌍 찾기
--------


2019년 암호 분석 경진 대회 4번 문제 입니다

해시 함수의 충돌쌍을 찾고 

라운드 안에서 압축함수 F를 적용할 때 사용하는 인덱스 j 중에서 가장 큰 j 를 찾는 문제 입니다.


> 아래는 해당 문제 입니다

![.](https://github.com/joseoyeon/joseoyeon.github.io/blob/master/_posts/img/20190716_04_AES_hash_2.jpg?raw=true)

0_2019암호경진대회_4번_압축함수-충돌쌍-찾기_문제.PDF 파일안에 있습니다.



> 정리한 내용 입니다

![.](https://github.com/joseoyeon/joseoyeon.github.io/blob/master/_posts/img/20190716_04_AES_hash.jpg?raw=true)



> 진행 내용
1_20190719_해시구현.C

1_해시구현_테스트.jpg


 ____
 참고 사이트


[1] [http://www.kocw.net/home/search/kemView.do?kemId=1320013)

import base64
import re

def stringToBase64(s) : 
    return base64.b64encode(s.encode('utf-8'))
 
def base64ToString(b) :
    return base64.b64decode(b)#.decode('utf-8')

def base32ToString(b) :
    return base64.b32decode(b).decode('utf-8')

def main() : 

    try :
        text = open("FIFA22_IRC.txt","r")
        dec_text = open("FIFA_IRC_DECODE.txt", "w")
    except FileNotFoundError :
        print ("not found file")

# base64 인코딩에서 문자 세트는 [A-Z, a-z, 0-9 및 /]입니다. 나머지 길이가 4보다 작 으면 문자열에 ‘=’문자가 채워집니다.
# ^ ([A-Za-z0-9 /] {4}) *는 문자열이 0 개 이상의 base64 그룹으로 시작 함을 의미합니다.
# ([A-Za-z0-9 /] {4} | [A-Za-z0-9 /] {3} = | [A-Za-z0-9 /] {2} ==) $는 문자열 [A-Za-z0-9 /] {4}, [A-Za-z0-9 /] {3} = 또는 [A-Za-z0-9 /] {2} = =.

    lines = text.readlines()
    for line in lines : 
        try :
            b = base64ToString(line)
            e = base32ToString(b)
        except : 
            print ("pass")
            continue
        print(e)

if __name__ == "__main__" : 
    main()
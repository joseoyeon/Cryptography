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

# base64 ���ڵ����� ���� ��Ʈ�� [A-Z, a-z, 0-9 �� /]�Դϴ�. ������ ���̰� 4���� �� ���� ���ڿ��� ��=�����ڰ� ä�����ϴ�.
# ^ ([A-Za-z0-9 /] {4}) *�� ���ڿ��� 0 �� �̻��� base64 �׷����� ���� ���� �ǹ��մϴ�.
# ([A-Za-z0-9 /] {4} | [A-Za-z0-9 /] {3} = | [A-Za-z0-9 /] {2} ==) $�� ���ڿ� [A-Za-z0-9 /] {4}, [A-Za-z0-9 /] {3} = �Ǵ� [A-Za-z0-9 /] {2} = =.

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
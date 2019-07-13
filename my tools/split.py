# *- encoding: utf-8 -*-
import glob
import sys

def stringToWord(s):
#https://dojang.io/mod/page/view.php?id=2299
#, . �� �����ϰ� ����Ʈ�� �и��Ѵ�.
    return s.replace(",","").replace("'","").split(' ')

def main() :   
    Snowden_eloquent_quotes = "I can't in good conscience allow the U.S. government to destroy privacy, internet freedom and basic liberties for people around the world with this massive surveillance machine they're secretly building"
    quotes = stringToWord(Snowden_eloquent_quotes)

    tmp = []
    path = "FearThePackets/" 
    for word in quotes :
        if word in tmp : continue # not overlap
        try : 
            print (path + word + '.jpg')
            with open(path + word + '.jpg', "rb") as f :
                jpg = f.read() # �ش� ������ ������ ����.
        except:
            print ("pass")
            continue

        try :
            with open("answer.jpg","ab") as ans :
                ans.write(jpg)
        except : print("err")
        f.close() 
        tmp.append(word)
    ans.close()


if __name__ == "__main__" : 
    main()
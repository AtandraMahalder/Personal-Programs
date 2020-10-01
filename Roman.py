#/usr/bin/env python3

#Atandra Mahalder
#09/08/2020

#Convert an integer to a roman number for ranges upto 4000
#Range can be increased by adding symbols after M

#Enter integer
num = int(input())

d = {1:'I', 5:'V', 10:'X', 50:'L', 100:'C', 500:'D', 1000:'M'}
l = True
c = 1000
res = list()
s = 0
while num:
    r = num//c
    if r<4:
        for i in range(0,r):
            res.append(d[c])
            s+=1
    elif s>0 and res[s-1]==d[5*c]:
        res.pop()
        res.append(d[c])
        res.append(d[10*c])
        s+=1
    else:
        res.append(d[c])
        res.append(d[5*c])
        s+=2
    num%=c
    if l:
        c//=2
        l = False
    else:
        c//=5
        l = True

#print roman equivalent
print(''.join(res))

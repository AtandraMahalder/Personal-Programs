#!/usr/bin/env python3
#Atandra Mahalder
#10/01/2020
#Euclid's extended algorithm to reduce labor in Discrete class

cases = int(input())          #Enter cases/number of times you want to calculate Bezout's coefficients and GCD

while cases:
    s0, t0, s1, t1 = 1, 0, 0, 1    
    a, b = input().split(' ')   #Enter case description, two integers a and b
    a = int(a)
    b = int(b)
    if a<b:
        a, b = b, a
    while a%b:
        s0, t0, s1, t1 = s1, t1, s0 - (a//b)*s1, t0 - (a//b)*t1
        a, b = b, a%b
        
    print(f'{b} {s1} {t1}')   #answer will be displayed in form gcd x y where ax + by = gcd and a>b 
    cases-=1    

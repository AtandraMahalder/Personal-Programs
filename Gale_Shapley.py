#!/usr/bin/env python3

#Atandra Mahalder
#08/02/2020
#Primitive Gale Shapely Algorithm for stable matching
#Works with equal number of men and women

#class storing information about a person
class info:
    preferences = list()
    partner = str()
    prop = int()
    def __init__(self, **args):
        if len(args):
            self.preferences = args['preferences']
        self.partner = None
        self.prop = 0
    def __str__(self):
        return f'{self.partner}'

#get number of males and females                
n = int(input('Enter number of men and women: '))

#get information about males and females and store them in dicts
Men = dict()
Women = dict()
print('Enter information about men:')
for i in range(0, n):
    m_name = input(f'Enter name of man #{i+1}: ')
    prefer = input('Enter his preferences in a comma seperated list (highest priority first): ').split(', ')
    Men[m_name] = info(preferences = prefer)
print('Enter information about women:')
for i in range(0, n):
    w_name = input(f'Enter name of woman #{i+1}: ')
    prefer = input('Enter her preferences in a comma seperated list (highest priority first): ').split(', ')
    Women[w_name] = info(preferences = prefer)

#perform the Gale-Shapely Algorithm
rejected = n
c = int(input('''Which type of matching do you want?
1. Male optimal
2. Female optimal
Enter the corresponding number: '''))

#if we have to generate male optimal matchings
if c==1:
    while rejected:
        for man in Men:
            if Men[man].partner is None:
                if Women[Men[man].preferences[Men[man].prop]].partner is None:
                    Men[man].partner = Men[man].preferences[Men[man].prop]
                    Women[Men[man].preferences[Men[man].prop]].partner = man
                    rejected-=1
                elif Women[Men[man].preferences[Men[man].prop]].preferences.index(Women[Men[man].preferences[Men[man].prop]].partner) > Women[Men[man].preferences[Men[man].prop]].preferences.index(man):
                    Men[Women[Men[man].preferences[Men[man].prop]].partner].prop+=1
                    Men[Women[Men[man].preferences[Men[man].prop]].partner].partner = None
                    Women[Men[man].preferences[Men[man].prop]].partner = man
                    Men[man].partner = Men[man].preferences[Men[man].prop]
                else:
                    Men[man].prop+=1
#if we have to generate female optimal matchings
else:
    while rejected:
        for woman in Women:
            if Women[woman].partner is None:
                if Men[Women[woman].preferences[Women[woman].prop]].partner is None:
                    Women[woman].partner = Women[woman].preferences[Women[woman].prop]
                    Men[Women[woman].preferences[Women[woman].prop]].partner = woman
                    rejected-=1
                elif Men[Women[woman].preferences[Women[woman].prop]].preferences.index(Men[Women[woman].preferences[Women[woman].prop]].partner) > Men[Women[woman].preferences[Women[woman].prop]].preferences.index(woman):
                    Women[Men[Women[woman].preferences[Women[woman].prop]].partner].prop+=1
                    Women[Men[Women[woman].preferences[Women[woman].prop]].partner].partner = None
                    Men[Women[woman].preferences[Women[woman].prop]].partner = woman
                    Women[woman].partner = Women[woman].preferences[Women[woman].prop]
                else:
                    Women[woman].prop+=1

#printing requested matchings
print('The requested matchings are (male, female):')
for i in Men:
    print(f'({i}, {Men[i]})')

import random


def getChance():
    return random.random()

def getResult(x, x_sym, banana_sym, cherry_sym, p_sym):
    xChance = .5
    bananaChance = .75
    cherryChance = .9
    pChance = 1
    if x < xChance:
        return x_sym
    elif x < bananaChance:
        return banana_sym
    elif x < cherryChance:
        return cherry_sym
    else:
        return p_sym
    

def getSpin(x, y, z):
    print("########################")
    first = x
    second = y
    third = z
    reels = 3
    depth = 5
    for i in range(depth):
        print(first[i], second[i], third[i])

x = getChance()
y = getChance()
z = getChance()


        


print("Hello, Welcome to my slot machine")
print("Please enter an amount of money to deposit")
# x = input("Money to deposit: ")

print("Money deposited: ", x )

x_sym = ["#   #", " # # ", "  #  ", " # # ", "#   #"]
for symbol in x_symbol:
    print(symbol)

banana_sym = ["#    ", " ##  ", "  ###", " ##  ", "##   "]
for symbol in banana_symbol:
    print(symbol)

cherry_sym = ["   # ", "  #  ", " ### ", "#   #", " ### "]
for symbol in cherry_symbol:
    print(symbol)

p_sym = ["#####", "#   #", "#####", "#    ", "#    "]
for symbol in p_symbol:
    print(symbol)



first = getResult(x, x_sym, banana_sym, cherry_sym, p_sym)

second = getResult(x, x_sym, banana_sym, cherry_sym, p_sym)

third = getResult(x, x_sym, banana_sym, cherry_sym, p_sym)

getSpin()
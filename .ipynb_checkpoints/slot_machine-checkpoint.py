import random

balance = 100
bet = 10



def getResult():
    """This function return an int determining which list is output.
    """
    xChance = .35
    bananaChance = .55
    cherryChance = .8
    pChance = 1
    x_sym = ["#   #", " # # ", "  #  ", " # # ", "#   #"]
    banana_sym = ["#    ", " ##  ", "  ###", " ##  ", "##   "]        
    cherry_sym = ["   # ", "  #  ", " ### ", "#   #", " ### "]
    p_sym = ["#####", "#   #", "#####", "#    ", "#    "]
    x = random.random()
    if x < xChance:
        return x_sym
    elif x < bananaChance:
        return banana_sym
    elif x < cherryChance:
        return cherry_sym
    else:
        return p_sym


    

def Spin():
    """This function gets the result, prints the outputs, then returns ints to represent the outcome"""
    print("########################")
    first = getResult()
    second = getResult()
    third = getResult()
    # ok so how does printing work, we need 3 columns and 5 rows
    # cant we just run print 5 times formatted so each row prints?
    for i in range(5):
        print(f"| {first[i]} | {second[i]} | {third[i]} |")
    print("########################")
    print(first[0])

    a = 0
    b = 0
    c = 0
    if (first[0] == "#   #"):
        a = 1
    elif (first[0] == "#   #"):
        a = 2
    elif (first[0] == "   # "):
        a = 3
    else:
        a = 4

    
    if (second[0] == "#   #"):
        b = 1
    elif (second[0] == "#   #"):
        b = 2
    elif (second[0] == "   # "):
        b = 3
    else:
        b = 4

    if (third[0] == "#   #"):
        c = 1
    elif (third[0] == "#   #"):
        c = 2
    elif (third[0] == "   # "):
        c = 3
    else:
        c = 4
    
    
    return a, b, c
        



result = Spin()
print(result)



# ok so now, we need to take our tuple and run a bunch of if else statements? or can we use a dict?
# no we will use checking of how many in the tuple

# ok so now lets determine payouts
# should we do that in this function? no lets do it in another and just return an integer
    # and a string
x_win = "Ooooohh! XXX, that's hot"
x_miss = "Close, but no cigar"

banana_win = "Woah! That's bananas!"
banana_miss = "Baaah. Banana baskets benefit bigly"

cherry_win = "Cherry on top! Big win"
cherry_miss = "Almost!"

p_win = "Pushing P. Nice"
p_miss = "PP isnt what we wanted, but its still a big win"

none_lose = "Ahhh, so close. Better luck next time"

# x, banana, cherry, p

def checker(result):
    a = result.count(1)
    b = result.count(2)
    c = result.count(3)
    d = result.count(4)

    if a >= 2:
        if a == 3:
            return x_win, 4
        else:
            return x_miss, 2
    elif b >= 2:
        if b == 3:
            return banana_win, 5
        else:
            return banana_miss, 3
    elif c >= 2:
        if c == 3:
            return cherry_win, 6
        return cherry_miss, 4
    elif d >= 2:
        if d == 3:
            return p_win, 7
        return p_miss, 5
    return none_lose, 0

# ok so lets see if this works

result = Spin()
final = checker(result)
print(final)
    
        
            
            

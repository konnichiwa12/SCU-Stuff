#Name: Dillon Kanai
#Date: 9/29/20
#Lab 2
#main.py

from vacuum import *
import random
if __name__ == "__main__":
    room = Room()
    #get input from user, state of the environment
    L = int(input("Dirty(1) or clean(0) for left side: "))
    R = int(input("Dirty(1) or clean(0) for right side: "))
    P = int(input("Right(1) or Left(0) for inital robot position: "))
    #create list and score to print at the end
    list = []
    score = 0
    #initialize choice variable
    choice = -1
    room.init(L, R, P)

    finished = False
    #check if floor is clean, if it is terminate automatically
    finished = room.scan()
    #loop until floor is clean
    while(not finished):
        print("-------------------------------------------------------")
        #check floor
        room.checkfloor()
        #Select Action: Go left(0), Go right(1), Clean(2)
        choice = int(random.random()*3)
        score += 1
        #call function based on the choice variable
        if (choice == 0):
            room.left()
            list.append("Left")
        elif (choice == 1):
            room.right()
            list.append("Right")
        else:
            room.clean()
            list.append("Clean")
        finished = room.scan()

    #alert user that floor is clean, print list and score
    print("Floor is now Clean!")
    print(score)
    print(list)


        



    
    

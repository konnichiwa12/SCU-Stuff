#Name: Dillon Kanai
#Date: 9/29/20
#Lab 2
#vacuum.py


#1 means floor is dirty
#0 means floor is clean
#state[0] is the left tile state
#state[1] is the right tile state
#state[2] is the position robot is in: 0 = left, 1 = right

#Room class
class Room:
    #acts like a constructor, called by the main function. Creates the state array that keeps track of the environment
    def init(self, L, R, P):
        self.state = [L, R, P]
    
    #will check both tiles and the robot's position, print statements based on situation
    def checkfloor(self):
        if (self.state[2]):
            print("You are on the right!")
            if (self.state[1]):
                print("The floor is dirty!")
            else:
                print("The floor is clean!")
        else:
            print("You are on the left!")
            if (self.state[0]):
                print("The floor is dirty!")
            else:
                print("The floor is clean!")
    
    #similar to checkfloor(), except it will return true or false, which will either cause the while loop in main terminate or to keep looping
    def scan(self):
        if (self.state[0] == 1):
            return False
        if (self.state[1] == 1):
            return False
        return True
    
    #might change state array, move the robot to the left tile, moving left while already on the left tile will do nothing, change state array
    def left(self):
        if (self.state[2] == 0):
            print("You are already on the left tile!")
        else:
            print("You are now on the left side!")
            self.state[2] = 0

    #might change state array, move the robot to the right tile, moving right while already on the right tile will do nothing, change state array
    def right(self):
        if (self.state[2] == 1):
            print("You are already on the right tile!")
        else:
            print("You are now on the right side!")
            self.state[2] = 1
    
    #might change state array, clean current tile, if tile is already clean nothing will happen
    def clean(self):
        pos = self.state[2]
        if (self.state[pos] == 1):
            print("Tile is now clean!")
            self.state[pos] = 0
        else:
            print("Tile is already clean!")
#Name : Dillon Kanai
#Date 9/24/2020
#Title: Lab1 - Rectangle
#Description: this file takes input from user and computes the area of a rectangle

#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
#Greet User
echo "Hi $user! There are $numusers users logged on."
#Check username
if [ $user = "dkanai" ]
then
	echo "Now you can proceed!" #Allow correct user to use code
else
	echo "Check who logged in!" #Don't allow incorrect users to use code
	exit 1 #quit code
fi

response="Yes"
#run loop while response variable equals "Yes"
while [ $response != "No" ]
do 
	echo "Enter height of rectangle:"
	read height #recieve height input from user
	echo "Enter width of rectangle:"
	read width #receive width input from user
	area=`expr $height \* $width`
	#calculate area using input and print
	echo "The area of the rectangle is $area"
	#ask user if he/she wants to use code again
	echo "Would you like to repeat for another rectangle [Yes/No]?"
	read response

done

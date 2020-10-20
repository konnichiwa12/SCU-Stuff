#Name: Dillon kanai
#Date: 9/24/2020
#Title: Lab1 - Circle
#Description: Takes input from the user to compute the area of a circle.


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
echo "Hi $user! There are $numusers users logged on."
#check if user is correct
if [ $user = "dkanai" ]
then
	echo "Now you can proceed!" #allow correct user to use code
else
	echo "Check who logged in!" #don't allow incorrect user to use code
	exit 1
fi

response="Yes"
while [ $response != "No" ] #run while loop while response equals yes
do 
	echo "Enter the radius of circle:" 
	read radius #receive input for radius variable
	area=`expr "3.1415 * $radius * $radius" | bc` #calculate area of circle
	echo "The area of the circle is $area" #print
	#ask user if he/she wants to use code again
	echo "Would you like to repeat for another circle [Yes/No]?"
	read response #receive input

done

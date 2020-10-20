//
//  Part3.cpp
//  coen79Lab1
//
//  Created by dkanai on 1/10/20.
//  Copyright © 2020 SCU. All rights reserved.
//

#include "Part3.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main(int argc, const char * argv[]){//this code will take words from a file, then print out all words >10 letters long
    cout << "Hello\n";
    if ((argc != 2)){//check to make sure a file name was given
        cout << "File name not given/too many file names given\n";
        return 1;
    }
    string thing = "";
    string temp; //will act as temp string
    string filename(argv[1]);//get name of file (look at todays notes)
    ifstream in_file;//prepare code to read file
    in_file.open(filename);//open file
    cout << "starting for loop\n";
    while(in_file && in_file.peek() != EOF){//while there is still content to be read, copy each word into temp
	thing = "";
	getline(in_file, temp, ' ');	
	for (int i = 0; i < temp.length(); i++){ //for each letter
			if (isalnum(temp[i])){ //check if char is a letter
				thing += toupper(temp[i]);//convert it to upper case and add to thing
			}
		}
		if (thing.length() >= 10){//after processing, if the word is >10 letters long, print it
			cout << thing << "\n";
		}
	}
    return 0;
}

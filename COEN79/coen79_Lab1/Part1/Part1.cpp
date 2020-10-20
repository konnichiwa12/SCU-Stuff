//
//  Part1.cpp
//  coen79Lab1
//
//  Created by dkanai on 1/10/20.
//  Copyright © 2020 SCU. All rights reserved.
//
#include <iostream>
using namespace std;
#include "Part1.hpp"
int main(int argc, const char* argv[]){//this will take input from the user and count how many letters/numbers and non-letters the word has
    string word = "";
    getline(cin, word);//get input from user
    int returnthis = 0, returnthis2 = 0;//counters for letters and non-letters and spaces
    int length = word.length();
    for (int i = 0; i < length; i++){
        if (word[i] != ' '){//go through each letter/element and count
            if (isalnum(word[i])){//letters and numbers
                returnthis++;
            }
            else{//everything else except spaces
            returnthis2++;
            }
        }
    }
        cout <<"This string has " << returnthis << " alphanumeric characters and " << returnthis2 << " non-alphanumeric characters.";//print results
        return 0;
}

//
//  mystring.cpp
//  coen79_Lab5
//
//  Created by dkanai on 2/7/20.
//  Copyright © 2020 SCU. All rights reserved.
//

#include <cctype>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "mystring.h"
using std::cin;
using std::cout;
namespace coen79_lab5{
    // CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR
    string::string(const char str[ ]){//constructor, parameter is an array of characters
        current_length = strlen(str);
        allocated = current_length + 1;
        characters = new char[allocated];
        strncpy(characters, str, current_length);
    }
    string::string(char c){//constructor, parameter is a single character
        current_length = 1;
        characters = NULL;
        allocated = 2;
        characters = new char[allocated];
        characters[0] = c;
        characters[current_length] = '\0';
    }
    string::string(const string& source){//copy constructor
        current_length = source.current_length;
        allocated = current_length + 1;
        characters = new char[allocated];
        for (int i = 0; i < source.current_length; i++){
            characters[i] = source.characters[i];
        }
    }
    string::~string( ){//destructor
        delete[] characters;
        characters = NULL;
        allocated = 0;
        current_length = 0;
    }

    // MODIFICATION MEMBER FUNCTIONS
    void string::operator +=(const string& addend){//add string to object that called this function
        if (current_length + strlen(addend.characters) > allocated){
            reserve(current_length + addend.current_length + 1);
        }
        for(int i = 0; i < strlen(addend.characters); i++){
            characters[current_length] = addend.characters[i];
            current_length++;
        }
        return;
    }
    void string::operator +=(const char addend[ ]){//add character array to the object that called this function
        if(current_length + strlen(addend) > allocated){
            reserve(current_length + strlen(addend) + 1);
        }
        for (int i = 0; i < strlen(addend); i++){
            characters[current_length] = addend[i];
            current_length++;
        }
    }
    void string::operator +=(char addend){//add character to object to *this
        if (current_length + 1 > allocated){
            reserve(current_length + 1);
        }
        characters[current_length] = addend;
        current_length++;
        characters[current_length] = '\0';
    }
    void string::reserve(size_t n){//increase space of *this.characters
        char *new_characters;
        if (n == allocated){
            return;
        }
        if (n < current_length + 1){
            n = current_length + 1;
        }
        new_characters = new char[n];
        if(characters != NULL){
            strncpy(new_characters, characters, n);
            delete[] characters;
        }
        characters = new_characters;
        allocated = n + 1;
    }
    string& string::operator =(const string& source){//set *this equal to source
        if(this == &source){
		return *this;	
	}
        if(source.current_length > allocated){
            reserve(source.current_length + 1);
        }
        for(int i = 0; i < source.current_length; i++){
            characters[i] = source.characters[i];
        }
        current_length = source.current_length;
        characters[current_length] = '\0';
        return *this;
    }
    void string::insert(const string& source, unsigned int position){//insert string at characters[position]
    	assert(position <= current_length);
        reserve(source.current_length + current_length);
        char storage[current_length - position];
        strncpy(storage, characters + position, current_length - position);
        strncpy(characters + position + source.current_length, storage, current_length - position);
        strncpy(characters + position, source.characters, source.current_length);
        current_length += source.current_length;
    }
    void string::dlt(unsigned int position, unsigned int num){//delete num characters starting from characters[position]
        assert(position + num <= current_length);
        for(int i = position; i < current_length + position; i++){
            characters[i] = characters[i + num];
        }
        current_length -= num;
        characters[current_length] = '\0';
    }
    void string::replace(char c, unsigned int position){//change character *this->characters[position] to c
        assert(position < current_length);
        characters[position] = c;
        return;
    }
    void string::replace(const string& source, unsigned int position){//change characters starting from *this->characters[position] to source.characters
        assert(position + source.current_length <= current_length);
        strncpy(characters + position, source.characters, source.current_length);
        return;
    }

    // CONSTANT MEMBER FUNCTIONS
    size_t string::length( ) const {//return current_length
        return current_length;
    }
    char string::operator [ ](size_t position) const{//overload [] operator
        assert(position < length());
        char temp;
        temp = characters[position];
        return temp;
    }
    int string::search(char c) const{//search for character c in *this->characters
        for (int i = 0; i < current_length; i++){
            if (characters[i] == c){
                return i;
            }
        }
        return -1;
    }
    int string::search(const string& substring) const{//search for a string in *this->characters
        int i = 0;
        for(i = 0; i + substring.current_length < current_length + 1; i++){
            if(strncmp(characters + i, substring.characters, substring.current_length) == 0){
                return i;
            }
        }
        return -1;
    }
    unsigned int string::count(char c) const{//count how many characters in *this->characters equals character c
        int count = 0;
        for (int i = 0; i < current_length; i++){
            if (characters[i] == c){
                count++;
            }
        }
        return count;
    }

    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source){//overload << operator
        for(int i = 0; i < source.current_length; i++){
            outs << source.characters[i];
        }
        return outs;
    }
    bool operator ==(const string& s1, const string& s2){//overload == operator
        if(s1.current_length != s2.current_length){
            return false;
        }
        if(strncmp(s1.characters, s2.characters, s1.current_length) == 0){
            return true;
        }
        return false;
    }
    bool operator !=(const string& s1, const string& s2){//overload != operator
        if (s1 == s2){
            return false;
        }
        return true;
    }
    bool operator > (const string& s1, const string& s2){//overload > operator
        if (strncmp(s1.characters, s2.characters, s1.current_length) > 0){
            return true;
        }
        return false;
    }
    bool operator < (const string& s1, const string& s2){//overload < operator
        if (strncmp(s1.characters, s2.characters, s1.current_length) < 0){
            return true;
        }
        return false;
    }
    bool operator >=(const string& s1, const string& s2){//overload > = operator
        if (strncmp(s1.characters, s2.characters, s1.current_length) >= 0){
            return true;
        }
        return false;
    }
    bool operator <=(const string& s1, const string& s2){//overload <= operator
        if (strncmp(s1.characters, s2.characters, s1.current_length) <= 0){
            return true;
        }
        return false;
    }
    string operator +(const string&s1, const string& s2){//overload + operator
        string temp;
        temp += s1;
        temp += s2;
        return temp;
    }
    string operator +(const string& s1, const char addend[ ]){//overload + operator
        string temp(s1);
        temp += addend;
        return temp;
    }
    std::istream& operator >> (std::istream& ins, string& target){//overload > operator
        char next;
        target = "";
        while(!ins.eof() && isspace(ins.peek())){
            ins.ignore();
            }
        while(!ins.eof() && !isspace(ins.peek())){
            ins >> next;
	    target += next;
        }
        return ins;
    }

}

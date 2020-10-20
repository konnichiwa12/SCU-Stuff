//
//  sequence1.cpp
//  coen79Lab3
//
//  Created by dkanai on 1/24/20.
//  Copyright © 2020 SCU. All rights reserved.
//

#include "sequence1.h"
#include <cctype>       // Provides toupper
#include <iostream>     // Provides cout and cin
#include <cstdlib>      // Provides EXIT_SUCCESS
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;

namespace coen79_lab3{
    sequence::sequence(){//constructor, initialize private variables
        this->length = 0;
        this->iterator = 0;
    }
    void sequence::start(){//put iterator at the first element
        iterator = 0;
        return;
    }
    void sequence::end(){//put the iterator at the spot after the last element
        iterator = length - 1;
    }
    void sequence::last(){//put the iterator at the end of the array
        iterator = CAPACITY - 1;;
    }
    void sequence::advance(){//move iterator forward one
        assert(is_item() == true);
        if (iterator < length){
            iterator++;
        }
        return;
    }
    void sequence::retreat(){//move iterator back one
        if (iterator != 0){
            iterator--;
        }
        return;
    }
    void sequence::insert(const value_type& entry){//insert an element into the array at the location right before iterator
        assert(size() < CAPACITY);
        int i;
        if (iterator > length){
            iterator = 0;
        }
        for (i = length; i > iterator; i--){
                bag[i] = bag[i - 1];
        }
        bag[iterator] = entry;
        length++;
    }
    void sequence::attach(const value_type& entry){//insert an element into the array ar the location right after the iterator
        assert(size() < CAPACITY);
        if (!is_item()){
            bag[length] = entry;
        }
        else{
            for (int i = length; i > iterator + 1; i--){
                bag[i] = bag[i - 1];
            }
            bag[iterator + 1] = entry;
            iterator++;
        }
        length++;
    }
    void sequence::remove_current(){//return the value at iterator's address
        assert(is_item() == true);
        for(int i = iterator + 1; i < length; i++){
            bag[i - 1] = bag[i];
        }
        length--;
    }
    void sequence::insert_front(const value_type& entry){//insert an item at the front of the array
        assert(size() < CAPACITY);
        iterator = 0;
        insert(entry);
        return;
    }
    void sequence::attach_back(const value_type& entry){//insert an item after the last element of the array
        assert(size() < CAPACITY);
        iterator = length;
        bag[length] = entry;
        length++;
        return;
    }
    void sequence::remove_front(){//remove the first array element
        assert(is_item() == true);
        int i = (int)length - 1;
        for(i = 0; i < length; i++){
            bag[i] = bag[i + 1];
        }
        length--;
    }
    void sequence::operator +=(const sequence& rhs){//add elements of rhs to the lhs bag
        assert((length + rhs.length) < CAPACITY);
        int temp = rhs.length;
        for (int i = 0; i < temp; i++){
            bag[length] = rhs.bag[i];
            length++;
        }
    }
    
    sequence::size_type sequence::size() const{//return the number of element in array
        return length;
    }
    bool sequence::is_item() const{//check if the iterator's address has a value
        if (iterator < length){
            return true;
        }
        return false;
    }
    sequence::value_type sequence::current() const{//return the value at iterator's address
        assert(is_item() == true);
        return bag[iterator];
    }
    sequence::value_type sequence::operator [](int index) const{//return item at bag[index]
        assert(index < length);
        return bag[index];
    }
    double sequence::mean() const{//return the mean of all values
        value_type sum = 0;
        
        for (int i = 0; i < length; i++){
            sum += bag[i];
        }
        return sum/length;
    }
    double sequence::standardDeviation() const {//return standard deviation
        double avg = this->mean();
        double temp = 0;
        for (int i = 0; i < this->length; i++){
            temp += pow(this->bag[i] - avg, 2);
        }
        return sqrt(temp/this->length);
    }
}
coen79_lab3::sequence::value_type coen79_lab3::summation(const coen79_lab3::sequence &s){//return the sum
    coen79_lab3::sequence s2;
    s2 += s;
    coen79_lab3::sequence::value_type sum = 0;
    for (int i = 0; i < s2.size(); i++){
        sum += s2.current();
        s2.advance();
    }
    return sum;
}
coen79_lab3::sequence coen79_lab3::operator +(const coen79_lab3::sequence& lhs, const coen79_lab3::sequence& rhs){//add both bags together and return it
    assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
    coen79_lab3::sequence temp;
    temp += lhs;
    temp += rhs;
    return temp;
}


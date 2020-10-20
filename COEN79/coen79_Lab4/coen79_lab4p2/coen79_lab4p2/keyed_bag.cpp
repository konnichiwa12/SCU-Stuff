//
//  keyed_bag.cpp
//  coen79_lab4p2
//
//  Created by dkanai on 2/5/20.
//  Copyright © 2020 SCU. All rights reserved.
//
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include "keyed_bag.h"
using namespace std;
namespace coen79_lab4{
    keyed_bag::keyed_bag(){//constructor, set used to 0
        used = 0;
        return;
    }
    void keyed_bag::erase(){//set used to 0, left over values wont matter because used will not let iterators past the index used represents
        for (int i = 0; i < CAPACITY; i++){
            keys[i] = '\0';
            data[i] = 0;
        }
        used = 0;
        return;
    }
    bool keyed_bag::erase(const key_type& key){//erase a specific value in the arrays, return true if found, return false if it wasnt
        if(has_key(key)){
            for (int i = 0; i < used; i++){
                if (keys[i] == key){
                    for (int j = i; j< used - 1; j++){
                        keys[j] = keys[j + 1];
                        data[j] = data[j + 1];
                    }
                    used--;
                    return true;
                }
            }
        }
        return false;
    }
    void keyed_bag::insert(const value_type& entry, const key_type& key){//insert a new value in the arrays
        assert((size() < CAPACITY)&&(!has_key(key)));
        data[used] = entry;
        keys[used] = key;
        used++;
    }
    void keyed_bag::operator +=(const keyed_bag& addend){//overload += operator, returned keyed_bag should include all elements of this->bag and addend's bags
        assert((size() + addend.size() <= CAPACITY)&&(!hasDuplicateKey(addend)));
        for (int i = 0; i < addend.size(); i++){
            if (!this->has_key(addend.keys[i])){
                this->insert(addend.data[i], addend.keys[i]);
            }
        }
    }
    bool keyed_bag::has_key(const key_type& key) const{//return true if the specified key is found in keys array, false if not found
        for (int i = 0; i < used; i++){
            if (keys[i] == key){
                return true;
            }
        }
        return false;
    }
    keyed_bag::value_type keyed_bag::get(const key_type& key) const{//return value in data[i] if keys[i] matches specified key
        assert(has_key(key) == true);
        for (int i = 0; i < used; i++){
            if (keys[i] == key){
                return data[i];
            }
        }
        return 0;
    }
    keyed_bag::size_type keyed_bag::size() const{//return used
        return used;
    }
    keyed_bag::size_type keyed_bag::count(const value_type& target) const{//return how many duplicates of target there are in data[i]
        size_type count = 0;
        for (int i = 0; i < used; i++){
            if (data[i] == target){
                cout << "yee\n";
                count++;
            }
        }
        return count;
    }
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{//return true if there is a duplicate value shared between keys array and otherBag.keys array
        for (int i = 0; i < otherBag.used; i++){
            if(has_key(otherBag.keys[i])){
                    return true;
            }
        }
        return false;
    }
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){//NON MEMBER FUNCTION: return a keyed_bag that has all elements of b1 and b2
        assert((b1.size() + b2.size() <= keyed_bag::CAPACITY)&&(!b1.hasDuplicateKey(b2)));
        keyed_bag temp;
        temp += b1;
        temp += b2;
        return temp;
    }
    
}


#include <iostream>
#include <cassert>
#include "random.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2{
    rand_gen::rand_gen(int newSeed, int mult, int incr, int mod){//constructor, set all values to parameters
        multiplier = mult;
        seed = newSeed;
        increment = incr;
        modulus = mod;
    }
    void rand_gen::set_seed(int newSeed){//set seed as parameter newSeed
        seed = newSeed;
        return;
    }
    int rand_gen::next(){//generate a new number and designate it as "newnum", set it as the new seed using the set_seed function, return the new value
        int newnum = ((multiplier * seed + increment) % modulus);
        set_seed(newnum);//call upon public function above
        return newnum;
    }
    void rand_gen::print_info() const{//print out all private variables of object
        cout << "Seed: " << seed << "\n";
        cout << "Multiplier: " << multiplier << "\n";
        cout << "Increment: " << increment << "\n";
        cout << "Modulus: " << modulus << "\n";
        }
}

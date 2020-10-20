//
//  Part2.cpp
//  coen79Lab1
//
//  Created by dkanai on 1/10/20.
//  Copyright © 2020 SCU. All rights reserved.
//

#include "Part2.hpp"
#include <iostream>
#include <iomanip>
using namespace std;
int main(int argc, const char* argv[]){//print out numbers in a certain pattern
    string ascend = "0123456789";//initialize variables
    string descend = "9876543210";

    for (int i = 0; i < 5; i++){//print variables with correct spacing using setw()
        cout << setw(9 + 2*i) << ascend << setw(19 + 4*i) << descend << "\n";
    }
    return 0;
}
    
    

//
//  main.cpp
//  coen79Lab1
//
//  Created by dkanai on 1/10/20.
//  Copyright © 2020 SCU. All rights reserved.
//

#include <iostream>
#include "test.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int i = 1;
    int j = 2;
    
    i++;
    int k = i+j;
    
    std::cout << "k is " << k << std::endl;
    print_hello();
    return 0;
}

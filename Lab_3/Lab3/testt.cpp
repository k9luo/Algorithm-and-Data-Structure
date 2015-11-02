//
//  testt.cpp
//  Lab3
//
//  Created by 锴 罗 on 2015-03-10.
//  Copyright (c) 2015 锴 罗. All rights reserved.
//

#include <stdio.h>
#include "Tester.h"
#include "Leftist_node.h"
#include "Leftist_heap_tester.h"
#include "Leftist_heap.h"
#include "Exception.h"
#include "ece250.h"
#include <string>

int main() {
    std::string hh;
    Leftist_heap<int> heapp;
    heapp.push(3);
    heapp.push(1);
    heapp.push(6);
    heapp.push(6);
    heapp.push(9);
    std::cout<<heapp<<std::endl;
    std::cout<<"count 6: "<<std::endl;
    std::cout<<heapp.count(6)<<std::endl;
    std::cin >> hh;
    
    
    return 0;
}

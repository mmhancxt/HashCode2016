//
//  main.cpp
//  HashCode2016
//
//  Created by Liang LIU on 16/01/2016.
//  Copyright (c) 2016 Liang LIU. All rights reserved.
//
#include "Piano.h"
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

void test_boost()
{
    std::string s = "a,b,c,d,e";
    std::vector<std::string> fields;
    boost::split(fields, s, boost::is_any_of(","));
    std::copy(fields.begin(), fields.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "We are the champion!\n";
    Piano p("Yamaha");
    p.PrintMark();
    auto c = 11;
    std::cout << "c++" << c << std::endl;


    test_boost();

    return 0;
}

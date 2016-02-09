//
//  main.cpp
//  HashCode2016
//
//  Created by Liang LIU on 16/01/2016.
//  Copyright (c) 2016 Liang LIU. All rights reserved.
//
#include <iostream>
#include "PaintFacade.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    FacadePrinter s;
//    s.PrintWithHorizon();
    // logo : 68
    // right_angle: 124
    // learn_and_teach : 3225
    
//    s.ReadData("logo.in");      // 64
//    s.ReadData("right_angle.in"); // 92
    s.ReadData("learn_and_teach.in");   // 3486
    s.PrintImage();
    return 0;
}

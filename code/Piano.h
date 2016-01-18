//
//  Piano.h
//  HashCode2016
//
//  Created by Liang LIU on 16/01/2016.
//  Copyright (c) 2016 Liang LIU. All rights reserved.
//

#ifndef __HashCode2016__Piano__
#define __HashCode2016__Piano__

#include <iostream>

class Piano
{
private:
    std::string mark;
public:
    Piano(std::string name) : mark(name) {}
    void PrintMark();
};

#endif /* defined(__HashCode2016__Piano__) */

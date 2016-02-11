//
//  main.cpp
//  HashCode2016
//
//  Created by Liang LIU on 16/01/2016.
//  Copyright (c) 2016 Liang LIU. All rights reserved.
//
#include <iostream>
#include "InputLoader.h"
#include "OrderFirst.hpp"
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
	InputLoader loader;
	loader.LoadFromFile(argv[1]);
	OrderFirstDistribution distribute(loader);
	distribute.run();
	return 0;
}


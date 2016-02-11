#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <map>

using namespace std;

struct Product
{
	int id;
	int weight;
};

struct Position
{
	int x;
	int y;
};

struct WareHouse
{
	Position position;
	map<int, int> availableProducts;

};

struct Order
{
	Position deliverPosition;
	map<int, int> purchasedProducts;
};
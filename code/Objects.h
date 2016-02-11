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

enum Status
{
    UNPROCESSED,
    INDELIVERING,
    COMPLETED
};

struct Order
{
    Stauts staus;
	Position deliverPosition;
	map<int, int> purchasedProducts;
};
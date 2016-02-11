#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <map>
#include <math.h>

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
	int id;
	Position position;
	map<int, int> availableProducts;
	bool containsProduct(int productId) {
		return availableProducts.find(productId) != availableProducts.end();
	}
};

enum Status
{
    UNPROCESSED,
    INDELIVERING,
    COMPLETED
};

struct Order
{
	int id;
    Status status;
	Position deliverPosition;
	map<int, int> purchasedProducts;
};

enum DroneStatus
{
    FLY,
    WAIT,
    INORDER,
    INWAREHOUSE
};

struct Drone
{
    Drone(Position p)
    {
		id = 0;
        load = 0;
        position.x = p.x;
        position.y = p.y;
        status = INWAREHOUSE;
        nextUsableTurn = 0;
        productId = 0;
        productCount = 0;
    }
	int id;
    int load;
    int nextUsableTurn;
    DroneStatus nextAction;
    int productId;
    int productCount;
    DroneStatus status;
    Position position;
    map<int, int> goods;
};

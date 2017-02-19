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
		return availableProducts[productId] > 0;
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
    Drone(Position p, int i)
    {
		id = i;
        load = 0;
        position.x = p.x;
        position.y = p.y;
        status = INWAREHOUSE;
        nextUsableTurn = 0;
    }
	int id;
    int load;
    int nextUsableTurn;
    DroneStatus nextAction;
    DroneStatus status;
    Position position;
    map<int, int> goods;
};

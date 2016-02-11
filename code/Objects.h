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
	int id;
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
        load = 0;
        position.x = p.x;
        position.y = p.y;
        status = INWAREHOUSE;
    }
    int load;
    DroneStatus status;
    Position position;
    map<int, int> goods;
};
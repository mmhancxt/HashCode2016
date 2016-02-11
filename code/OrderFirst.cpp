#include "OrderFirst.hpp"
#include "InputLoader.h"
#include "Objects.h"
#include <iostream>
#include <map>
using namespace std;

void load(int drone, int warehouse, int product_type, int count)
{
	cout << drone << ' ' << 'L' << warehouse << ' ' << product_type << ' ' << count << endl;
}

void unload(int drone, int warehouse, int product_type, int count)
{
	cout << drone << ' ' << 'U' << warehouse << ' ' << product_type << ' ' << count << endl;
}

void deliver(int drone, int order, int product_type, int count)
{
	cout << drone << ' ' << 'D' << order << ' ' << product_type << ' ' << count << endl;
}

void wait(int drone, int turn)
{
	cout << drone << ' ' << 'W' << turn << endl;
}

struct PlanePlan {
	int available_turn;
	Position available_pos;
	PlanePlan() {
		available_turn = 0;
		available_pos.x = 0;
		available_pos.y = 0;
	}
};

void order_first()
{
	multimap< int, PlanePlan > schedule_status;
	// warehouses[0]
}

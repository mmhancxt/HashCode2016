//
//  Common.h
//  HashCode2016
//
//  Created by Liang LIU on 11/02/2016.
//  Copyright © 2016 Liang LIU. All rights reserved.
//

#ifndef Common_h
#define Common_h
#include "code/InputLoader.h"
#include "code/Objects.h"
#include <cmath>
#include <iostream>
static const int CalculateEula(const Position& a, const Position& b)
{
    return static_cast<int>(sqrt((a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y)) + 0.5);
}

static WareHouse* GetNearestWareHouse(InputLoader& loader, Drone& drone, const int productId)
{
    int min_distance = INT_MAX;
    int houseId = 0;
    for (WareHouse& house : loader.warehouses)
    {
        if (house.containsProduct(productId))
        {
            int distance = CalculateEula(drone.position, house.position);
            if (distance < min_distance)
            {
                min_distance = distance;
                houseId = house.id;
            }
        }
    }
    return &loader.warehouses[houseId];
}

static Order* GetNearestOrder(InputLoader& loader, const Drone& drone)
{
    int min_distance = INT_MAX;
    int orderId = -1;
    for (Order& order : loader.orders)
    {
        bool hasProductToDelivery = false;
        for (auto it = order.purchasedProducts.begin(); it != order.purchasedProducts.end(); it++)
        {
            if (drone.goods.find(it->first) != drone.goods.end())
            {
                hasProductToDelivery = true;
                break;
            }
        }
        if (hasProductToDelivery)
        {
            int distance = CalculateEula(drone.position, order.deliverPosition);
            if (distance < min_distance)
            {
                min_distance = distance;
                orderId = order.id;
            }
        }
    }
    if (orderId != -1)
    {
        return &(loader.orders[orderId]);
    }
    return nullptr;
}

void load(int drone, int warehouse, int product_type, int count)
{
	std::cout << drone << ' ' << "L " << warehouse << ' ' << product_type << ' ' << count << std::endl;
}

void unload(int drone, int warehouse, int product_type, int count)
{
	std::cout << drone << ' ' << "U " << warehouse << ' ' << product_type << ' ' << count << std::endl;
}

void deliver(int drone, int order, int product_type, int count)
{
	std::cout << drone << ' ' << "D " << order << ' ' << product_type << ' ' << count << std::endl;
}

void wait(int drone, int turn)
{
	std::cout << drone << ' ' << "W " << turn << std::endl;
}


#endif /* Common_h */

//
//  Common.h
//  HashCode2016
//
//  Created by Liang LIU on 11/02/2016.
//  Copyright © 2016 Liang LIU. All rights reserved.
//

#ifndef Common_h
#define Common_h
#include "InputLoader.h"
#include <cmath>

static const int CalculateEula(const Position& a, const Position& b)
{
    return squr((a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y));
}

static WareHouse* GetNearestWareHouse(const InputLoader& loader, Position& p)
{
    return &loader.warehouses[0];
//    int min_distance = INT_MAX;
//    int houseId = 0;
//    for (WareHOuse& house : loader.warehouses)
//    {
//        int distance = CalculateEula(p, house.Position);
//        if (distance < min_distance)
//        {
//            min_distance = distance;
//            houseId = house.Id;
//        }
//    }
}

static WareHouse* GetNearestOrder(const InputLoader& loader, const Position& p, const Drone& drone)
{
    int min_distance = INT_MAX;
    int orderId = -1;
    for (Order& order : loader.orders)
    {
        bool hasProductToDelivery = false;
        for (auto it = order.purchasePruducts.begin(); it != order.purchasePruducts.end(); it++)
        {
            if (drone.goods.find(it->first) != drone.goods.end())
            {
                hasProductToDelivery = true;
                break;
            }
        }
        if (hasProductToDelivery)
        {
            int distance = CalculateEula(p, order.Position);
            if (distance < min_distance)
            {
                min_distance = distance;
                orderId = order.Id;
            }
        }
    }
    if (orderId != -1)
    {
        return &loader.orders[orderId]
    }
    return nullptr;
}

#endif /* Common_h */

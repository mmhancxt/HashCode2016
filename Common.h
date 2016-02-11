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

static const WareHouse& GetNearestWareHouse(const InputLoader& loader, Position& p)
{
    int min_distance = INT_MAX;
    int houseId = 0;
    for (WareHOuse& house : loader.warehouses)
    {
        int distance = CalculateEula(p, house.Position);
        if (distance < min_distance)
        {
            min_distance = distance;
            houseId = house.Id;
        }
    }
}

static const WareHouse& GetNearestOrder(const InputLoader& loader, Position& p)
{
    int min_distance = INT_MAX;
    int houseId = 0;
    for (Order& order : loader.orders)
    {
        int distance = CalculateEula(p, order.Position);
        if (distance < min_distance)
        {
            min_distance = distance;
            houseId = house.Id;
        }
    }
}

#endif /* Common_h */

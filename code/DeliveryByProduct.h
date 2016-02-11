//
//  DeliveryByProduct.h
//  HashCode2016
//
//  Created by Liang LIU on 11/02/2016.
//  Copyright © 2016 Liang LIU. All rights reserved.
//

#ifndef DeliveryByProduct_h
#define DeliveryByProduct_h
#include "InputLoader.h"

class DeliveryByProduct
{
public:
    DeliverByProduct();
    
    void Start()
    {
        InputLoader loader;
        vector<Drone> drowns;
        for (int i = 0 ; i< const_droneNum; i++)
        {
            Drone d(loader.warehouses[0].position);
            drowns.push_back(d);
        }
        
        loader.LoadFromFile("mother_of_all_warehouses.in");
        vector<int> productNum;
        for (Order& order : loader.orders)
        {
            for (auto it=order.purchasedProducts.begin(); it!= order.purchasedProducts.end(); it++)
            {
                productNum[it->first]+= it->second;
            }
        }
        while (1)
        {
            for (int i = 0 ;i < const_droneNum ; i++)
            {
                if (drone.staus != FLY)
                {
                    if (drone.load != 0)
                    {
                        Order nearestOrder = GetNearestOrder(loader, p, drone);
                    }
                    Position p = drone.position;
                    WareHouse nearestHouse = GetNearestWareHouse(loader, p);
                    
                }
            }
        }
    
    }
};
                
#endif /* DeliveryByProduct_h */

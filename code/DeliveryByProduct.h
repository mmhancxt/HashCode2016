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
        for (int turn = 0; turn < loader.const_totalTurns; turn++)
        {
            for (int i = 0 ;i < const_droneNum ; i++)
            {
                if (drone.nextUsableTurn == turn)
                {
                    
                }
                if (drone.staus != FLY)
                {
                    Position p = drone.position;
                    if (drone.load != 0)
                    {
                        Order* nearestOrder = GetNearestOrder(loader, p, drone);
                        if (nearestOrder != nullptr)
                        {
                            // Del
                            deliver(drone.id, nearestOrder->id, int product_type, int count)

                        }
                    }
                    else
                    {
                        // Load
                        int product = -1;
                        for (int productId = 0; productId < productNum.size() && product == -1; productId++)
                        {
                            if (productNum[productId] != 0)
                            {
                                product = productId;
                            }
                        }
                        int productSize = std::min((loader.const_maxDroneLoad-load)/loader.products[productId].weight, productNum[productId]);
                        
                        WareHouse* nearestHouse = GetNearestWareHouse(loader, p);
                        load(drone.id, nearestHouse->id, product, productSize);
                        productNum[productId]-= productSize;
                        drone.status = FLY;
                        drone.productId = product;
                        drone.productCount = productSize;
                    }
                    
                }
            }
        }
    
    }
};
                
#endif /* DeliveryByProduct_h */

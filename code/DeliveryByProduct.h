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
    
    void Delivery(InputLoader& loader, const Position& p, Drone& drone)
    {
        Order* nearestOrder = GetNearestOrder(loader, p, drone);
        if (nearestOrder != nullptr)
        {
            for (auto it=drone.goods.begin(); drone.goods.end(); it++)
            {
                int productId = it->first;
                int productCountInDrone = it->second;
                auto iterator = nearestOrder->purchasedProducts.find(poroductId);
                if (iterator != nearestOrder->purchasedProducts.end())
                {
                    int productCountInOrder = iterator->second;
                    int deliverCount = std::min(productCountInDrone, productCountInOrder);
                    deliver(drone.id, nearestOrder->id, productId, deliverCount);
                    drone.load = drone.load - loader.products[productId]*deliverCount;
                    if (productCountInDrone == deliverCount)
                    {
                        drone.goods.erase(productId);
                    }
                    else
                    {
                        drone.goods[productId] = productCountInDrone - deliverCount;
                    }
                    if (productCountInOrder == deliverCount)
                    {
                        nearestOrder->purchasedProducts.erase(productId);
                    }
                    else
                    {
                        nearestOrder->purchasedProducts[productId] = productCountInOrder - deliverCount;
                    }
                }
            }
            
            if (load == 0)
            {
                Load(loader, p, drone);
            }
            else
            {
                Delivery(loader, p, drone);
            }
        }
    }
    
    void Load(InputLoader& loader, const Position& p, Drone& drone)
    {
        // next status is load
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
        //drone.nextAction = INWAREHOUSE;
        drone.productId = product;
        drone.productCount = productSize;
        drone.load = productSize*loader.products[poroductId].weight;
        drone.nextUsableTurn = CalculateEula(nearestHouse->position, p);
  
    }
    
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
                Drone& drone = drowns[i];
                if (drone.nextUsableTurn == turn)
                {
                    Position p = drone.position;
                    if (drone.load != 0)
                    {
                        Delivery(loader, p, drone);
                    }
                    else
                    {
                        Load(loader, p, drone);
                    }
                }
            }
        }
        
    }
};

#endif /* DeliveryByProduct_h */

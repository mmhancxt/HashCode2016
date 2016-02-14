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
#include "Common.h"

class DeliveryByProduct
{
public:
    InputLoader loader;
    vector<Drone> drowns;
    vector<int> productNum;
    
    DeliveryByProduct()
    {
        loader.LoadFromFile("/Users/Xavier/Programs/c++/HashCode2016/input/mother_of_all_warehouses.in");
        for (int i = 0 ; i< loader.const_droneNum; i++)
        {
            Drone d(loader.warehouses[0].position, i);
            drowns.push_back(d);
        }
        
        for (int i = 0; i < loader.products.size(); i++)
        {
            productNum.push_back(0);
        }
        
        for (Order& order : loader.orders)
        {
            for (auto it=order.purchasedProducts.begin(); it!= order.purchasedProducts.end(); it++)
            {
                //cout << it->first << endl;
                //cout << it->second << endl;
                productNum[it->first]+= it->second;
            }
        }
    }
    
    void Delivery(InputLoader& loader, Drone& drone)
    {
        Order* nearestOrder = GetNearestOrder(loader, drone);
        if (nearestOrder != nullptr)
        {
            vector<int> toErase;
            for (auto it=drone.goods.begin(); it != drone.goods.end(); it++)
            {
                int productId = it->first;
                int productCountInDrone = it->second;
                auto iterator = nearestOrder->purchasedProducts.find(productId);
                if (iterator != nearestOrder->purchasedProducts.end())
                {
                    int productCountInOrder = iterator->second;
                    int deliverCount = std::min(productCountInDrone, productCountInOrder);
                    deliver(drone.id, nearestOrder->id, productId, deliverCount);
                    drone.load = drone.load - loader.products[productId].weight*deliverCount;
                    if (productCountInDrone == deliverCount)
                    {
                        toErase.push_back(productId);
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
            for (int pId : toErase)
            {
                drone.goods.erase(pId);
            }
            drone.nextUsableTurn += CalculateEula(nearestOrder->deliverPosition, drone.position);
            drone.position.x = nearestOrder->deliverPosition.x;
            drone.position.y = nearestOrder->deliverPosition.y;
            
            if (drone.load == 0)
            {
                Load(loader, drone);
            }
            else
            {
                Delivery(loader, drone);
            }
        }
    }
    
    void Load(InputLoader& loader, Drone& drone)
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
        if (product == -1)
        {
            return;
        }
        int productSize = std::min((loader.const_maxDroneLoad-drone.load)/loader.products[product].weight, productNum[product]);
        
        WareHouse* nearestHouse = GetNearestWareHouse(loader, drone.position);
        load(drone.id, nearestHouse->id, product, productSize);
        productNum[product]-= productSize;
        drone.goods[product] = productSize;
        drone.load = productSize*loader.products[product].weight;
        drone.nextUsableTurn += (CalculateEula(nearestHouse->position, drone.position)+1);
        drone.position.x = nearestHouse->position.x;
        drone.position.y = nearestHouse->position.y;
//        cout << "Next available " << drone.nextUsableTurn << endl;
    }
    
    void Start()
    {
        for (int turn = 0; turn < loader.const_totalTurns; turn++)
        {
            for (int i = 0 ;i < loader.const_droneNum ; i++)
            {
                Drone& drone = drowns[i];
                if (drone.nextUsableTurn == turn)
                {
//                    cout << "turn " << turn << endl;
                    if (drone.load != 0)
                    {
                        Delivery(loader, drone);
                    }
                    else
                    {
                        Load(loader, drone);
                    }
                }
            }
        }
    }
};

#endif /* DeliveryByProduct_h */

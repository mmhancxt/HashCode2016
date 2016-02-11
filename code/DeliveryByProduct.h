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
        loader.LoadFromFile("/Users/Xavier/Programs/c++/HashCode2016/code/mother_of_all_warehouses.in");
        for (int i = 0 ; i< loader.const_droneNum; i++)
        {
            Drone d(loader.warehouses[0].position);
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
    
    void Delivery(InputLoader& loader, const Position& p, Drone& drone)
    {
        Order* nearestOrder = GetNearestOrder(loader, p, drone);
        cout << "nearestOrder " << nearestOrder << endl;
        if (nearestOrder != nullptr)
        {
            cout << "NearestOrder id is " << nearestOrder->id << endl;
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
            
            if (drone.load == 0)
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
        int productSize = std::min((loader.const_maxDroneLoad-drone.load)/loader.products[product].weight, productNum[product]);
        
        WareHouse* nearestHouse = GetNearestWareHouse(loader, p);
        load(drone.id, nearestHouse->id, product, productSize);
        productNum[product]-= productSize;
        //drone.nextAction = INWAREHOUSE;
        drone.productId = product;
        drone.productCount = productSize;
        drone.load = productSize*loader.products[product].weight;
        drone.nextUsableTurn = CalculateEula(nearestHouse->position, p)+1;
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
                    cout << "Next " << turn << endl;
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

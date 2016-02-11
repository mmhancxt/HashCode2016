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
        vector<Drown> drowns;
        for (int i = 0 ; i< const_droneNum; i++)
        {
            Drown d(0, )
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
                if (l
            }
        }
    
    }
};
                
#endif /* DeliveryByProduct_h */

#pragma once

#include "Objects.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>


class InputLoader
{
public:

    void LoadFromFile(const string & fileName)
    {
        ifstream file(fileName);
        if (file.is_open())
        {
            string line;
            getline(file, line);
            stringstream ss;
            ss << line;
			ss >> const_rowNum >> const_columnNum >> const_droneNum >> const_totalTurns >> const_maxDroneLoad;
            ss.clear();
            //cout << param << endl;

			int productsNum;
			getline(file, line);
			ss << line;
			ss >> productsNum;
            ss.clear();

			getline(file, line);
			ss << line;
			for (int i = 0; i < productsNum; ++i)
			{
				Product product;
				product.id = i;
				ss >> product.weight;
				products.push_back(product);
			}
			ss.clear();





            //while(unavailableSlotNb)
            //{
            //    getline(file, line);
            //    UnavailableSlot slot;
            //    ss << line;
            //    ss >> slot.rowIndex >> slot.slotIndex;
            //    //cout << slot << endl;
            //    unavailableSlots.push_back(slot);
            //    unavailableSlotNb--;
            //    ss.clear();
            //}

            //int serverNb = param.NbServes;
            //int serverIndex = 0;
            //while(serverNb)
            //{
            //    getline(file, line);
            //    auto server = std::make_shared<Server>();
            //    ss << line;
            //    ss >> server->size >> server->capacity;
            //    ss.clear();
            //    //cout << *server << endl;
            //    server->id = serverIndex;
            //    serverIndex++;
            //    servers.push_back(server);
            //    serverNb--;
            //}
        }
        else
        {
            cout << " file is not open" << endl;
        }
    }

public:
	vector<Product> products;
	vector<WareHouse> warehouses;
	vector<Order> orders;

	int const_rowNum;
	int const_columnNum;
	int const_droneNum;
	int const_totalTurns;
	int const_maxDroneLoad;

};
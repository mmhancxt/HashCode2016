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


			int dataWarehouseNum;
			getline(file, line);
			ss << line;
			ss >> dataWarehouseNum;
			ss.clear();

			for (int i = 0; i < dataWarehouseNum; ++i)
			{
				WareHouse house;
				getline(file, line);
				ss << line;
				ss >> house.position.x >> house.position.y;
				ss.clear();

				house.id = i;

				getline(file, line);
				ss << line;
				for (int j = 0; j < productsNum; ++j)
				{
					int productId = j;
					int productQty;
					ss >> productQty;
					house.availableProducts[j] = productQty;
				}
				warehouses.push_back(house);
			}
			ss.clear();


			int orderNum;
			getline(file, line);
			ss << line;
			ss >> orderNum;
			ss.clear();

			for (int i = 0; i < orderNum; ++i)
			{
				Order order;
				order.id = i;
				order.status = UNPROCESSED;

				getline(file, line);
				ss << line;
				ss >> order.deliverPosition.x >> order.deliverPosition.y;
				ss.clear();

				int itemNum;
				getline(file, line);
				ss << line;
				ss >> itemNum;
				ss.clear();

				getline(file, line);
				ss << line;
				for (int j = 0; j < itemNum; ++j)
				{
					int productId;
					ss >> productId;
					auto it = order.purchasedProducts.find(productId);
					if (it != order.purchasedProducts.end())
					{
						order.purchasedProducts[productId] += 1;
					}
					else
					{
						order.purchasedProducts.insert(make_pair(productId, 1));
					}
				}
				ss.clear();

				orders.push_back(order);
			}



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

		for (int i = 0; i != const_droneNum; ++i)
		{
			Drone drone(warehouses[0].position, i);
			drone.id = i;
			drone.nextUsableTurn = 0;
			drones.push_back(drone);
		}
	}

public:
	vector<Product> products;
	vector<WareHouse> warehouses;
	vector<Order> orders;
	vector< Drone > drones;
	int const_rowNum;
	int const_columnNum;
	int const_droneNum;
	int const_totalTurns;
	int const_maxDroneLoad;
};

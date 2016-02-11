
//#include "../Common.h"
//#include "InputLoader.h"
//#include "Objects.h"
//#include <iostream>
//#include <map>
//#include <numeric>
//#include <algorithm>
//using namespace std;
/*
void load(int drone, int warehouse, int product_type, int count)
{
	cout << drone << ' ' << 'L' << warehouse << ' ' << product_type << ' ' << count << endl;
}

void unload(int drone, int warehouse, int product_type, int count)
{
	cout << drone << ' ' << 'U' << warehouse << ' ' << product_type << ' ' << count << endl;
}

void deliver(int drone, int order, int product_type, int count)
{
	cout << drone << ' ' << 'D' << order << ' ' << product_type << ' ' << count << endl;
}

void wait(int drone, int turn)
{
	cout << drone << ' ' << 'W' << turn << endl;
}
*/

//class OrderFirstDistribution : public Distribution
//{
//public:
//	OrderFirstDistribution(InputLoader & _loader) : Distribution(_loader) {}
//
//	void send_product(Drone& drone, WareHouse& warehouse, int productId, Order & order)
//	{
//		int flight_available_capacity = loader.const_maxDroneLoad;
//		int warehouse_product_count = warehouse.availableProducts[productId];
//		int order_product_count = order.purchasedProducts[productId];
//		Product const& product = getProductById(productId);
//		int max_flight_product_count = flight_available_capacity / product.weight;
//		int deliver_product_count = std::min(std::min(warehouse_product_count, order_product_count), max_flight_product_count);
//		load(drone.id, warehouse.id, productId, deliver_product_count);
//		warehouse.availableProducts[productId] -= deliver_product_count;
//		deliver(drone.id, order.id, productId, deliver_product_count);
//		order.purchasedProducts[productId] -= deliver_product_count;
//		int expense = CalculateEula(warehouse.position, drone.position);
//		expense += CalculateEula(warehouse.position, order.deliverPosition);
//		expense += 2;
//		drone.nextUsableTurn += expense;
//		drone.position = order.deliverPosition;
//	}
//
//	Drone & getFlight()
//	{
//		std::sort(loader.drones.begin(), loader.drones.end(), [](Drone const& l, Drone const& r) {
//			return l.nextUsableTurn < r.nextUsableTurn;
//		});
//		return loader.drones.front();
//	}
//
//	WareHouse* getWarehouse(Product const & p, Position const& order, Position const& flight)
//	{
//		int minimum = numeric_limits<int>::max();
//		WareHouse* w;
//		for (auto & warehouse : loader.warehouses)
//		{
//			if (warehouse.containsProduct(p.id))
//			{
//				int d = CalculateEula(warehouse.position, order) + CalculateEula(warehouse.position, flight);
//				if (d < minimum)
//				{
//					minimum = d;
//					w = &warehouse;
//				}
//			}
//		}
//		return w;
//	}
//
//	Product& getProductById(int id)
//	{
//		return loader.products[id];
//	}
//
//	void scheduleFlightForOrder(Order & order)
//	{
//		auto products = order.purchasedProducts;
//		for (auto& product : products)
//		{
//			while (order.purchasedProducts[product.first] > 0) {
//				Drone & flight = getFlight();
//				WareHouse * w = getWarehouse(getProductById(product.first), order.deliverPosition, flight.position);
//				send_product(flight, *w, product.first, order);
//			}
//		}
//	}
//	
//	void run()
//	{	
//		for (auto& order : loader.orders) {
//			scheduleFlightForOrder(order);
//		}
//	}
//};
//
//

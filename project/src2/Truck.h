#ifndef TRUCK_H
#define TRUCK_H

#include <cpen333/thread/thread_object.h>
#include <iostream>
#include <thread>

#include "Customer.h"
#include "Order.h"
#include "OrderQueue.h"
#include "safe_printf.h"


class Truck : public cpen333::thread::thread_object {
  OrderQueue& delivery_queue_;
  OrderQueue& order_queue_;
  int id_;
  Storage& storage_;

 public:

  Truck(int id,OrderQueue& order_queue ,OrderQueue& delivery_queue,Storage& storage) :
      id_(id),order_queue_(order_queue), delivery_queue_(delivery_queue), storage_(storage) {}

  int id() {
    return id_;
  }

  
  int main() {

    safe_printf("Truck %d started\n", id_);
	Order order = delivery_queue_.get();

	std::string item_name;
	for (auto object : storage_.list_) {
		if (object.id == order.item_id) {
			item_name = object.name;
		}
	}

    while (order.item_id != 4000) {
		if (order.type == ORDER_TYPE_REGULAR) {
			safe_printf("Truck %d delivering to customer {%s,%d} \n", id_, item_name.c_str(), order.quantity);
		}
		else {
			safe_printf("Truck %d delivering restock {%s,%d}\n", id_, item_name.c_str(), order.quantity);
			order_queue_.add(order);
		}
		order = delivery_queue_.get();
    }

    safe_printf("Truck %d done.\n", id_);

    return 0;
  }
};

#endif TRUCK_H

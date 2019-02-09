#ifndef TRUCK_H
#define TRUCK_H

#include <cpen333/thread/thread/thread_object.h>
#include <iostream>
#include <thread>

#include "order.h"
#include "OrderQueue.h"
#include "safe_print.h"

class Truck : public cpen333::thread::thread_object {
  Order& queue_;
  int id_

public:

  Truck(OrderQueue& queue):
  queue_(queue){}

  int id(){
    return id_;
  }

  int main{
    safe_printf("Truck %d Ready\n", id_);

    Order order = queue_.get();
    while(){
      safe_printf("Truck %d dekivering %d\n",id_,order_.item_id);

      std::this_thread::sleep_for(std::chrono::seconds(3));

      safe_printf("Truck %d delivery of %d completed",id_,order.item_id);
      order = queue_.get();
    }
    return 0;
  }
};

#endif TRUCK_H

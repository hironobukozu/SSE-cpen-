#ifndef QUEUE_H
#define QUEUE_H

#include "Order.h"

class OrderQueue {
 public:

  virtual void add(const Order& order) = 0;


  virtual Order get() = 0;

};

#endif QUEUE_H

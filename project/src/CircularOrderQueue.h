#ifndef LAB6_CIRCULARORDERQUEUE_H
#define LAB6_CIRCULARORDERQUEUE_H

#include "OrderQueue.h"
#include <cpen333/thread/semaphore.h>
#include <mutex>

#define CIRCULAR_BUFF_SIZE 8

class CircularOrderQueue : public virtual OrderQueue {
  Order buff_[CIRCULAR_BUFF_SIZE];
  cpen333::thread::semaphore producer_;
  cpen333::thread::semaphore consumer_;
  std::mutex pmutex_;
  std::mutex cmutex_;
  size_t pidx_;
  size_t cidx_;


 public:
  CircularOrderQueue() :
      buff_(),
      producer_(CIRCULAR_BUFF_SIZE), consumer_(0),
      pmutex_(), cmutex_(), pidx_(0), cidx_(0){}

  void add(const Order& order) {

	  producer_.wait();
	  pmutex_.lock();
    int pidx;
    pidx = pidx_;
    pidx_ = (pidx_+1)%CIRCULAR_BUFF_SIZE;
	pmutex_.unlock();
    buff_[pidx] = order;
	consumer_.notify();
  }

  Order get() {


	  consumer_.wait();
	  cmutex_.lock();
    int cidx;
    cidx = cidx_;
    cidx_ = (cidx_+1)%CIRCULAR_BUFF_SIZE;
	cmutex_.unlock();
    Order out = buff_[cidx];

	producer_.notify();
    return out;
  }

};

#endif LAB6_CIRCULARORDERQUEUE_H

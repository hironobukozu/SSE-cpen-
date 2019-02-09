#ifndef LAB6_DYNAMICORDERQUEUE_H
#define LAB6_DYNAMICORDERQUEUE_H

#include "OrderQueue.h"
#include <deque>
#include <condition_variable>
#include <mutex>

/**
 * Dynamically-sized Queue Implementation
 *
 * Does not block when adding items
 */
class DynamicOrderQueue : public virtual OrderQueue {
  std::deque<Order> buff_;
  std::mutex mutex_;
  std::condition_variable cv_;
  bool orders_ = false;

 public:
  /**
   * Creates the dynamic queue
   */
  DynamicOrderQueue() :
      buff_(), mutex_(), cv_(),orders_() {}

  void add(const Order& order) {

    //==================================================
    // TODO: Safely add item to "queue"
    //    - safely add to end of internal queue
    //    - notify others of item availability
    //==================================================
	std::lock_guard<std::mutex> lock(mutex_);
    buff_.push_back(order);
    orders_ = true;
    cv_.notify_all();

  }

  Order get() {
	  std::unique_lock<decltype(mutex_)> lock(mutex_);

    //==================================================
    // TODO: Safely remove item from "queue"
    //    - wait until internal queue is non-empty
    //    - safely acquire item from internal queue
    //==================================================
	  cv_.wait(lock, [&]() {return orders_; });

	  // get first item in queue
		Order out = buff_.front();
		buff_.pop_front();
		lock.unlock();
		if (buff_.size() == 0) {
			orders_ = false;
		}
		return out;

  }
};

#endif //LAB6_DYNAMICORDERQUEUE_H
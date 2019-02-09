#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <cpen333/thread/thread_object.h>
#include <cpen333/thread/semaphore.h>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <string>

#include "safe_printf.h"

class Customer : public cpen333::thread::thread_object {
  OrderQueue& queue_;
  Storage& storage_;


 public:

  Customer(Storage& storage, OrderQueue& queue) :

      storage_(storage), queue_(queue){}


  int main() {

    safe_printf("Customer arrived\n" );

    double cost = 0;
    int items = 0;
    srand((int)std::chrono::system_clock::now().time_since_epoch().count());

	while (true) {
		size_t s = storage_.list().size();
		if (s > 0) {
			Item choice = storage_.list()[rand() % s];
			int quantity = rand() % 50 + 1;
			cost = choice.price*quantity;

			++items;
			safe_printf("Customer ordering %s \n",choice.name.c_str());
			safe_printf("Customer paying $%.2f \n", cost);
			queue_.add({ choice.id,quantity,ORDER_TYPE_REGULAR });
		}
		std::this_thread::sleep_for(std::chrono::seconds(15));
	}






    return 0;
  }
};

#endif CUSTOMER_H

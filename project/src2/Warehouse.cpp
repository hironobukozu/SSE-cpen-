#include "Computer.h"
#include "Robot.h"
#include "Customer.h"
#include "Truck.h"
#include "CircularOrderQueue.h"
#include "safe_printf.h"


int main() {
	Storage storage;
	storage.load_items("data/warehouse_stock.json");

  std::vector<Robot*> robots;
  std::vector<Customer*> customers;
  std::vector<Truck*> trucks;

  const int nrobots = 4;
  const int ntrucks = 3;
  const int ncustomers = 1;

  CircularOrderQueue order_queue;
  CircularOrderQueue deliver_queue;

  for (int i=0; i<nrobots; ++i) {
    robots.push_back(new Robot(i, order_queue, deliver_queue,0,0,0,0,std::ref(storage)));
  }

  for (int i=0; i<ntrucks; ++i) {
    trucks.push_back(new Truck(i,order_queue ,deliver_queue,std::ref(storage)));
  }

  for (int i=0; i<ncustomers; ++i) {
    customers.push_back(new Customer(std::ref(storage), order_queue));
  }

  for (auto& robot : robots) {
    robot->start();
  }
  for (auto& truck : trucks) {
    truck->start();
  }
  for (auto& customer : customers) {
    customer->start();
  }
  while (true) {
	  for (auto thing : storage.storage_) {
		  if (thing.second.stock <= 50) {
			  safe_printf("\n <<<Alert>>> \n %s is low on stock. Only %d left.\n Ordering Restock.\n\n", thing.second.name.c_str(), thing.second.stock);
			  deliver_queue.add({ thing.second.id,100,ORDER_TYPE_RESTOCK});
		  }
	  }
	  std::this_thread::sleep_for(std::chrono::seconds(10));
  }

  for (auto& customer : customers) {
    customer->join();
  }

  //for (int i = 0; i < 4; i++) {
	  //order_queue.add({ i, 4000 });
  //}

  for (auto& robot : robots) {
    robot->join();
  }

  //for (int i = 0; i < 2; i++) {
	  //deliver_queue.add({ i,4000 });
  //}

  for (auto& truck : trucks) {
    truck ->join();
  }

  for (auto& customer : customers) {
    delete customer;
    customer = nullptr;
  }
  for (auto& robot : robots) {
    delete robot;
    robot = nullptr;
  }
  for (auto& truck : trucks) {
    delete truck;
    truck = nullptr;
  }

  //std::cout << "Restaurant is closing" << std::endl;
  //cpen333::pause();

  return 0;
}

#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <memory>
#include <mutex>

#include "Warehouse.h"
#include "JsonWarehouseApi.h"


#include "Warehouse.h"
#include "Robot.h"

#include <cpen333/process/socket.h>
#include <cpen333/process/shared_memory.h>
#include <cpen333/process/mutex.h>


size_t load_items(const std::string filename, std::map<int,Item>& storage_){
  std::ifstream fin(filename);

  size_t nadded = 0;
  if (fin.is_open()){
    JSON jstorage;
    fin >> jstorage;

    for(const auto& jitem : jstorage){
      Item item;
      item.id = jitem["id"];
      item.name = jitem["name"];
      item.price = jitem["price"];
      item.stock = jitem["stock"];
      item.col_number = jitem["col_number"];
      item.row_number = jitem["row_number"];
      item.side = jitem["side"];
      item.shelf = jitem["shelf"];

	  auto it = storage_.insert({ item.id,item });
      nadded++;
    }
  }
  return nadded;

}

void service(Storage &storage, WarehouseApi &&api){

  std::cout<<"Customer Connected"<<std::endl;

  cpen333::process::mutex mutex_(WAREHOUSE_MUTEX_NAME);

  std::unique_ptr<Message> msg = api.recvMessage();

  while(msg != nullptr){
    MessageType type = msg->type();
    switch (type){
      case MessageType::SEARCH:{
        {
          std::lock_guard<cpen333::process::mutex> lock(mutex_);
          SearchMessage &search_ = (searchMessage &)(*msg);
          std::cout << "Customer searching for:" <<search_.name_regex<<std::endl;
        }
        std::vector<Item> results;
        results = storage.search(search_.name_regex);

        api.sendMessage(SearchResponseMessage(search_,results,MESSAGE_STATUS_OK));
        break;
      }
      case MessageType::ORDER:{
        {
          std::lock_guard<decltype(mutex)> lock(mutex);
          OrderMessage &order_ = (OrderMessage &)(*msg);
          std::cout << "Customer ordering item"<< order_.order << std::endl;
        }
        bool success = false;
        success = storage.order(order_.order);

        if(success){
          api.sendMessage(OrderResponseMessage(order_,MESSAGE_STATUS_OK));
        }else{
          api.sendMessage(OrderResponseMessage(order_,MESSAGE_STATUS_ERROR,"Item not available"));
        }
        break;
      }
      default:{
        std::cout<<"Customer sent invalid message"<<std::endl;
      }
    }
    msg = api.recvMessage();
  }
}



int main{
  cpen333::process::mutex mutex_(WAREHOUSE_MUTEX_NAME);
  cpen333::process::shared_memory memory_(WAREHOUSE_SHARED_MEMORY_NAME,sizeof(Storage));
  Storage *data = (Storage*)memory_.get();


  load("warehouse_stock.json",std::ref(data -> storage_));

  std::vector<Robot*> robots;
  std::vector<Truck*> trucks;

  const int nrobots=4;
  const int ntrucks=2;

  CircularOrderQueue order_queue;
  CircularOrderQueue delivery_queue;

  for(int i=0; i<nrobots;i++){
    robots.push_back(new Robot(i, order_queue, delivery_queue));
  }

  for(int i=0; i<ntrucks; i++){
    trucks.push_back(new Truck(i, delivery_queue));
  }

  cpen333::process::socket_server server(WAREHOUSE_SERVER_PORT);
  server.open();
  std::cout << "Server started on port "<<server.port()<<std::endl;

  int i=0;
  while(true){
    cpen333::process::socket customer;
    if (server.accept(client)){
      JsonWarehouseApi api(std::move(customer));
      std::thread thread(service,storage,std::move(api));
      thread.detach();
    }
  }
server.close();
return 0;

}

#include "Computer.h"
#include "JsonWarehouseApi.h"

#include <cpen333/process/socket.h>
#include <cpen333/process/shared_memory.h>
#include <cpen333/process/mutex.h>

#include <fstream>
#include <iostream>
#include <string>
#include <thread>



void service(Storage &storage, WarehouseApi &&api){

  std::cout<<"Customer Connected"<<std::endl;

  cpen333::process::mutex mutex_(WAREHOUSE_MUTEX_NAME);

  std::unique_ptr<Message> msg = api.recvMessage();

  while(msg != nullptr){
    MessageType type = msg->type();
    switch (type){
      case MessageType::SEARCH:{
        
		  mutex_.lock();
          SearchMessage &search = (SearchMessage &)(*msg);
          std::cout << "Customer searching for:" <<search.name_regex<<std::endl;
		  mutex_.unlock();
        
        std::vector<Item> results;
        results = storage.find(search.name_regex);

        api.sendMessage(SearchResponseMessage(search,results,MESSAGE_STATUS_OK));
        break;
      }
      case MessageType::ORDER:{
        
		  mutex_.lock();
          OrderMessage &order_ = (OrderMessage &)(*msg);
          std::cout << "Customer ordering item" << order_.order << std::endl;
		  mutex_.unlock();
        
        bool success = false;
        success = storage.order(order_.order);

        if(success){
          api.sendMessage(OrderResponseMessage(order_,MESSAGE_STATUS_OK));
        }
		//else{    api.sendMessage(OrderResponseMessage(order_,MESSAGE_STATUS_ERROR,"Item not available"));}
        break;
      }
      default:{
        std::cout<<"Customer sent invalid message"<<std::endl;
      }
    }
    msg = api.recvMessage();
  }
}




int main(){

	Storage storage;
	storage.load_items("warehouse_stock.json");

  cpen333::process::socket_server server(WAREHOUSE_SERVER_PORT);
  server.open();
  std::cout << "Server started on port "<<server.port()<<std::endl;

  int i=0;
  while(true){
    cpen333::process::socket customer;
    if (server.accept(customer)){
      JsonWarehouseApi api(std::move(customer));
      std::thread thread(service,storage,std::move(api));
      thread.detach();
    }
  }
server.close();


  return 0;
}

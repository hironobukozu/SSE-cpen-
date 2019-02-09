#include "Warehouse.h"
#include "JsonWarehouseApi.h"
#include "Item.h"

#include <cpen333/process/socket.h>

#include <iostream>
#include <limits>

static const char CUSTOMER_SEARCH = '1';
static const char CUSTOMER_ORDER = '2';

void print_start(){

  std::cout << "Welcome to Amazoom!!!!!!"<<std::endl;
  std::cout << "  "<<std::endl;
  //std::cout << "To begin please press ENTER" <<std::endl;
  //std::cin.get();
  std::cout << " (1) Search Item"<<std::endl;
  std::cout << " (2) Order Item"<<std::endl;
  std::cout<< " Enter Number: ";
  std::cout.flush();


}

void do_search(WarehouseApi &api){
  std::regex name_regex;

  std::cout << std::endl << "Search for items" << std::endl;
  std::cout << " Item name expression: ";
  std::getline(std::cin, name_regex);

  SearchMessage msg(name_regex);
  if (api.sendMessage(msg)){

    std::unique_ptr<Message> msgr = api.recvMessage();

    SearchResponseMessage& resp = (SearchResponseMessage&)(*msgr);

    if(resp.status == MESSAGE_STATUS_OK){
      std::cout << std:endl << "Search Results:"<<std::endl;
      for (const auto& item : resp.results){
        std::cout << "  " <<item<<std::endl;
      }
    } else {
      std::cout << std::endl << " Search \"" <<name_regex<<"\" failed"<<resp.info<std::endl;
    }
  }
  std::cout<<std::endl;

}

void do_order(Warehouse &api){


  std::string temp;
  int item_id;
  int quantity;

  std::cout << std::endl << "Order Item" << std::endl;
  std::cout << "  Item id: ";
  std::getline(std::cin,temp);
  item_id = stoi(temp);
  std::cout << "  Item quantity:  ";
  std::getline(std::cin,temp);
  quantity = stoi(temp);

  Order order(item_id,quantity);
  OrderMessage msg(order);

  if(api.sendMessage(msg)){

    std::unique_ptr<Message> msgr = api.recvMessage();
    OrderResponseMessage& resp = (OrderResponseMessage&)(*msgr);

    if(resp.status == MESSAGE_STATUS_OK){
      std::cout << std::endl << "Order Confirmed" <<std::endl;
    } else{
      std::cout << std::endl << "Order Unsuccessful" << resp.info <<std::endl;
    }
  }
std::cout << std::endl;

}

int main(){
  cpen333::process::shared_object memory_(WAREHOUSE_SHARED_MEMORY_NAME,sizeof(Storage));
  Storage *data = (Storage*)memory_.get();
  cpen333::process::socket socket("localhost", MUSIC_LIBRARY_SERVER_PORT);
  std::cout << "Customer connecting...";
  std::cout.flush();

  if(socket.open()){
    std::cout<<"connected"<<std::endl;

    JsonWarehouseApi api(std::move(socket));

    char cmd = 0;
    while (true){
      print_start();

      ;

      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

      switch(cmd){
        case CUSTOMER_SEARCH:
        do_search(api);
        break;
        case CUSTOMER_ORDER:
        do_order(api);
        break;
        default:
        std::cout<<"invalid command number"<<cmd<<std::endl<std::endl;
      }
      cpen333::pause();
    }
  }else{
    std::cout << "failed"<<std::endl;
  }

return 0;
}

#ifndef ROBOT_H
#define ROBOT_H

#include <cpen333/thread/thread_object.h>
#include <cpen333\process\shared_memory.h>
#include <iostream>
#include <thread>
#include <mutex>

#include "Order.h"
#include "OrderQueue.h"
#include "Warehouse.h"
#include "safe_printf.h"
#define WAREHOUSE_ROWS 7
#define WAREHOUSE_COLUMNS 7
#define WAREHOUSE_SHELVES 6




class Robot : public cpen333::thread::thread_object{

	cpen333::process::shared_object <Storage> memory_;
	OrderQueue& orders_;
	OrderQueue& deliveries_;
	int id_;
	int layout[WAREHOUSE_ROWS][WAREHOUSE_COLUMNS][3][WAREHOUSE_SHELVES+1]={};
	int col_position = 0;
	int row_position = 0;
	int side_position = 0;
	int shelf_position = 0;

public:
	Robot(int id, OrderQueue& orders, OrderQueue& deliveries) :

		memory_(WAREHOUSE_SHARED_MEMORY_NAME), id_(id), orders_(orders), deliveries_(deliveries) {}

int id(){
  return id_;
}

void prepare_order(const Order& order,std::map<int,Item>& storage){
  cpen333::process::mutex mutex_(WAREHOUSE_MUTEX_NAME);
  cpen333::process::shared_memory memory_(WAREHOUSE_SHARED_MEMORY_NAME,sizeof(Storage));
  Storage *data = (Storage*)memory_.get();

  int col_destination, row_destination, side_destination, shelf_destination;


  for(auto storage : data -> storage_){
    if(order.item_id == data -> storage.id){
      std::lock_guard<cpen333::process::mutex> lock(mutex_);
      col_destination = data -> storage.col_number;
      row_destination = data ->  storage.row_number;
      side_destination = data -> storage.side;
      shelf_destination = data -> storage.shelf;
    }
  }

  for(int i = 0; i == col_destination; i++){
    col_position++;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  for(int i = 0; i == row_destination; i++){
    row_position++;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  for(int i = 0; i==side_destination;i++){
    side_position++;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  for(int i = 0; i==shelf_destination; i++){
    shelf_position++;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  safe_printf("Got Item");
  for(int i = shelf_position;shelf_position==0;i--){
    shelf_position--;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  side_position = 0;

  for(int i = row_position; row_position==6; i++){
    row_position++;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  if(col_position>3){
    for(int i = col_position;col_position==3;i--){
      col_position--;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  } else if(col_position<3){
    for(int i = col_position;col_position==3;i++){
      col_position++;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }

  deliveries_.add(order);
  safe_printf("Order preapared");


}



  int main(){
    safe_printf("Robot %d activated\n",id_);
    //std::this_thread::sleep_for(std::chrono::seconds(3));
	cpen333::process::shared_memory memory_(WAREHOUSE_SHARED_MEMORY_NAME, sizeof(Storage));
	Storage *data = (Storage*)memory_.get();

    safe_printf("Robot %d ready\n",id_);

    Order order = orders_.get();


    while(true){

		prepare_order(order,std::ref(data -> storage_));

		Order order = orders_.get();

    }

    return 0;
  }
};


#endif ROBOT_H

#ifndef WAREHOUSE_ITEM_H
#define WAREHOUSE_ITEM_H

#include <string>
#include <iostream>
#include <map>


#define WAREHOUSE_MUTEX_NAME "Warehouse_mutex"
#define WAREHOUSE_SHARED_MEMORY_NAME "Warehouse_memory"


class Item{
  public:
    int id;
    std::string name;
    double price;
    int stock;
    int col_number;
    int row_number;
    int side;
    int shelf;

};

struct Storage{
  std::map<int,Item> storage_;
  OrderQueue& queue_

public:
  Storage():storage_(){}



  std::vector<Item>& storage() {
    return storage_;
  }

  std:vector<Item> search(const std::string& name_regex) const{
    std::vector<Item> out;

    std::regex nregex(name_regex);
    for(const auto& item:storage_){
      if(std::regex_search(item.name,nregex)){
        out.push_back(item);
      }
    }
    return out;
  }

  bool order(const Order& order){
    queue_.add({order.item_id,order.quantity});
  }

};



#endif WAREHOUSE_ITEM_H

#ifndef COMPUTER_H
#define COMPUTER_H

#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <map>
#include <json.hpp>

#include "Item.h"

#define WAREHOUSE_MUTEX_NAME "warehouse_mutex"

using JSON = nlohmann::json;




class Storage {
public:
  std::map<int,Item> storage_;
  std::vector<Item> list_;


 public:
  Storage(): storage_(),list_() {}


   size_t load_items(const std::string filename){
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
	  if (it.second) {
		  nadded++;
		  list_.push_back(item);
	  }

     }
    }

    return nadded;

  }

   const std::vector<Item>& list() const {
	   return list_;
   }

   std::vector<Item> find(const std::string& name_regex)const{
     std::vector<Item> out;

     std::regex nregex(name_regex);

     for(const auto& object :list_){
       if(std::regex_search(object.name,nregex)){
         out.push_back(object);
       }
     }
     return out;
   }

  // bool order(const Order& order) {}


};

#endif COMPUTER_H

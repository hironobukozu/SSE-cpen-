#ifndef WAREHOUSE_JSON_H
#define WAREHOUSE_JSON_H

#include "Computer.h"
#include "Message.h"
#include "Item.h"

#include <json.hpp>

#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <set>

using JSON = nlohmann::json;

#define MESSAGE_SEARCH "search"
#define MESSAGE_SEARCH_RESPONSE "search_response"
#define MESSAGE_ORDER "order"
#define MESSAGE_ORDER_RESPONSE "order_response"

#define MESSAGE_TYPE "msg"
#define MESSAGE_STATUS "status"
#define MESSAGE_INFO "info"
#define MESSAGE_SEARCH_RESULTS "results"
#define MESSAGE_ITEM "item"
#define MESSAGE_ITEM_NAME "name"
#define MESSAGE_ITEM_NAME_REGEX "name_regex"

class JsonConverter{
public:

  static JSON toJSON(const Item &item){
    JSON j;
    j[MESSAGE_ITEM_NAME] = item.name;
    return j;
  }

static JSON toJSON(const std::vector<Item> &items){
  JSON j;
  for(const auto& item : items){
    j.push_back(toJSON(item));
  }
  return j;
}

static JSON toJSON(const SearchMessage & search){
  JSON j;
  j[MESSAGE_TYPE] = MESSAGE_SEARCH;
  j[MESSAGE_ITEM_NAME_REGEX] = search.name_regex;
  return j;
}

static JSON toJSON(const SearchResponseMessage &search_response){
  JSON j;
  j[MESSAGE_TYPE] = MESSAGE_SEARCH_RESPONSE;
    j[MESSAGE_STATUS] = search_response.status;
    j[MESSAGE_INFO] = search_response.info;
    j[MESSAGE_SEARCH] = toJSON(search_response.search);
    j[MESSAGE_SEARCH_RESULTS] = toJSON(search_response.results);
	return j;
}

static JSON toJSON(const OrderMessage &order){
  JSON j;
  j[MESSAGE_TYPE] = MESSAGE_ORDER;
  j[MESSAGE_ITEM] = toJSON(order.order);
  return j;
}

static JSON toJSON(const OrderResponseMessage &order_response){
  JSON j;
  j[MESSAGE_TYPE] = MESSAGE_ORDER_RESPONSE;
  j[MESSAGE_STATUS] = order_response.status;
  j[MESSAGE_INFO] = order_response.info;
  j[MESSAGE_ORDER] = toJSON(order_response.order);
  return j;
}

static JSON toJSON(const Message &msg){
  switch(msg.type()){
    case SEARCH: {
      return toJSON((SearchMessage &) msg);
    }
    case SEARCH_RESPONSE:{
      return toJSON((SearchResponseMessage &) msg);
    }
    case ORDER: {
      return toJSON((OrderMessage &) msg);
    }
    case ORDER_RESPONSE:{
      return toJSON((OrderResponseMessage &) msg);
    }
    default:{

    }
  }

  JSON err;
  err[MESSAGE_STATUS] = MESSAGE_STATUS_ERROR;
  err[MESSAGE_INFO] = std::string("unknown message type");
  return err;
}

static Item parseItem(const JSON &j){
	return Item(j[MESSAGE_ITEM_NAME]);
}

static std::vector<Item> parseItems(const JSON &jitems){
  std::vector<Item> out;

  for (const auto& item : jitems){
    out.push_back(parseItem(item));
  }

  return out;
}

static SearchMessage parseSearch(const JSON &jsearch){
  std::string name_regex = jsearch[MESSAGE_ITEM_NAME_REGEX];
  return SearchMessage(name_regex);
}

static SearchResponseMessage parseSearchResponse(const JSON &jsearchr){
  SearchMessage search = parseSearch(jsearchr[MESSAGE_SEARCH]);
  std::vector<Item> results = parseItem(jsearchr[MESSAGE_SEARCH_RESULTS]);
  std::string status = jsearchr[MESSAGE_STATUS];
  std::string info = jsearchr[MESSAGE_INFO];
  return SearchResponseMessage(search,results,status,info);
}


static OrderMessage parseOrder(const JSON &jorder){
  Item item = parseItem(jorder[MESSAGE_ITEM]);
  return OrderMessage(item);
}

static OrderResponseMessage parseOrderResponse(const JSON &jorderr){
  OrderMessage order = parseOrder(jorderr[MESSAGE_ORDER]);
  std::string status = jorderr[MESSAGE_STATUS];
  std::string info = jorderr[MESSAGE_INFO];
  return OrderResponseMessage(order,status,info);
}

static MessageType parseType(const JSON &jmsg){
  std::string msg = jmsg[MESSAGE_TYPE];
  if(MESSAGE_SEARCH == msg){
    return MessageType::SEARCH;
  } else if(MESSAGE_SEARCH_RESPONSE == msg){
    return MessageType::SEARCH_RESPONSE;
  } else if(MESSAGE_ORDER == msg){
    return MessageType::ORDER;
  } else if(MESSAGE_ORDER_RESPONSE == msg){
    return MessageType::ORDER_RESPONSE;
  }
  return MessageType::UNKNOWN;
}

static std::unique_ptr<Item> parseMessage(const JSON &jmsg){
  MessageType type = parseType(jmsg);
  switch(type){
    case SEARCH: {
      return std::unique_ptr<Message>(new SearchMessage(parseOrder(jmsg)));
    }
    case SEARCH_RESPONSE:{
      return std::unique_ptr<Message>(new SearchResponseMessage(parseSearchResponse(jmsg)));
    }
    case ORDER:{
      return std::unique_ptr<Message>(new OrderMessage(parseOrder(jmsg)));
    }
    case ORDER_RESPONSE: {
      return std::unique_ptr<Message>(new OrderResponseMessage(parseOrderResponse(jmsg)));
    }
  }
  return std::unique_ptr<Message>(nullptr);
}



};

#endif WAREHOUSE_JSON_H

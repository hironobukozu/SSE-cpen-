#ifndef WAREHOUSE_MESSAGE_H
#define WAREHOUSE_MESSAGE_H

#include "Order.h"
#include "Computer.h"
#include "Item.h"
#include <string>

enum MessageType{
  SEARCH,
  SEARCH_RESPONSE,
  ORDER,
  ORDER_RESPONSE,
  UNKNOWN
};

#define MESSAGE_STATUS_OK "OK"
#define MESSAGE_STATUS_ERROR "ERROR"

class Message{
public:
  virtual MessageType type() const = 0;
};

class ResponseMessage : public Message{
public:
  const std::string status;
  const std::string info;
  ResponseMessage(const std::string& status, const std::string& info = ""):
  status(status),info(info){}
};

class SearchMessage : public Message{
public:
  const std::string name_regex;

  SearchMessage(const std::string& name_regex) : name_regex(name_regex){}
  MessageType type() const{
    return MessageType::SEARCH;
  }
};
class SearchResponseMessage : public ResponseMessage{
public:
  const SearchMessage search;
  const std::vector<Item> results;

  SearchResponseMessage(const SearchMessage& search, const std::vector<Item>& results,const std::string& status, const std::string& info = ""):
  ResponseMessage(status, info), search(search),results(results){}

  MessageType type() const {
    return MessageType::SEARCH_RESPONSE;
  }
};
class OrderMessage : public Message{
public:
  const Order order;

  OrderMessage(const Order& order) : order(order){}

  MessageType type() const {
    return MessageType::ORDER;
  }
};
class OrderResponseMessage : public ResponseMessage{
public:

	const Order order;

  OrderResponseMessage(Order order, std::string status, std::string info = ""):
  ResponseMessage(status,info), order(order){}

  MessageType type() const {
    return MessageType::ORDER_RESPONSE;
  }
};




#endif WAREHOUSE_MESSAGE_H

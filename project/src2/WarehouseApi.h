#ifndef WAREHOUSE_API_H
#define WAREHOUSE_API_H

#include <memory>
#include "Message.h"

class WarehouseApi{
public:
  virtual bool sendMessage(const Message& msg) = 0;
  virtual std::unique_ptr<Message> recvMessage() =0;
};

#endif WAREHOUSE_API_H

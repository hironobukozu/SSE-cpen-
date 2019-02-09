#ifndef WAREHOUSE_JSON_API_H
#define WAREHOUSE_JSON_API_H

#include "WarehouseApi.h"
#include "Message.h"
#include "JsonConverter.h"

#include <cpen333/process/socket.h>

#include <algorithm>

#define WAREHOUSE_SERVER_PORT 55555


class JsonWarehouseApi : public WarehouseApi{
private:
  cpen333::process::socket socket_;

  static const char JSON_ID = 0x55;

  bool sendJSON(const JSON& j){

    std::string jsonstr = j.dump();

    char buff[4];
    size_t size = jsonstr.size()+1;
    for(int i=4; i-->0;){
      buff[i] = (char)(size & 0xFF);
      size = size >> 8;
    }

    bool success = socket_.write(buff,4);
    success &= socket_.write(jsonstr);

    return success;
  }

  bool readString(std::string& str, size_t size){

    char cbuff[256];
    bool success = false;

    while(size>0){
      if(size<256){
        socket_.read_all(cbuff,size);
        str.append(cbuff);
        size = 0;
      } else if(size>=256) {
        socket_.read_all(cbuff,256);
        str.append(cbuff);
        size = size-256;
      }
      success = true;

    }
    return success;
  }

  bool recvJSON(JSON& jout){
    char buff[4];
    if(!socket_.read_all(buff,4)){
      return false;
    }

    int size = 0;

    size = (int)((0xFF & buff[0]) << 24 |( 0xFF & buff[1] )<< 16 |( 0xFF & buff[2]) << 8 | 0xFF & buff[3]);

    std::string str;
    if(!readString(str,size)){
		return false;
    }
    jout = JSON::parse(str);

    return true;
  }

  JsonWarehouseApi();

public:
  JsonWarehouseApi(cpen333::process::socket&& socket):
  socket_(std::move(socket)){}

  bool sendMessage(const Message& msg){
    JSON jmsg = JsonConverter::toJSON(msg);

    char id = JSON_ID;
    if(!socket_.write(&id,1)){
      return false;
    }
    return sendJSON(jmsg);
  }

  std::unique_ptr<Message> recvMessage(){
    char id;
    if(!socket_.read_all(&id,1)||id != JSON_ID){
      return nullptr;
    }
    JSON jmsg;

    if (!recvJSON(jmsg)){
      return nullptr;
    }
    return JsonConverter::parseMessage(jmsg);
  }

};


#endif WAREHOUSE_JSON_API_H

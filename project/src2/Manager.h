#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>

#include <cpen333/thread/thread_object.h>

#include "Computer.h"


class Manager : public cpen333::thread::thread_object{
  Storage& storage_;

public:
  Manager(Storage& storage):
  storage_(storage){}

  void check

};






#endif MANAGER_H

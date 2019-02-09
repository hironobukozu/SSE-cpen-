#include "common.h"

#include "common.h"

#include <cpen333/process/semaphore.h>
#include <cpen333/process/mutex.h>
#include <cpen333/process/shared_memory.h>
#include <cpen333/process/condition_variable.h>
#include <iostream>


int main() {
	cpen333::process::shared_memory memory_(MAZE_MEMORY_NAME,sizeof(SharedData));
	SharedData *data = (SharedData*)memory_.get();
	//condition 2
	// passenger will notify() waiting_when in line
	// passenger will wait() after getting on
	data->waiting_("number in line", 0);

  //==========================================================
  // TODO: Implement passenger
  //   - Wait until roller coaster is ready and boarding
  //   - Notify roller coaster when boarded
  //   - Wait until ride is over and safe to leave
  //   - Notify roller coaster when leaving
  //==========================================================
  std::cout << "Passenger waiting in line" << std::endl;
  
  data->waiting_.notify();
  //conodition 1
  data->entry_.wait();
  data->waiting_.wait();
  data->full_.notify();
  // wait until roller coaster is boarding and there is room

  std::cout << "Passenger boarded" << std::endl;

  // wait until ride is over

  data->exit_.wait();

  std::cout << "Passenger leaving" << std::endl;
  //condition 4
  // give back semaphore to notify that a seat has become empty

  data->entry_.notify();
  data->empty_.notify();
  return 0;
}

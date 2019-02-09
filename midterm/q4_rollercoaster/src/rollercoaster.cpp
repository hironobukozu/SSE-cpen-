#include "common.h"

#include <cpen333/process/semaphore.h>
#include <cpen333/process/mutex.h>
#include <cpen333/process/shared_memory.h>
#include <cpen333/process/condition_variable.h>

#include <thread>
#include <chrono>

int main() {

  //==========================================================
  // TODO: Implement roller coaster
  //   - Initialize anything that needs to be initialized
  //   - Loop
  //      - Notify passengers it is safe to board
  //      - Wait until full OR
  //          there is at least one passenger boarded AND
  //          no more passengers are in line
  //      - Go for ride
  //      - Notify passengers it is safe to exit
  //      - Wait until all passengers have exited
  //==========================================================
	cpen333::process::shared_memory memory_(MAZE_MEMORY_NAME, sizeof(SharedData));
	SharedData *data = (SharedData*)memory_.get();
  // initialize

  //condition1
  // create a semaphore for number of empty seats
  // use wait() to get on or wait
	data->entry_("number of passengers aboard",4);


	//condition3
	// create semaphore for exiting
	// when taking off passengers will wait()
	// after rollercoaster returns it will notify() twice to let passengers off
	data -> exit_("exit", 0);

	//condition 4
	//create a semaphore to count number of pasengers aboard
	data -> full_("number of passengers", 0);
	data->empty_("check for empty", 0);
  // keep running roller coaster forever
  while(true) {

    // start boarding

    std::cout << "Roller coaster loading passengers" << std::endl;

    // wait until either coaster is full or we have at least one and nobody waiting
    int npassengers = 0;

    // condition 2
    /*rollercoaster will try_wait() waiting_
    * if waiting_ is 0 try_wait will return false meaning that there is nobody waiting
	* if it is true there is someone waiting
    */
	while (data->waiting_.try_wait() && npassengers<=4 ) {
		npassengers++;
	}
	for (int i = 0; i < npassengers && data->waiting_.try_wait(); i++) {
		data->full_.wait();
	}
	
	
    // GO!
    std::cout << "Roller coaster running with " << npassengers << " passengers" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Roller coaster returned, letting passengers off" << std::endl;

    // let passengers off
	//condition3
	// notify() exit_ the number of times as the number of passengers

	for (int i = 0; i < npassengers; i++) {
		data->exit_.notify();
	}

    std::cout << "Roller coaster waiting for passengers to exit" << std::endl;

    // wait for passengers to leave
	//condition 4
	// making sure that rollercoaster is empty 
	for (int i = 0; i < npassengers; i++) {
		data->empty_.wait();
	}

  }

  return 0;
}

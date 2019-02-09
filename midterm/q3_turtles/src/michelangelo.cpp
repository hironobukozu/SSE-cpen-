#include "turtles.h"
#include <cpen333/process/shared_memory.h>
#include <cpen333/process/mutex.h>
#include <cpen333/process/subprocess.h>
#include <thread>

int main() {

  cpen333::process::shared_object<TurtleMemory> memory(TURTLE_MEMORY_NAME);
  cpen333::process::mutex mutex("q4_turtle_mutex");

  //========================================================
  // TODO: Implement Michelangelo
  //       - Initialize his memory
  //       - check-in
  //       - check if defeated
  //       - check on other turtle(s), restart if necessary
  //========================================================

  // re-initialize my memory
  {
    // adding lock_guard for mutual exclutsion since michelangelo is accessing shared data

	  std::lock_guard<cpen333::process::mutex> lock(mutex);
    memory->michelangelo.checkin = 0;
  }

  // take care of leonardo
  int last_raphael= -1;
  int next_raphael = 0;
  int miss = 0;
  while (true) {



		  // adding lock_guard for mutual exclutsion since michelangelo is accessing shared data

     {
       std::lock_guard<cpen333::process::mutex> lock(mutex);
		  memory->michelangelo.checkin++;
		  next_raphael = memory->raphael.checkin;
    }

		  // check on leonardo and restart if necessary

		  if (last_raphael == next_raphael) {
			  ++miss;
			  if (miss == 1) {
				  // restart leonardo
				  miss = 0;
				  std::cout << "picking up raphael" << std::endl;
				  cpen333::process::subprocess raph("raphael", true, true);
			  }
		  }

		  last_raphael= next_raphael;

    std::this_thread::sleep_for(std::chrono::seconds(5));
  }

  return 0;
}

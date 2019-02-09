#include "turtles.h"
#include <cpen333/process/shared_memory.h>
#include <cpen333/process/mutex.h>
#include <cpen333/process/subprocess.h>
#include <thread>

//XXX Leo -> Donny ->Mikey ->Raph ->Leo

int main() {

  cpen333::process::shared_object<TurtleMemory> memory(TURTLE_MEMORY_NAME);
  cpen333::process::mutex mutex("q4_turtle_mutex");
  //========================================================
  // TODO: Implement Donatello
  //       - Initialize his memory
  //       - check-in
  //       - check if defeated
  //       - check on other turtle(s), restart if necessary
  //========================================================

  // re-initialize my memory
  {

    // adding lock_guard for mutual exclutsion since raphael is accessing shared data

   std::lock_guard<cpen333::process::mutex> lock(mutex);
    memory->raphael.checkin = 0;
  }

  // take care of michelangelo
  int last_leonardo = -1;
  int next_leonardo = 0;
  int miss = 0;
  while (true) {


      // adding lock_guard for mutual exclutsion since raphael is accessing shared data
  {
      std::lock_guard<cpen333::process::mutex> lock(mutex);
      memory->raphael.checkin++;
      next_leonardo = memory->leonardo.checkin;
  }
      // check on michelangelo and restart if necessary
      if (last_leonardo == next_leonardo) {
        ++miss;
        if (miss == 1) {
          // restart leonardo
          miss = 0;
          std::cout << "picking up leonardo" << std::endl;
          cpen333::process::subprocess leo("leonardo", true, true);
        }
      }

      last_leonardo = next_leonardo;

   std::this_thread::sleep_for(std::chrono::seconds(5));
  }

  return 0;
}

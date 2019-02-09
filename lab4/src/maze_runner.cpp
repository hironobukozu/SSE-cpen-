#include "maze_runner_common.h"

#include <cpen333/process/shared_memory.h>
#include <cpen333/process/mutex.h>
#include <cstring>
#include <chrono>
#include <thread>

class MazeRunner {

  cpen333::process::shared_object<SharedData> memory_;
  cpen333::process::mutex mutex_;

  // local copy of maze
  MazeInfo minfo_;

  // runner info
  size_t idx_;   // runner index
  int loc_[2];   // current location

 public:

  MazeRunner() : memory_(MAZE_MEMORY_NAME), mutex_(MAZE_MUTEX_NAME),
                 minfo_(), idx_(0), loc_() {

    // copy maze contents
    minfo_ = memory_->minfo;

    {
      // protect access of number of runners
      //std::lock_guard<decltype(mutex_)> lock(mutex_);
      idx_ = memory_->rinfo.nrunners;
      memory_->rinfo.nrunners++;
    }

    // get current location
    loc_[COL_IDX] = memory_->rinfo.rloc[idx_][COL_IDX];
    loc_[ROW_IDX] = memory_->rinfo.rloc[idx_][ROW_IDX];

  }

  /**
   * Solves the maze, taking time between each step so we can actually see progress in the UI
   * @return 1 for success, 0 for failure, -1 to quit
   */
  int go() {
	  // current location
	  int c = loc_[COL_IDX];
	  int r = loc_[ROW_IDX];

	  std::this_thread::sleep_for(std::chrono::milliseconds(100));

	  //==========================================================
	  // TODO: NAVIGATE MAZE
	  //==========================================================

	  while(minfo_.maze[c][r] != 'E') {
      int new_row = r;
      int new_col = c;
	  while (true) {
		  if (minfo_.maze[c][r - 1] == ' ') { //left
			  new_row = r - 1;
			  break;
		  }
		  else if (minfo_.maze[c][r + 1] == ' ') { //right
			  new_row = r + 1;
			  break;
		  }
		  else if (minfo_.maze[c - 1][r] == ' ') { //up
			  new_col = c - 1;
			  break;
		  }
		  else if (minfo_.maze[c + 1][r] == ' ') { //down
			  new_col = c + 1;
			  break;
		  }
	  }

      memory_->rinfo.rloc[idx_][ROW_IDX] = new_row;
      memory_->rinfo.rloc[idx_][COL_IDX] = new_col;
	  r = new_row;
	  c = new_col;

      if(memory_ -> quit == 1){
        return -1;
      }

	  }


    if(minfo_.maze[c][r] == 'E'){
      return 1;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // failed to find exit
    return 0;
  }

  bool quit() {
	  // check if we need to quit
	  return memory_->quit;
  }

  bool magic() {
	  if (memory_->magic != 123123123) {
		  std::cout << memory_->magic << std::endl;
		  std::cout << "Error: SharedData not initialized" << std::endl;
		  std::cin.get();
		  memory_->quit = true;
		  return memory_->quit;
	  }
  }

};

int main() {


  MazeRunner runner;

  runner.magic();

  //while (!runner.quit()) {
	  runner.go();
  //}

  return 0;
}

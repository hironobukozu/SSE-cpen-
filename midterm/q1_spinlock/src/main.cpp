#include "SpinLock.h"

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <exception>

void dangerous_increment(long& counter) {

  // randomly throw an exception
  static auto rand = std::default_random_engine((int)std::chrono::system_clock::now().time_since_epoch().count());
  static auto unif = std::uniform_real_distribution<double>(0, 1);
  if (unif(rand) < 0.00000001) {
    throw std::exception();
  }

  // increment
  ++counter;
}

void thread_increment(long& counter) {
	SpinLock spinlock;
  //====================================================
  // TODO: SAFELY increment by one at a time
  //====================================================
  try {
    for (int i = 0; i < 1000; ++i) {
		if (spinlock.try_lock()) {
			spinlock.lock();
			++counter;
			//dangerous_increment(counter);
			spinlock.unlock();
		}
    }
  } catch (std::exception& ex) {
    std::cout << "EXCEPTION!!" << std::endl;
  }
}

int main() {

  long counter = 0;

  //=========================================================
  // TODO: create and run 5 threads calling thread_increment
  //=========================================================
  //create a vector for threads
  std::vector<std::thread> threads;
  SpinLock spin;

  for (int i=0; i<5; ++i) {
    threads.push_back(std::thread(thread_increment,std::ref(counter)));
  }

  for (int i=0; i<5; ++i) {
    threads[i].join();
  }

  
  std::cout << "Counter value: " << counter << std::endl;

  std::cout<<"Press ENTER to continue.."<<std::endl;
  std::cin.get();

  return 0;
}

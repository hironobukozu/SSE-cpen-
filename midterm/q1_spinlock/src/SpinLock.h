#ifndef MIDTERM_Q1_SPINLOCK_H
#define MIDTERM_Q1_SPINLOCK_H

#include <atomic>
#include <thread>

class SpinLock {
  std::atomic_flag flag_;

 public:

  SpinLock() : flag_{ATOMIC_FLAG_INIT} {}

  /**
   * Acquires the lock, blocking if necessary
   */
  void lock() {
	  //=======================================
	  // TODO: Implement lock operation
	  //=======================================

	  //locks the lock by setting it to true
	  while (flag_.test_and_set(std::memory_order_acquire));
  }

  /**
   * Tries to acquire the lock
   * @return true if lock is available and acquired successfully, false otherwise
   */
  bool try_lock() {
    //=======================================
    // TODO: Implement try_lock operation
    //=======================================

    //checks if lock is acquired
	  if(flag_.test_and_set(std::memory_order_acquire)) {
		  return true;
	  }
    return false;
  }

  /**
   * Releases or unlocks the lock, regardless of who may have locked it
   */
  void unlock() {
    //=======================================
    // TODO: Implement unlock operation
    //=======================================
    //releases and unlocks the lock
    flag_.clear(std::memory_order_release);
  }
};

#endif

#ifndef MIDTERM_ROLLERCOASTER_H
#define MIDTERM_ROLLERCOASTER_H

//=============================================================
// TODO: Add names and layouts for any shared resources
//=============================================================
#define MAZE_MEMORY_NAME "rollercoaster"
#define MAZE_MUTEX_NAME "rollercoaster_mutex"

struct SharedData {
	cpen333::process::semaphore entry_;
	cpen333::process::semaphore exit_;
	cpen333::process::semaphore full_;
	cpen333::process::semaphore empty_;
	cpen333::process::semaphore waiting_;
};

#define ROLLERCOASTER_CAPACITY 4

#endif //MIDTERM_ROLLERCOASTER_H

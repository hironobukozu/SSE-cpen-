#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <random>
using namespace std;

// partitions elements low through high (inclusive)
// around a pivot and returns the pivot index
int partition(vector<int>& data, int low, int high) {
  int pivot = data[high];
  while(low<high){
    while(data[low]<pivot){
      low++;
    }
    while(data[high]>pivot){
      high--;
    }
    if(data[low]==data[high]){
		low++;
    }else if(low<high){
      int temp = data[low];
      data[low] = data[high];
      data[high] = temp;
    }
  }
  return high;
}



// sorts elements low through high (inclusive) using a single thread
void quicksort(vector<int>& data, int low, int high) {
  if(low<high){
    int j = partition(data,low,high);
    quicksort(data,low,j-1);
    quicksort(data,j+1,high);
  }
}

// sorts elements low through high (inclusive) using multiple threads
void parallel_quicksort(vector<int>& data, int low, int high) {
  if(low<high){
  int j = partition(data,low,high);
  thread thread1(quicksort,data,low,j-1);
  thread thread2(quicksort,data,j+1,high);
  thread1.join();
  thread2.join();
}
}

int main() {

  // create two copies of random data
  const int VECTOR_SIZE = 10000;
  vector<int> v1(VECTOR_SIZE, 0);
  // fill with random integers
  for (int i=0; i<VECTOR_SIZE; ++i) {
    v1[i] = rand();
  }
  std::vector<int> v2 = v1;  // copy all contents

  // sort v1 using sequential algorithm
  auto t11 = std::chrono::high_resolution_clock::now();
  quicksort(v1, 0, (int)v1.size()-1);
  auto t12 = std::chrono::high_resolution_clock::now();
  auto duration = t12 - t11;
  auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
  long ms = duration_ms.count();
  cout << "regular sorting took"<< ms <<"ms"<< endl;

  // sort v2 using parallel algorithm
  auto t21 = std::chrono::high_resolution_clock::now();
  parallel_quicksort(v2, 0, (int)v2.size()-1);
  auto t22 = std::chrono::high_resolution_clock::now();
  auto duration_parallel = t22 - t21;
  auto duration_parallel_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration_parallel);
  long ms_parallel = duration_parallel_ms.count();
  cout<<"parallel sorting took"<<ms_parallel<<"ms"<<endl;

  std::cin.get();

  return 0;
}

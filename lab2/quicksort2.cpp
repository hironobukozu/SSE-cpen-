#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <random>
using namespace std;

// partitions elements low through high (inclusive)
// around a pivot and returns the pivot index
int partition(std::vector<int>& data, int low, int high) {
  int pivot = data[low+high/2];
  int temp;
  while(low <= high){
    while(data[low]<pivot){
      low++;
    }
    while(data[high]>pivot){
      high--;
    }
    if(low<=high){
      temp = data[low];
      data[low] = data[high];
      data[high] = temp;
      low++;
      high--;
    }
  }
  return low+1;
}

// sorts elements low through high (inclusive) using a single thread
void quicksort(std::vector<int>& data, int low, int high) {
  int a = low,b=high;
  partition(data,a,b);
  if(low<b){
    quicksort(data,low,b);
  }
  if(a<high){
    quicksort(data,a,high);
  }

}

// sorts elements low through high (inclusive) using multiple threads
void parallel_quicksort(std::vector<int>& data, int low, int high) {
  int a = low, b = high;
  partition(data,a,b);
  std::thread thread1(quicksort,data,low,b);
  std::thread thread2(quicksort,data,a,high);
  thread1.join();
  thread2.join();
}

int main() {

  // create two copies of random data
  const int VECTOR_SIZE = 20;
  std::vector<int> v1(VECTOR_SIZE, 0);
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
  std::cout << "parallel sorting took"<< ms <<"ms"<< std::endl;

  // sort v2 using parallel algorithm
  auto t21 = std::chrono::high_resolution_clock::now();
  parallel_quicksort(v2, 0, (int)v2.size()-1);
  auto t22 = std::chrono::high_resolution_clock::now();
  auto duration_parallel = t21 - t22;
  std::chrono::duration_cast<std::chrono::milliseconds>(duration);
  auto duration_parallel_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration_parallel);
  long ms_parallel = duration_parallel_ms.count();
  std::cout<<"parallel sorting took"<<ms_parallel<<"ms"<<std::endl;

  std::cin.get();

  return 0;
}

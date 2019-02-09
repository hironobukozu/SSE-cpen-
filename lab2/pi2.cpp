#include <thread>
#include <iostream>
#include <random>

void pi_sampler(std::vector<bool>& hits, int idx) {

  // single instance of random engine and distribution
  static std::default_random_engine rnd;
  static std::uniform_real_distribution<double> dist(-1.0, 1.0);
  double x,y,z;
  double count;
  for (int i = 0; i < idx; i++) {
    x = dist(rnd);
    y = dist(rnd);
    z = x*x+y*y;
    if(z<=1){
      hits[idx] = true;
    }else{
      hits[idx] = false;
    }
  }


}

// naively uses multithreading to try to speed up computations
double estimate_pi_multithread_naive(int nsamples) {
  // stores whether each sample falls within circle
  std::vector<bool> hits(nsamples, false);

  // create and store all threads
  std::vector<std::thread> threads;
  for (int i=0; i<nsamples; ++i) {
    threads.push_back(std::thread(pi_sampler, std::ref(hits), i));
  }

  // wait for all threads to complete
  for (int i=0; i<nsamples; ++i) {
    threads[i].join();
  }

  // estimate our value of PI
  double pi = 0;
  for (int i=0; i<nsamples; ++i) {
    if (hits[i]) {
      pi = pi + 1;
    }
  }
  pi = pi / nsamples*4;

  return pi;
}
int main(){
  double pi = estimate_pi_multithread_naive(1000);
  std::cout << "My estimate of PI is: "<<pi<<std::endl;

  return 0;
}

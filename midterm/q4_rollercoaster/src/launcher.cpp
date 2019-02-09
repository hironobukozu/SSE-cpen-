#include <cpen333/process/subprocess.h>
#include <thread>
#include <chrono>

int main() {

  // launch a single roller coaster
  cpen333::process::subprocess rollercoaster("./rollercoaster", true, true);

  // launch a bunch of persons
  const int npeople = 7;
  for (int i=0; i<npeople; ++i) {
    cpen333::process::subprocess person("./passenger", true, true);
  }

  // waits 10 seconds
  std::this_thread::sleep_for(std::chrono::seconds(5));
  for (int i=0; i<npeople; ++i) {
    cpen333::process::subprocess person("./passenger", true, true);
  }

  return 0;
}
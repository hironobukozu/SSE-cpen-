#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cpen333/process/mutex.h>
#include <cpen333/process/shared_memory.h>
#include <cpen333/process/subprocess.h>





int main(){

	for (int i = 0; i < 2; i++) {
		std::vector<std::string> cmd;
		cmd.push_back("malware");
		cmd.push_back(std::to_string(i));
		cmd.push_back("oindex");
		cpen333::process::subprocess processes(cmd, true, true);

	}

  return 0;
}

#include <cpen333/process/subprocess.h>
#include <cpen333/process/mutex.h>

int main() {

  // shared inter-process mutex
  cpen333::process::mutex mutex("system_logger");

  // list of child processes
  std::vector<cpen333::process::subprocess> processes;

  const int nprocesses = 20;
  const int nmessages = 100;
  const std::string logfile = "system_log.txt";

  for (int i=0; i<nprocesses; ++i) {
    std::vector<std::string> cmd;
    cmd.push_back("./system_logger_child");
    cmd.push_back(std::to_string(i));
    cmd.push_back("system_log.text");
    cmd.push_back("100");
    cpen333::process::subprocess processes(cmd,true,true);
    //=================================================
    //  RUN CHILD PROCESSES (system_logger_child)
    //      Process arguments:
    //          - a name for identification in the log
    //          - a log filename to append to
    //          - a number of messages to append
    //=================================================

  }
  for (auto& process : processes) {
	  process.start();
  }

  // wait for processes to finish
  for (auto& process : processes) {
    process.join();
  }

  // unlink mutex since we and all child processes are done with it
  mutex.unlink();

  // pause, waiting for keyboard input
  cpen333::pause();
  return 0;
}

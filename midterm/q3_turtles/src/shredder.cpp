#include "turtles.h"
#include <cpen333/util.h>
#include <cpen333/process/shared_memory.h>
#include <cpen333/process/mutex.h>
#include <iostream>

void show_menu() {

  std::cout << "===================================" << std::endl;
  std::cout << "=        SHREDDER'S MENU          =" << std::endl;
  std::cout << "===================================" << std::endl;
  std::cout << " (1) Leonardo" << std::endl;
  std::cout << " (2) Michelangelo" << std::endl;
  std::cout << " (3) Donatello" << std::endl;
  std::cout << " (4) Raphael" << std::endl;
  std::cout << " (5) All" << std::endl;
  std::cout << "===================================" << std::endl;
  std::cout << "Enter menu item: ";
  std::cout.flush();

}

int main() {

  cpen333::process::shared_object<TurtleMemory> memory(TURTLE_MEMORY_NAME);

  //==========================================================
  // TODO: Implement synchronization and attacking of turtles
  //==========================================================

  bool quit = false;
  do {
    show_menu();
    char c;
    std::cin >> c;
    switch (c) {
      case '1': {
        std::cout << "defeating leonardo" << std::endl;
        break;
      }
      case '2': {
        std::cout << "defeating michelangelo" << std::endl;
        break;
      }
      case '3': {
        std::cout << "defeating donatello" << std::endl;
        break;
      }
      case '4': {
        std::cout << "defeating raphael" << std::endl;
        break;
      }
      case '5': {
        quit = true;
        break;
      }
      default: {
        std::cout << "Invalid entry: " << c << std::endl;
        break;
      }

    }
  } while (!quit);

  std::cout << "Shredder wins!" << std::endl << std::endl;
  cpen333::pause();

  return 0;
}
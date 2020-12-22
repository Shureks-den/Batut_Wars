#include <iostream>
#include <stdexcept>

#include "Game.h"

int main() {
  try {
    Game game;
    game.run();
  } catch (std::exception& exeption) {
    std::cout << std::endl << "EXCEPTION: " << exeption.what() << std::endl;
  }
}

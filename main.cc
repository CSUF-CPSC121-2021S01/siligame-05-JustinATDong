#include <iostream>

#include "game.h"

int main() {
  Game game1;
  game1.Init();
  game1.Start(game1.GetGameScreen());
  return 0;
}

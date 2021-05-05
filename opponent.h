#include <memory>

#include "game_element.h"

#ifndef OPPONENT_H
#define OPPONENT_H

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile(int x, int y) : GameElement(x, y, 9, 23) {}
  OpponentProjectile() : GameElement(0, 0, 5, 5) {}
  void Draw(graphics::Image &board);
  void Move(const graphics::Image &image);
};

class Opponent : public GameElement {
 public:
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
  Opponent() : GameElement(0, 0, 50, 50) {}
  void Draw(graphics::Image &board);
  void Move(const graphics::Image &image);

  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int beam_firing_rate = 0;
};

#endif

#include "opponent.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameElement {
 public:
  Player(int x, int y) : GameElement(x, y, 50, 50) {}
  Player() : GameElement(0, 0, 50, 50) {}
  void Draw(graphics::Image &canvas);
  void Move(const graphics::Image &image);
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile(int x, int y) : GameElement(x, y, 9, 24) {}
  PlayerProjectile() : GameElement(0, 0, 5, 5) {}
  void Draw(graphics::Image &canvas);
  void Move(const graphics::Image &image);
};

#endif

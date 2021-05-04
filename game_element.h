#include <iostream>

#include "cpputils/graphics/image.h"

#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

class GameElement {
 public:
  GameElement() : x_(0), y_(0), width_(50), height_(50) {}
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height), is_active(true) {}

  void SetX(int x) { x_ = x; }

  void SetY(int y) { y_ = y; }

  void SetWidth(int width) { width_ = width; }

  void SetHeight(int height) { height_ = height; }

  void SetIsActive(bool active) { is_active = active; }

  int GetX() const { return x_; }

  int GetY() const { return y_; }

  int GetWidth() const { return width_; }

  int GetHeight() const { return height_; }

  bool GetIsActive() const { return is_active; }

  virtual void Draw(graphics::Image &board) = 0;

  virtual void Move(const graphics::Image &image) = 0;

  bool IntersectsWith(GameElement *characters);

  bool IsOutOfBounds(const graphics::Image &image);

 private:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active;
};

#endif

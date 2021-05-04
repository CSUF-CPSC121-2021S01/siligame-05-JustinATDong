#include "player.h"

void Player::Draw(graphics::Image &canvas) {
  graphics::Image Plane;
  Plane.Load("Player.bmp");
  for (int i = 0; i < Plane.GetHeight(); i++) {
    for (int j = 0; j < Plane.GetWidth(); j++) {
      canvas.SetColor(GetX() + j, GetY() + i, Plane.GetColor(j, i));
    }
  }
}
void Player::Move(const graphics::Image &image) {}

void PlayerProjectile::Draw(graphics::Image &canvas) {
  graphics::Image Bullet;
  Bullet.Load("PlayerProjectile.bmp");
  for (int i = 0; i < Bullet.GetHeight(); i++) {
    for (int j = 0; j < Bullet.GetWidth(); j++) {
      canvas.SetColor(GetX() + j, GetY() + i, Bullet.GetColor(j, i));
    }
  }
}

void PlayerProjectile::Move(const graphics::Image &image) {
  SetY(GetY() - 8);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}

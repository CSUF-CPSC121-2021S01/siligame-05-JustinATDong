#include "opponent.h"

#include "cpputils/graphics/image.h"

// Opponent Functions
void Opponent::Draw(graphics::Image &canvas) {
  graphics::Image UFO;
  UFO.Load("Opponent.bmp");
  for (int i = 0; i < UFO.GetHeight(); i++) {
    for (int j = 0; j < UFO.GetWidth(); j++) {
      canvas.SetColor(GetX() + j, GetY() + i, UFO.GetColor(j, i));
    }
  }
}

void Opponent::Move(const graphics::Image &image) {
  SetY(GetY() + 1);
  SetX(GetX() + 1);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  if (beam_firing_rate >=10) {
    beam_firing_rate = 0;
    std::unique_ptr<OpponentProjectile> BeamofLight;
    BeamofLight = std::make_unique<OpponentProjectile>();
      return std::move(BeamofLight);
  } else {
    beam_firing_rate++;
    return nullptr;
  }
}

void OpponentProjectile::Draw(graphics::Image &canvas) {
  graphics::Image Beam;
  Beam.Load("OpponentProjectile.bmp");
  for (int i = 0; i < Beam.GetHeight(); i++) {
    for (int j = 0; j < Beam.GetWidth(); j++) {
      canvas.SetColor(GetX() + j, GetY() + i, Beam.GetColor(j, i));
    }
  }
}

void OpponentProjectile::Move(const graphics::Image &image) {
  SetY(GetY() + 1);
  SetX(GetX() + 1);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}

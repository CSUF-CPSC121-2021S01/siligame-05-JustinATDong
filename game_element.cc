#include "game_element.h"

bool GameElement::IsOutOfBounds(const graphics::Image &image) {
  if (GetX() < 0 || GetX() + GetWidth() > image.GetWidth()) {
    return true;
  } else if (GetY() < 0 || GetY() + GetHeight() > image.GetHeight()) {
    return true;
  } else {
    return false;
  }
}
bool GameElement::IntersectsWith(GameElement *characters) {
  return !(GetX() > characters->GetX() + characters->GetWidth() ||
           characters->GetX() > GetX() + GetWidth() ||
           GetY() > characters->GetY() + characters->GetHeight() ||
           characters->GetY() > GetY() + GetHeight());
}

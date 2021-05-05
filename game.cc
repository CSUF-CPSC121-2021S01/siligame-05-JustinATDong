#include "game.h"

void Game::Init() {
  board_.AddMouseEventListener(*this);
  board_.AddAnimationEventListener(*this);
  Plane_.SetX(10);
  Plane_.SetY(board_.GetHeight() - 75);
}

void Game::CreateOpponents() {
  for (int i = 0; i < 5; i++) {
    UFO_.push_back(std::make_unique<Opponent>(50 * i + 15, 50));
  }
}

int Game::GetScore() { return game_score; }

bool Game::HasLost() { return YouLost; }

void Game::UpdateScreen() {
  board_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  for (int i = 0; i < UFO_.size(); i++) {
    if (UFO_[i]->GetIsActive() == true) {
      UFO_[i]->Draw(board_);
    }
  }
  for (int i = 0; i < Beam_.size(); i++) {
    if (Beam_[i]->GetIsActive() == true) {
      Beam_[i]->Draw(board_);
    }
  }
  for (int i = 0; i < Bullet_.size(); i++) {
    if (Bullet_[i]->GetIsActive() == true) {
      Bullet_[i]->Draw(board_);
    }
  }
  if (Plane_.GetIsActive() == true) {
    Plane_.Draw(board_);
  }

  board_.DrawText(10, 10, std::to_string(game_score), 35, 0, 0, 0);
}

void Game::MoveGameElements() {
  for (int i = 0; i < Bullet_.size(); i++) {
    Bullet_[i]->Move(board_);
  }
  for (int i = 0; i < Beam_.size(); i++) {
    Beam_[i]->Move(board_);
  }
  for (int i = 0; i < UFO_.size(); i++) {
    UFO_[i]->Move(board_);
  }
}

void Game::FilterIntersections() {
  // plane and UFO
  for (int j = 0; j < UFO_.size(); j++) {
    if (Plane_.IntersectsWith(UFO_[j].get()) == true) {
      Plane_.SetIsActive(false);
      UFO_[j]->SetIsActive(false);
      YouLost = true;
    }
  }
  // Beam and Plane
  for (int i = 0; i < Beam_.size(); i++) {
    if (Beam_[i]->IntersectsWith(&Plane_) == true) {
      Plane_.SetIsActive(false);
      Beam_[i]->SetIsActive(false);
      YouLost = true;
    }
  }
  // Bullet and UFO
  for (int p = 0; p < Bullet_.size(); p++) {
    for (int k = 0; k < UFO_.size(); k++) {
      if (Bullet_[p]->IntersectsWith(UFO_[k].get()) == true) {
        Bullet_[p]->SetIsActive(false);
        UFO_[k]->SetIsActive(false);
        if (Plane_.GetIsActive() == true) {
          game_score++;
        }
      }
    }
  }
}
void Game::OnAnimationStep() {
  if (UFO_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  board_.Flush();
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < UFO_.size(); i++) {
    if (UFO_[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> Cannon;
      Cannon = std::make_unique<OpponentProjectile>();
      Cannon->SetX(UFO_[i]->GetX());
      Cannon->SetY(UFO_[i]->GetY());
      Beam_.push_back(std::move(Cannon));
    }
  }
}

void Game::OnMouseEvent(const graphics::MouseEvent &mouse) {
  if (mouse.GetX() > 0 && mouse.GetY() > 0 &&
      mouse.GetX() < board_.GetWidth() && mouse.GetY() < board_.GetHeight()) {
    Plane_.SetX(mouse.GetX() - 25);
    Plane_.SetY(mouse.GetY() - 25);
  }
  if (mouse.GetMouseAction() == graphics::MouseAction::kPressed) {
    std::unique_ptr<PlayerProjectile> Missle =
        std::make_unique<PlayerProjectile>(mouse.GetX(), mouse.GetY() + 25);
    Bullet_.push_back(std::move(Missle));
  }
  if (mouse.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> Missle =
        std::make_unique<PlayerProjectile>(mouse.GetX(), mouse.GetY() + 25);
    Bullet_.push_back(std::move(Missle));
  }
}

void Game::RemoveInactive() {
  for (int i = Bullet_.size() - 1; i >= 0; i--) {
    if (Bullet_[i]->GetIsActive() == false) {
      Bullet_.erase(Bullet_.begin() + i);
    }
  }
  for (int i = Beam_.size() - 1; i >= 0; i--) {
    if (Beam_[i]->GetIsActive() == false) {
      Beam_.erase(Beam_.begin() + i);
    }
  }
  for (int i = UFO_.size() - 1; i >= 0; i--) {
    if (!UFO_[i]->GetIsActive()) {
      UFO_.erase(UFO_.begin() + i);
    }
  }
}

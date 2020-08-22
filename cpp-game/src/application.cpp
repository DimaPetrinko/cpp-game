/**
 * @author      : potapchukanatoliy (potapchukanatoliy@penguin)
 * @file        : application
 * @created     : Saturday Aug 22, 2020 19:20:05 EEST
 */

#include "application.h"
#include <iostream>

const int kWindowWidth = 640;
const int kWindowHeight = 480;

void Application::Start() {
  renderer_ = std::make_unique<OGL>(kWindowWidth, kWindowHeight);
  renderer_->Init();

  controls_ = std::make_unique<GameControls>();
  controls_->Init();

  game_ = std::make_unique<Game>(controls_.get(), renderer_.get());
  game_->Init();

  while (!ShouldExit()) {
    std::cout << " LOOP LOOP.\n";

  }
}

bool Application::ShouldExit() {
  return renderer_->IsWindowClosed();
}

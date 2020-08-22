/**
 * @author      : potapchukanatoliy (potapchukanatoliy@penguin)
 * @file        : game
 * @created     : Saturday Aug 22, 2020 19:06:50 EEST
 */

#ifndef GAME_H
#define GAME_H

#include "game_controls.h"
#include "OGL.h"

class Game {
  public:
    Game(GameControls* controls, OGL* renderer);

    void Init();
    void Update();
  private:
    GameControls* controls_;
    OGL* renderer_;
};


#endif /* end of include guard GAME_H */


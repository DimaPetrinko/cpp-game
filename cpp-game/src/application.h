/**
 * @author      : potapchukanatoliy (potapchukanatoliy@penguin)
 * @file        : application
 * @created     : Saturday Aug 22, 2020 19:10:15 EEST
 */

#ifndef APPLICATION_H

#define APPLICATION_H

#include <memory>

#include "game_controls.h"
#include "game.h"
#include "OGL.h"

// Responsible for the lifecycle of the game, connects Game, Renderer and Controls.
class Application {
  public:
    void Start();

  private:
    // Whether we should close the game now.
    bool ShouldExit();

    std::unique_ptr<OGL> renderer_;
    std::unique_ptr<GameControls> controls_;
    std::unique_ptr<Game> game_;
};


#endif /* end of include guard APPLICATION_H */


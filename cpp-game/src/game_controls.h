/**
 * @author      : potapchukanatoliy (potapchukanatoliy@penguin)
 * @file        : game_controls
 * @created     : Saturday Aug 22, 2020 19:16:08 EEST
 */

#ifndef GAME_CONTROLS_H

#define GAME_CONTROLS_H

class GameControls {
  public:
    enum class KeyState {
      ON, OFF
    };

    GameControls();

    void Init();

    KeyState GetKeyState(int key);
  private:
};


#endif /* end of include guard GAME_CONTROLS_H */


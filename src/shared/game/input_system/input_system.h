#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "raylib.h"

namespace game
{
  enum KeyCode
  {
    KEY_UP = KEY_UP,
    KEY_DOWN = KEY_DOWN,
    KEY_LEFT = KEY_LEFT,
    KEY_RIGHT = KEY_RIGHT,
  };

  class Input
  {
  public:
    inline static bool isKeyDown(int keyKode)
    {
      return IsKeyDown(keyKode);
    }
  };
};

#endif
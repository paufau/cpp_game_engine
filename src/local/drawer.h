#ifndef DRAWER_H
#define DRAWER_H

#include "../shared/game/loop/component/component.h"
#include "../shared/game/loop/controlls/transform/transform.h"
#include "../shared/game/loop/controlls/sprite/sprite.h"
#include "../shared/game/loop/controlls/animated_sprite/animated_sprite.h"
#include "../shared/game/loop/component/accessor/accessor.h"
#include "../shared/game/input_system/input_system.h"

class Drawer : public Component
{
private:
  int direction = 1;
  float speed = 100;

  game::Accessor<game::Transform> transform;
  game::Accessor<game::AnimatedSprite> sprite;

public:
  void prepare() override
  {
    transform = attach<game::Transform>();
    sprite = attach<game::AnimatedSprite>("resources/New Piskel.png", 7, 0.09);

    sprite.get()->scale = 2;
    transform.get()->rectangle.y = 100;
  }

  void update(float deltaTime) override
  {
    if (transform.get()->rectangle.x < 20)
    {
      direction = 1;
      sprite.get()->wFlipModifier = 1;
    }
    else if (transform.get()->rectangle.x > 300)
    {
      direction = -1;
      sprite.get()->wFlipModifier = -1;
    }

    if (game::Input::isKeyDown(game::KeyCode::KEY_UP))
    {
      transform.get()->rectangle.y -= speed * deltaTime;
    }
    else if (game::Input::isKeyDown(game::KeyCode::KEY_DOWN))
    {
      transform.get()->rectangle.y += speed * deltaTime;
    }

    transform.get()->rectangle.x += speed * direction * deltaTime;
  }
};

#endif
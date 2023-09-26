#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"
#include "../../component/component.h"
#include "../../component/accessor/accessor.h"
#include "../transform/transform.h"
#include <iostream>

namespace game
{
  class Sprite : public Component
  {
  public:
    Sprite() : Component(false){};
    Sprite(char *imageSrc) : Component(false)
    {
      this->imageSrc = imageSrc;
    }
    Sprite(const char *imageSrc) : Component(false)
    {
      this->imageSrc = const_cast<char *>(imageSrc);
    }
    ~Sprite()
    {
      std::cout << "Destroy" << std::endl;
    };

    char *imageSrc;
    Texture2D texture;
    game::Accessor<game::Transform> transform;

    float scale = 1;
    float hFlipModifier = 1;
    float wFlipModifier = 1;

    void prepare() override
    {
      texture = LoadTexture(imageSrc);
      transform = attach<game::Transform>();
    }

    void draw() override
    {
      DrawTexturePro(
          this->texture,
          (Rectangle){
              0.0,
              0.0,
              (float)(this->wFlipModifier * this->texture.width),
              (float)(this->hFlipModifier * this->texture.height)},
          (Rectangle){
              transform.get()->position.x,
              transform.get()->position.y,
              (float)this->texture.width * this->scale,
              (float)this->texture.height * this->scale},
          (Vector2){0.0, 0.0}, // transforms origin
          0,                   // rotation
          WHITE);
    }
  };
};

#endif
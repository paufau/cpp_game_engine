#ifndef ANIMATED_SPRITE
#define ANIMATED_SPRITE

#include "../sprite/sprite.h"
#include <iostream>

namespace game
{
  class AnimatedSprite : public Sprite
  {
  public:
    AnimatedSprite(const char *imageSrc, int framesCount, float timePerFrame) : Sprite(imageSrc)
    {
      this->framesCount = framesCount;
      this->timePerFrame = timePerFrame;
    }

    int framesCount;
    int currentFrame;
    int frameWidth;
    float timePerFrame;
    float timeFromPrevFrame;

    void prepare() override
    {
      Sprite::prepare();
      frameWidth = (int)(texture.width / framesCount); // Count starts from zero
      currentFrame = 0;
      timeFromPrevFrame = 0;
      framesCount--;
    }

    void update(float deltaTime) override
    {
      timeFromPrevFrame += deltaTime;

      if (timeFromPrevFrame >= timePerFrame)
      {
        timeFromPrevFrame = 0;
        currentFrame++;
        if (currentFrame > framesCount)
        {
          currentFrame = 0;
        }
      }
    }

    void draw() override
    {
      DrawTexturePro(
          texture,
          (Rectangle){
              (float)(frameWidth * currentFrame),
              0.0,
              (float)(wFlipModifier * frameWidth),
              (float)(hFlipModifier * texture.height)},
          (Rectangle){
              transform.get()->rectangle.x,
              transform.get()->rectangle.y,
              (float)frameWidth * scale,
              (float)texture.height * scale},
          (Vector2){0.0, 0.0}, // transforms origin
          0,                   // rotation
          WHITE);
    }
  };
};

#endif
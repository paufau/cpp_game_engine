#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "raylib.h"
#include "../../component/component.h"
#include <iostream>

namespace game
{
  class Transform : public Component
  {
  public:
    Transform() : Component(false)
    {
      std::cout << "Create transform" << std::endl;
    };
    Transform(float x, float y, float width, float height) : Component(false)
    {
      this->position = (Rectangle){x, y, width, height};
    };
    ~Transform()
    {
      std::cout << "Destroy transform" << std::endl;
    }

    Rectangle position = (Rectangle){0, 0, 0, 0};

    void setPosition(float x, float y)
    {
      this->position.x = x;
      this->position.y = y;
    }

    void setSize(float width, float height)
    {
      this->position.width = width;
      this->position.height = height;
    }
  };
};

#endif
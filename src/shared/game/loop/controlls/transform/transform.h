#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "raylib.h"
#include "../../component/component.h"
#include <iostream>

namespace game
{
  struct Position
  {
    Position(float x, float y) : x(x), y(y){};
    float x;
    float y;
  };

  class Transform : public Component
  {
  public:
    Transform() : Component(false)
    {
      std::cout << "Create transform" << std::endl;
    };
    Transform(float x, float y, float width, float height) : Component(false)
    {
      this->rectangle = (Rectangle){x, y, width, height};
    };
    ~Transform()
    {
      std::cout << "Destroy transform" << std::endl;
    }

    // TODO move to private
    Rectangle rectangle = (Rectangle){0, 0, 0, 0};

    void setPosition(Position position)
    {
      this->rectangle.x = position.x;
      this->rectangle.y = position.y;
    }

    void setSize(float width, float height)
    {
      this->rectangle.width = width;
      this->rectangle.height = height;
    }
  };
};

#endif
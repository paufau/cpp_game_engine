#ifndef COLLISTION_SYSTEM_H
#define COLLISTION_SYSTEM_H

#include "../../injector/injectable.h"
#include "../loop/controlls/collider/collider.h"

#include <list>

// IDEA replace list with approximate relative displacement grid/tree

// TODO collision layers
namespace game
{
  class CollisionSystem : public Injectable
  {
  private:
    std::list<Collider *> colliders = {};

  public:
    CollisionSystem(){};

    void addCollider(Collider *collider)
    {
      colliders.push_back(collider);
    }

    void removeCollider(Collider *collider)
    {
      colliders.remove(collider);
    }
  };
};

#endif
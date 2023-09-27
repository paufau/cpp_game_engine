#ifndef COLLIDER_H
#define COLLIDER_H

#include "../../component/component.h"
#include "../transform/transform.h"
#include "../../component/accessor/accessor.h"
#include "../../../bootstrap/bootstrap.h"

namespace game
{
  class Collider : public Component
  {
  private:
    game::Accessor<game::Transform> transform;

  public:
    Collider();
    ~Collider();

    void prepare() override
    {
      transform = attach<game::Transform>();
    }

    void move(game::Position position)
    {
      Component *parent = getParent();

      if (parent == nullptr)
      {
        return;
      }

      game::Accessor<game::Transform> parentTransform = parent->findFirst<game::Transform>();

      if (!parentTransform.exists())
      {
        return;
      }

      // TODO save parent position and revert it on collision

      parentTransform.get()->setPosition(position);
      // TODO check collisions
    }
  };
};

#endif
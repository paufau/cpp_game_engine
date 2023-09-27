#include "./collider.h"
#include "../../../collision_system/collistion_system.h"
#include <memory>

namespace game
{
  Collider::Collider()
  {
    CollisionSystem *cs = GameBootstrap::injector.injectSingleton<CollisionSystem>();
    cs->addCollider(this);
  }

  Collider::~Collider()
  {
    CollisionSystem *cs = GameBootstrap::injector.injectSingleton<CollisionSystem>();
    cs->removeCollider(this);
  }
}

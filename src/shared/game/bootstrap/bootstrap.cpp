#include "./bootstrap.h"

#include "../../injector/injector.h"
#include "../loop/loop_manager.h"
#include "../collision_system/collistion_system.h"

GameBootstrap::GameBootstrap(){};

void GameBootstrap::init()
{
  GameBootstrap bootstrap;

  bootstrap.injector.setBuilder<LoopManager>(
      []()
      { return new LoopManager(); });

  bootstrap.injector.setBuilder<game::CollisionSystem>(
      []()
      { return new game::CollisionSystem(); });
};

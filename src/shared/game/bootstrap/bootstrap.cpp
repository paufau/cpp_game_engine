#include "./bootstrap.h"

#include "../../injector/injector.h"
#include "../loop/loop_manager.h"

GameBootstrap::GameBootstrap(){};

void GameBootstrap::init()
{
  GameBootstrap bootstrap;

  bootstrap.injector.setBuilder<LoopManager>(
      []()
      { return new LoopManager(); });
};

#include "component.h"
#include "../loop_manager.h"
#include "../../bootstrap/bootstrap.h"

Component::Component()
{
  LoopManager *loopManager = GameBootstrap::injector.injectSingleton<LoopManager>();
  loopManager->addController(this);
}

Component::Component(bool isAllowedToHaveChildren)
{
  this->isChildrenHolder = isAllowedToHaveChildren;

  LoopManager *loopManager = GameBootstrap::injector.injectSingleton<LoopManager>();
  loopManager->addController(this);
}

Component::~Component()
{
  LoopManager *loopManager = GameBootstrap::injector.injectSingleton<LoopManager>();
  loopManager->removeController(this);
}

void Component::destroyMe()
{
  this->state = ComponentState::DESTROYED;
  delete (this);
}

void Component::scheduleDestruction()
{
  this->state = ComponentState::DESTROYING;
  LoopManager *loopManager = GameBootstrap::injector.injectSingleton<LoopManager>();
  loopManager->scheduleDesctruction(this);
}

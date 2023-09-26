#ifndef COMPONENT_H
#define COMPONENT_H

#include <list>
#include <string>

#include "./children/children.h"
#include "./family_manager/family_manager.h"

enum ComponentState
{
  CREATED,
  PREPARING,
  PREPARED,
  ACTIVE,
  DESTROYING,
  DESTROYED,
};

class Component : public game::FamilyManager<Component>
{
protected:
  bool isUpdateOverriden = true;
  bool isPrepareOverriden = true;
  bool isDrawOverriden = true;
  ComponentState state = ComponentState::CREATED;

public:
  Component();
  Component(bool);
  ~Component();

  void destroyMe();
  void scheduleDestruction();

  virtual void update(float deltaTime)
  {
    // Needs to be overriden
    isUpdateOverriden = false;
  };

  virtual void prepare()
  {
    // Needs to be overriden
    isPrepareOverriden = false;
  };

  virtual void draw()
  {
    // Needs to be overriden
    isDrawOverriden = false;
  };

  bool shouldCallUpdate()
  {
    return isUpdateOverriden && state == ComponentState::ACTIVE;
  }

  bool shouldCallPrepare()
  {
    return isPrepareOverriden && this->state == ComponentState::CREATED;
  }

  bool shouldCallDestroy()
  {
    return isDrawOverriden && this->state == ComponentState::DESTROYING;
  }

  bool shouldCallDraw()
  {
    return this->state == ComponentState::ACTIVE;
  }

  void processUpdate(float deltaTime)
  {
    if (this->shouldCallUpdate())
    {
      this->update(deltaTime);
    }
  }

  void processDestroy()
  {
    if (this->shouldCallDestroy())
    {
      this->destroyMe();
    }
  }

  void processDraw()
  {
    if (this->shouldCallDraw())
    {
      this->draw();
    }
  }

  void processPrepare()
  {
    if (shouldCallPrepare())
    {
      state = ComponentState::PREPARING;
      prepare();
      state = ComponentState::PREPARED;

      // TODO split preparing state to a separate components queue
      state = ComponentState::ACTIVE;
    }
  }
};

#endif
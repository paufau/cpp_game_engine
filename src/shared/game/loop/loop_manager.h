#ifndef LOOP_H
#define LOOP_H

#include "list"
#include "../../injector/injectable.h"
#include "component/component.h"
#include "raylib.h"
#include <iostream>
#include "component/accessor/accessor.h"

static Color GREEN_SCREEN = (Color){91, 191, 99, 255};

class LoopManager : public Injectable
{
private:
  std::list<Component *> controllers = {};
  std::list<Component *> destroyQueue = {};

public:
  LoopManager(){};

  void addController(Component *controller)
  {
    this->controllers.push_back(controller);
  };

  void removeController(Component *controller)
  {
    this->controllers.remove(controller);
  }

  void scheduleDesctruction(Component *controller)
  {
    this->destroyQueue.push_back(controller);
  }

  void prepare()
  {
    for (auto it = controllers.begin(); it != controllers.end(); ++it)
    {
      (*it)->processPrepare();
    }
  }

  void update()
  {
    float deltaTime = GetFrameTime();

    for (auto it = controllers.begin(); it != controllers.end(); ++it)
    {
      (*it)->processUpdate(deltaTime);
    }
  };

  void draw()
  {
    BeginDrawing();
    ClearBackground(GREEN_SCREEN);

    for (auto it = controllers.begin(); it != controllers.end(); ++it)
    {
      (*it)->processDraw();
    }

    DrawFPS(0, 0);
    EndDrawing();
  };

  void destroy()
  {
    for (auto it = destroyQueue.begin(); it != destroyQueue.end(); ++it)
    {
      (*it)->processDestroy();
    }

    this->destroyQueue.clear();
  }

  void processFrame()
  {
    try
    {
      prepare();
      update();
      draw();
      destroy();
    }
    catch (game::ComponentAccessException e)
    {
      std::cout << "Error occurs while frame processing - " << e.toString() << std::endl;
    }
    catch (game::AssignParentToItself e)
    {
      std::cout << "Error occurs while frame processing - " << e.toString() << std::endl;
    }
  }
};

#endif
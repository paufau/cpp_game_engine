#ifndef GAMEBOOTSTRAP_H
#define GAMEBOOTSTRAP_H

#include "../../injector/injector.h"

class GameBootstrap
{
public:
  GameBootstrap();

  inline static Injector injector = Injector();
  static void init();
};

#endif
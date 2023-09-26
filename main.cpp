#include "raylib.h"

#include "./src/shared/game/bootstrap/bootstrap.h"
#include "./src/shared/game/loop/loop_manager.h"
#include "./src/local/drawer.h"

int main(void)
{
  GameBootstrap::init();

  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "GameApp");

  SetWindowState(FLAG_WINDOW_RESIZABLE);
  // SetTargetFPS(60);

  LoopManager *loopManager = GameBootstrap::injector.injectSingleton<LoopManager>();
  auto d = new Drawer();

  while (!WindowShouldClose())
  {
    loopManager->processFrame();
  }

  delete (d);

  CloseWindow();
  return 0;
}
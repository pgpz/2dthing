#include "raylib.h"

int main(void)
{
  const int screenWidth = 1920;
  const int screenHeight = 1080;

  InitWindow(screenWidth, screenHeight, "pokeidk");

  SetTargetFPS(120);

  while (!WindowShouldClose())
  {
    BeginDrawing();
        ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

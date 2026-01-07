#include "raylib.h"
#include <math.h>

#define MAX_BUILDINGS   100

int main(void)
{
  const int screenWidth = 1920;
  const int screenHeight = 1080;

  InitWindow(screenWidth, screenHeight, "pokeidk");

  Rectangle player = { 400, 280, 40, 40 };

  int spacing = 0;

  Camera2D camera = { 0 };
  camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
  camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

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

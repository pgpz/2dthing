#include "raylib.h"
#include <math.h>

#define STAR_COUNT 200
#define MAX_TREES  30

typedef struct Tree {
  Rectangle trunk;
  Vector2 canopy[3];
} Tree;


int main(void)
{
  const int screenWidth = 1920;
  const int screenHeight = 1080;

  InitWindow(screenWidth, screenHeight, "2DGAMBLINGGAME");

  Rectangle player = { 400, 280, 40, 40 };
  Rectangle floor = { -100000.0f, 400.0f, 200000.0f, 200000.0f };

  float velocityY = 0.0f;
  float velocityX = 0.0f;

  const float gravity = 1200.0f;
  const float dt_cap = 1.0f / 60.0f;

  const float moveSpeed = 400.0f;
  const float jumpForce = 600.0f;

  bool grounded = false;

  Camera2D camera = { 0 };
  camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
  camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  Vector2 stars[STAR_COUNT];
  for (int i = 0; i < STAR_COUNT; i++)
  {
    stars[i].x = GetRandomValue(-5000, 5000);
    stars[i].y = GetRandomValue(-3000, 300);
  }

  Tree trees[MAX_TREES];
  for (int i = 0; i < MAX_TREES; i++)
{
    float trunkWidth  = GetRandomValue(20, 30);
    float trunkHeight = GetRandomValue(60, 120);
    float x;
    bool ok;

    int attempts = 0;
    do {
        ok = true;
        x = GetRandomValue(-1500, 1500);
        for (int j = 0; j < i; j++)
        {
            float dist = fabsf(x - trees[j].trunk.x);
            if (dist < 80)
            {
                ok = false;
                break;
            }
        }
        attempts++;
    } while (!ok && attempts < 100);

    float y = 400 - trunkHeight;

    trees[i].trunk = (Rectangle){ x, y, trunkWidth, trunkHeight };

    float canopyHeight = trunkHeight;
    float canopyWidth  = trunkWidth * 3;

    trees[i].canopy[0] = (Vector2){ x + trunkWidth/2.0f, y - canopyHeight };
    trees[i].canopy[1] = (Vector2){ x - canopyWidth/2.0f + trunkWidth/2.0f, y };
    trees[i].canopy[2] = (Vector2){ x + canopyWidth/2.0f + trunkWidth/2.0f + trunkWidth/2.0f, y };
}
  SetTargetFPS(120);

  while (!WindowShouldClose())
  {

    float dt = GetFrameTime();
    if (dt > 1.0f/60.0f) dt = 1.0f/60.0f;

    velocityX = 0.0f;
    if (IsKeyDown(KEY_A)) velocityX -= moveSpeed;
    if (IsKeyDown(KEY_D)) velocityX += moveSpeed;

    player.x += velocityX * dt;

    if (grounded && IsKeyPressed(KEY_SPACE))
    {
      velocityY = -jumpForce;
      grounded = false;
    }

    velocityY += gravity * dt;
    player.y += velocityY * dt;

    if (CheckCollisionRecs(player, floor))
    {
      player.y = floor.y - player.height;
      velocityY = 0.0f;
      grounded = true;
    }
    else
  {
      grounded = false;
    };

    camera.target = (Vector2){
      player.x + player.width/2.0f,
      player.y + player.height/2.0f
    };

    BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

            for (int i = 0; i < MAX_TREES; i++)
            {
                DrawRectangleRec(trees[i].trunk, (Color){ 139,69,19,255 });
                DrawTriangle(trees[i].canopy[0], trees[i].canopy[1], trees[i].canopy[2], GREEN);
            }

            for (int i = 0; i < STAR_COUNT; i++)
                DrawPixelV(stars[i], RAYWHITE);

        DrawRectangleRec(player, RED);

        DrawRectangleLinesEx(player, 1.0f, BLACK);

        DrawRectangleRec(floor, GREEN);

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

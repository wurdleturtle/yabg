#include "block.h"
#include "camera_controller.h"
#include "input.h"
#include "raylib.h"
#include "raymath.h"
#include "render.h"
#include "world.h"

Block toBlock(Vector3 v) {
  return {
      static_cast<int>(floorf(v.x)),
      static_cast<int>(floorf(v.y)),
      static_cast<int>(floorf(v.z)),
  };
};

int main() {

  // Init Settings:

  InitWindow(800, 600, "Raylib + CMake");

  int halfSize = 16;
  int y = 0;
  BlockType type = BlockType::Dirt;

  Camera3D camera = CreateDefaultPlayerCamera();
  PlayerCameraState cameraState{};

  World world;

  world.GenerateFlat(halfSize, y, type);

  float dt;

  Ray ray;
  RaycastHit rayHit;

  // SetTargetFPS(60);
  DisableCursor();

  while (!WindowShouldClose()) {

    dt = GetFrameTime();
    dt = std::max(dt, 0.001f);

    UpdatePlayerCamera(camera, cameraState, dt);

    ray = GetScreenToWorldRay(
        {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}, camera);
    TraceLog(LOG_INFO, "dir: %f %f %f", ray.direction.x, ray.direction.y,
             ray.direction.z);
    rayHit = world.Raycast(ray, 10.0f);
    rayHit = world.Raycast(ray, 10.0f);

    if (rayHit.hit && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      world.RemoveBlock(rayHit.blockPos);
    if (rayHit.hit && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
      world.AddBlock(
          toBlock(Vector3Add(rayHit.blockPos.toVector3(), rayHit.normal)),
          BlockType::Dirt);

    if (IsKeyPressed(KEY_G))
      world.UpdateFaces();

    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(camera);
    DrawWorld(world);
    if (rayHit.hit)
      DrawSelection(rayHit.blockPos);
    EndMode3D();
    DrawHud(world.GetBlockCount());
    EndDrawing();
  }

  EnableCursor();
  CloseWindow();
}

#include "block.h"
#include "camera_controller.h"
#include "input.h"
#include "raylib.h"
#include "raymath.h"
#include "render.h"
#include "world.h"

Block toBlock(Vector3 v)
{
  return {
      static_cast<int>(floorf(v.x)),
      static_cast<int>(floorf(v.y)),
      static_cast<int>(floorf(v.z)),
  };
};

int main()
{

  // Init Settings:

  InitWindow(800, 600, "Raylib + CMake");

  int halfSize = 16;
  int y = 0;
  Block selectionpos = {0, 0, 0};
  BlockType selectedType = BlockType::Dirt;

  Camera3D camera = CreateDefaultPlayerCamera();
  PlayerCameraState cameraState{};

  const BlockTextureSet blockTextures = LoadBlockTextures();

  World world;

  world.GenerateFlat(halfSize, y, BlockType::Bedrock);

  float dt;

  SetTargetFPS(60);
  DisableCursor();

  while (!WindowShouldClose())
  {
    dt = GetFrameTime();
    dt = std::max(dt, 0.001f);

    UpdatePlayerCamera(camera, cameraState, dt);
    HandleEditorInput(selectionpos, world, selectedType);
    if (IsKeyPressed(KEY_G))
      world.UpdateFaces();
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(camera);
    DrawWorld(world, blockTextures);
    DrawSelection(selectionpos);
    EndMode3D();
    DrawHud(world.GetBlockCount(), selectedType, blockTextures);
    EndDrawing();
  }

  for (auto &tex : blockTextures)
  {
    UnloadTexture(tex);
  }

  EnableCursor();
  CloseWindow();
}

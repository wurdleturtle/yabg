#include "block.h"
#include "camera_controller.h"
#include "input.h"
#include "raylib.h"
#include "render.h"
#include "world.h"

int main() {

  // Init Settings:

  InitWindow(800, 600, "Raylib + CMake");

  Block defaultBlock = {0, 0, 0};

  Camera3D camera = CreateDefaultEditorCamera();

  World world;

  world.AddBlock(defaultBlock);

  Block selectionPos = {0, 0, 0};

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    UpdateEditorCamera(camera, selectionPos);
    HandleEditorInput(selectionPos, world);

    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(camera);
    DrawWorld(world);
    DrawSelection(selectionPos);
    EndMode3D();
    DrawHud(selectionPos, world.GetBlockCount());
    EndDrawing();
  }

  CloseWindow();
}

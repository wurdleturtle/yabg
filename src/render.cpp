#include "render.h"

#include "raylib.h"

void DrawWorld(const World &world) {
  world.ForEachBlock([](const Block &pos, const BlockData &data) {
    (void)data;
    DrawCubeV(pos.toVector3(), {1.0f, 1.0f, 1.0f}, LIGHTGRAY);
    DrawCubeWiresV(pos.toVector3(), {1.0f, 1.0f, 1.0f}, BLACK);
  });
}

void DrawSelection(const Block &selectionPos) {
  DrawCubeWiresV(selectionPos.toVector3(), {1.01f, 1.01f, 1.01f}, WHITE);
}

void DrawHud(const Block &selectionPos, std::size_t blockCount) {
  DrawFPS(10, 10);

  DrawText(TextFormat("Blocks: %i", static_cast<int>(blockCount)), 10, 40, 20,
           RED);
}

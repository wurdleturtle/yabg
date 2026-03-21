#include "render.h"
#include "raylib.h"
#include "rlgl.h"

void DrawWorld(const World &world) {
  world.ForEachBlock([](const Block &pos, const BlockData &data) {
    DrawCubeFaces(data.blockFaces, pos.toVector3());
    DrawCubeWiresV(pos.toVector3(), {1.0f, 1.0f, 1.0f}, BLACK);
  });
}

void DrawSelection(const Block &selectionPos) {
  DrawCubeWiresV(selectionPos.toVector3(), {1.01f, 1.01f, 1.01f}, WHITE);
}

void DrawHud(std::size_t blockCount) {
  DrawFPS(10, 10);

  DrawText(TextFormat("Blocks: %i", static_cast<int>(blockCount)), 10, 40, 20,
           RED);

  DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 5, BLACK);
}

void DrawCubeFaces(Faces faces, Vector3 pos) {
  const float h = 1 * 0.5f;

  const float x0 = pos.x - h;
  const float x1 = pos.x + h;
  const float y0 = pos.y - h;
  const float y1 = pos.y + h;
  const float z0 = pos.z - h;
  const float z1 = pos.z + h;

  rlColor4ub(LIGHTGRAY.r, LIGHTGRAY.g, LIGHTGRAY.b, LIGHTGRAY.a);
  rlBegin(RL_QUADS);

  // Front (+Z)
  if (faces.Front) {
    rlVertex3f(x0, y0, z1);
    rlVertex3f(x1, y0, z1);
    rlVertex3f(x1, y1, z1);
    rlVertex3f(x0, y1, z1);
  }

  // Back (-Z)
  if (faces.Back) {
    rlVertex3f(x1, y0, z0);
    rlVertex3f(x0, y0, z0);
    rlVertex3f(x0, y1, z0);
    rlVertex3f(x1, y1, z0);
  }

  // Right (+X)
  if (faces.Right) {
    rlVertex3f(x1, y0, z1);
    rlVertex3f(x1, y0, z0);
    rlVertex3f(x1, y1, z0);
    rlVertex3f(x1, y1, z1);
  }

  // Left (-X)
  if (faces.Left) {
    rlVertex3f(x0, y0, z0);
    rlVertex3f(x0, y0, z1);
    rlVertex3f(x0, y1, z1);
    rlVertex3f(x0, y1, z0);
  }

  // Top (+Y)
  if (faces.Top) {
    rlVertex3f(x0, y1, z1);
    rlVertex3f(x1, y1, z1);
    rlVertex3f(x1, y1, z0);
    rlVertex3f(x0, y1, z0);
  }

  // Bottom (-Y)
  if (faces.Bottom) {
    rlVertex3f(x0, y0, z0);
    rlVertex3f(x1, y0, z0);
    rlVertex3f(x1, y0, z1);
    rlVertex3f(x0, y0, z1);
  }

  rlEnd();
};

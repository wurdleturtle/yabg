#include "render.h"
#include "raylib.h"
#include "rlgl.h"

void DrawWorld(const World &world, const Texture &tex)
{
  world.ForEachBlock([&tex](const Block &pos, const BlockData &data)
                     {
    DrawCubeFaces(data.blockFaces, pos.toVector3(), tex);
    DrawCubeWiresV(pos.toVector3(), {1.0f, 1.0f, 1.0f}, BLACK); });
}

void DrawSelection(const Block &selectionPos)
{
  DrawCubeWiresV(selectionPos.toVector3(), {1.01f, 1.01f, 1.01f}, RED);
}

void DrawHud(std::size_t blockCount)
{
  DrawFPS(10, 10);

  DrawText(TextFormat("Blocks: %i", static_cast<int>(blockCount)), 10, 40, 20,
           RED);
}

void DrawCubeFaces(const Faces &faces, const Vector3 pos, const Texture &tex)
{
  const float h = 1 * 0.5f;

  const float x0 = pos.x - h;
  const float x1 = pos.x + h;
  const float y0 = pos.y - h;
  const float y1 = pos.y + h;
  const float z0 = pos.z - h;
  const float z1 = pos.z + h;

  rlColor4ub(LIGHTGRAY.r, LIGHTGRAY.g, LIGHTGRAY.b, LIGHTGRAY.a);
  rlSetTexture(tex.id);
  rlBegin(RL_QUADS);

  // Front (+Z)
  if (faces.Front)
  {
    rlTexCoord2f(0, 1);
    rlVertex3f(x0, y0, z1);
    rlTexCoord2f(1, 1);
    rlVertex3f(x1, y0, z1);
    rlTexCoord2f(1, 0);
    rlVertex3f(x1, y1, z1);
    rlTexCoord2f(0, 0);
    rlVertex3f(x0, y1, z1);
  }

  // Back (-Z)
  if (faces.Back)
  {
    rlTexCoord2f(0, 1);
    rlVertex3f(x1, y0, z0);
    rlTexCoord2f(1, 1);
    rlVertex3f(x0, y0, z0);
    rlTexCoord2f(1, 0);
    rlVertex3f(x0, y1, z0);
    rlTexCoord2f(0, 0);
    rlVertex3f(x1, y1, z0);
  }

  // Right (+X)
  if (faces.Right)
  {
    rlTexCoord2f(0, 1);
    rlVertex3f(x1, y0, z1);
    rlTexCoord2f(1, 1);
    rlVertex3f(x1, y0, z0);
    rlTexCoord2f(1, 0);
    rlVertex3f(x1, y1, z0);
    rlTexCoord2f(0, 0);
    rlVertex3f(x1, y1, z1);
  }

  // Left (-X)
  if (faces.Left)
  {
    rlTexCoord2f(0, 1);
    rlVertex3f(x0, y0, z0);
    rlTexCoord2f(1, 1);
    rlVertex3f(x0, y0, z1);
    rlTexCoord2f(1, 0);
    rlVertex3f(x0, y1, z1);
    rlTexCoord2f(0, 0);
    rlVertex3f(x0, y1, z0);
  }

  // Top (+Y)
  if (faces.Top)
  {
    rlTexCoord2f(0, 1);
    rlVertex3f(x0, y1, z1);
    rlTexCoord2f(1, 1);
    rlVertex3f(x1, y1, z1);
    rlTexCoord2f(1, 0);
    rlVertex3f(x1, y1, z0);
    rlTexCoord2f(0, 0);
    rlVertex3f(x0, y1, z0);
  }

  // Bottom (-Y)
  if (faces.Bottom)
  {
    rlTexCoord2f(0, 1);
    rlVertex3f(x0, y0, z0);
    rlTexCoord2f(1, 1);
    rlVertex3f(x1, y0, z0);
    rlTexCoord2f(1, 0);
    rlVertex3f(x1, y0, z1);
    rlTexCoord2f(0, 0);
    rlVertex3f(x0, y0, z1);
  }

  rlEnd();
};

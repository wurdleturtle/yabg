#include "render.h"
#include "raylib.h"
#include "rlgl.h"

void DrawWorld(const World &world, const BlockTextureSet &textures)
{
  world.ForEachBlock([&textures](const Block &pos, const BlockData &data)
                     {
      const Texture &tex = textures.at(ToIndex(data.type));
      DrawCubeFaces(data.blockFaces, pos.toVector3(), tex); });
}

void DrawSelection(const Block &selectionPos)
{
  DrawCubeWiresV(selectionPos.toVector3(), {1.01f, 1.01f, 1.01f}, RED);
}

void DrawHud(std::size_t blockCount, BlockType selectiontype, const BlockTextureSet &textures)
{
  DrawFPS(10, 10);

  DrawText(TextFormat("Blocks: %i", static_cast<int>(blockCount)), 10, 40, 20,
           RED);

  DrawTexture(textures.at(ToIndex(selectiontype)), 10, 70, WHITE);
}

void DrawCubeFaces(const Faces &faces, const Vector3 pos, const Texture &texture)
{
  const float h = 1 * 0.5f;

  const float x0 = pos.x - h;
  const float x1 = pos.x + h;
  const float y0 = pos.y - h;
  const float y1 = pos.y + h;
  const float z0 = pos.z - h;
  const float z1 = pos.z + h;

  rlColor4ub(LIGHTGRAY.r, LIGHTGRAY.g, LIGHTGRAY.b, LIGHTGRAY.a);
  rlSetTexture(texture.id);
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

BlockTextureSet LoadBlockTextures()
{
  BlockTextureSet textures{};
  for (std::size_t i = 0; i < BlockTypeCount; ++i)
  {
    textures[i] = LoadTexture(BlockDefinitions[i].texturePath);
  }
  return textures;
}
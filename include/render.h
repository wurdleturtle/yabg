#pragma once

#include <cstddef>

#include "block.h"
#include "world.h"

using BlockTextureSet = std::array<Texture2D, BlockTypeCount>;

void DrawWorld(const World &world, const BlockTextureSet &textures);

void DrawSelection(const Block &selectionPos);

void DrawHud(std::size_t blockCount, BlockType selectionType, const BlockTextureSet &textures);

void DrawCubeFaces(const Faces &faces, const Vector3 pos, const Texture &tex);

BlockTextureSet LoadBlockTextures();
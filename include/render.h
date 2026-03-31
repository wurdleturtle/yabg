#pragma once

#include <cstddef>

#include "block.h"
#include "world.h"

void DrawWorld(const World &world, const Texture &tex);

void DrawSelection(const Block &selectionPos);

void DrawHud(std::size_t blockCount);

void DrawCubeFaces(const Faces &faces, const Vector3 pos, const Texture &tex);

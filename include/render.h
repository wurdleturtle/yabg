#pragma once

#include <cstddef>

#include "block.h"
#include "world.h"

void DrawWorld(const World &world);

void DrawSelection(const Block &selectionPos);

void DrawHud(std::size_t blockCount);

void DrawCubeFaces(Faces faces, Vector3 pos);

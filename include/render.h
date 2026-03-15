#pragma once

#include <cstddef>

#include "block.h"
#include "world.h"

void DrawWorld(const World &world);

void DrawSelection(const Block &selectionPos);

void DrawHud(const Block &selectionPos, std::size_t blockCount);

#pragma once
#include <array>
#include <cstddef>

// Single list: add/remove blocks here only.
#define BLOCK_LIST(X)              \
  X(Bedrock, "assets/bedrock.png") \
  X(Dirt, "assets/dirt.png")       \
  X(Grass, "assets/grass.png")     \
  X(Stone, "assets/stone.png")     \
  X(Sand, "assets/sand.png")       \
  X(Plank, "assets/plank.png")     \
  X(Log, "assets/log.png")

enum class BlockType
{
#define X(name, path) name,
  BLOCK_LIST(X)
#undef X
      Count
};

constexpr std::size_t BlockTypeCount = static_cast<std::size_t>(BlockType::Count);

constexpr std::size_t ToIndex(BlockType t)
{
  return static_cast<std::size_t>(t);
}

struct BlockDefinition
{
  const char *texturePath;
};

constexpr std::array<BlockDefinition, BlockTypeCount> BlockDefinitions = {{
#define X(name, path) BlockDefinition{path},
    BLOCK_LIST(X)
#undef X
}};
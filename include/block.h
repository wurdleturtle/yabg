#pragma once
#include "cstddef"
#include "raylib.h"
#include <functional>

struct Block {
  int x;
  int y;
  int z;

  Vector3 toVector3() const { return {(float)x, (float)y, (float)z}; }

  // checks only for position
  bool operator==(const Block &other) const {
    return x == other.x && y == other.y && z == other.z;
  }
};

struct BlockHash {

  // TODO: learn what the FUCK this means

  std::size_t operator()(const Block &b) const noexcept {
    std::size_t hx = std::hash<int>{}(b.x);
    std::size_t hy = std::hash<int>{}(b.y);
    std::size_t hz = std::hash<int>{}(b.z);
    std::size_t seed = hx;
    seed ^= hy + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hz + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};

enum class BlockType : unsigned short { Dirt = 0 };

struct BlockData {
  BlockType type = BlockType::Dirt;
};

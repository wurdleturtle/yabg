#pragma once

#include "block.h"
#include <unordered_map>

class World {
public:
  // Returns true if block successfully placed, false if not
  bool AddBlock(const Block &block, BlockType type = BlockType::Dirt);
  bool RemoveBlock(const Block &pos);
  bool HasBlock(const Block &pos) const;

  void UpdateFaces();

  RaycastHit Raycast(const Ray &ray, float maxDistance) const;

  template <typename F> void ForEachBlock(F &&visitor) const {
    for (const auto &[pos, data] : blocks_) {
      std::forward<F>(visitor)(pos, data);
    }
  }

  const std::unordered_map<Block, BlockData, BlockHash> &GetBlocks() const;

  std::size_t GetBlockCount() const;

  void GenerateFlat(int halfSize, int y, BlockType type);

private:
  std::unordered_map<Block, BlockData, BlockHash> blocks_;
};

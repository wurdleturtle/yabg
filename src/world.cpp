#include "world.h"
#include "block.h"
#include <cmath>
#include <limits>
#include <unordered_map>

bool World::AddBlock(const Block &pos, BlockType type) {
  auto [it, inserted] = blocks_.emplace(pos, BlockData{type});
  return inserted;
}

bool World::RemoveBlock(const Block &pos) { return blocks_.erase(pos) > 0; }

bool World::HasBlock(const Block &pos) const {
  return blocks_.find(pos) != blocks_.end();
}

const std::unordered_map<Block, BlockData, BlockHash> &
World::GetBlocks() const {
  return blocks_;
}

std::size_t World::GetBlockCount() const { return blocks_.size(); }

void World::GenerateFlat(int halfSize, int y, BlockType type) {
  if (halfSize < 0) {
    return;
  }

  for (int x = -halfSize; x <= halfSize; ++x) {
    for (int z = -halfSize; z <= halfSize; ++z) {
      AddBlock(Block{x, y, z}, type);
    }
  }
}

void World::UpdateFaces() {
  for (auto &[pos, data] : blocks_) {
    data.blockFaces.Front = !HasBlock(Block{pos.x, pos.y, pos.z + 1});
    data.blockFaces.Back = !HasBlock(Block{pos.x, pos.y, pos.z - 1});
    data.blockFaces.Right = !HasBlock(Block{pos.x + 1, pos.y, pos.z});
    data.blockFaces.Left = !HasBlock(Block{pos.x - 1, pos.y, pos.z});
    data.blockFaces.Top = !HasBlock(Block{pos.x, pos.y + 1, pos.z});
    data.blockFaces.Bottom = !HasBlock(Block{pos.x, pos.y - 1, pos.z});
  }
};

#include "world.h"
#include "block.h"
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

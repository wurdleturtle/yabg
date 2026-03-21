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

RaycastHit World::Raycast(const Ray &ray, float maxDistance) const {
  RaycastHit out{};

  if (!std::isfinite(ray.position.x) || !std::isfinite(ray.position.y) ||
      !std::isfinite(ray.position.z) || !std::isfinite(ray.direction.x) ||
      !std::isfinite(ray.direction.y) || !std::isfinite(ray.direction.z))
    return out;

  constexpr float EPS = 1e-4f;

  Vector3 dir = ray.direction;
  const float lenSq = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
  if (lenSq <= 0.0f || maxDistance <= 0.0f)
    return out;
  const float invLen = 1.0f / sqrtf(lenSq);
  dir.x *= invLen;
  dir.y *= invLen;
  dir.z *= invLen;

  const Vector3 &o = ray.position;

  // Step signs
  const int stepX = dir.x >= 0.0f ? 1 : -1;
  const int stepY = dir.y >= 0.0f ? 1 : -1;
  const int stepZ = dir.z >= 0.0f ? 1 : -1;

  const float INF = std::numeric_limits<float>::infinity();

  // How far along the ray to cross one voxel in each axis
  const float tDX = fabsf(dir.x) > EPS ? 1.0f / fabsf(dir.x) : INF;
  const float tDY = fabsf(dir.y) > EPS ? 1.0f / fabsf(dir.y) : INF;
  const float tDZ = fabsf(dir.z) > EPS ? 1.0f / fabsf(dir.z) : INF;

  // Current voxel
  int cx = (int)floorf(o.x);
  int cy = (int)floorf(o.y);
  int cz = (int)floorf(o.z);

  // t at which we first cross into the next voxel on each axis
  float tMaxX = (stepX > 0 ? (cx + 1.0f - o.x) : (o.x - cx)) * tDX;
  float tMaxY = (stepY > 0 ? (cy + 1.0f - o.y) : (o.y - cy)) * tDY;
  float tMaxZ = (stepZ > 0 ? (cz + 1.0f - o.z) : (o.z - cz)) * tDZ;

  int axis = -1; // which axis we last crossed

  // Check the starting voxel before any stepping
  if (HasBlock({cx, cy, cz})) {
    out.hit = true;
    out.blockPos = {cx, cy, cz};
    out.distance = 0.0f;
    out.normal = {0, 0, 0};
    return out;
  }

  while (true) {
    float t;
    if (tMaxX <= tMaxY && tMaxX <= tMaxZ) {
      t = tMaxX;
      if (t > maxDistance)
        break;
      cx += stepX;
      axis = 0;
      tMaxX += tDX;
    } else if (tMaxY <= tMaxZ) {
      t = tMaxY;
      if (t > maxDistance)
        break;
      cy += stepY;
      axis = 1;
      tMaxY += tDY;
    } else {
      t = tMaxZ;
      if (t > maxDistance)
        break;
      cz += stepZ;
      axis = 2;
      tMaxZ += tDZ;
    }

    if (HasBlock({cx, cy, cz})) {
      out.hit = true;
      out.blockPos = {cx, cy, cz};
      out.distance = t;
      out.normal = {0, 0, 0};
      if (axis == 0)
        out.normal.x = (float)-stepX;
      else if (axis == 1)
        out.normal.y = (float)-stepY;
      else if (axis == 2)
        out.normal.z = (float)-stepZ;
      return out;
    }
  }

  return out;
}

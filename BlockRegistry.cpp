#pragma once
#include "worldManager.cpp"
#include "BlockRenderer.cpp"
#include <map>
#include <string>

struct BlockDef {
    std::string name;
    cubeObject model;
};

std::map<BlockType, BlockDef> BLOCK_REGISTRY;

void RegisterBlock(BlockType type, std::string name, const char* sideTex, const char* topTex, bool transparent = false) {
    BLOCK_REGISTRY[type] = { name, InitializeLogObject(sideTex, topTex, transparent, type) };
}

void InitializeBlocks() {
    RegisterBlock(BLOCK_OAK_LOG, "Oak Log", "textures/oak.png", "textures/oakend.png");
    RegisterBlock(BLOCK_BONE, "Bone Block", "textures/bone.png", "textures/boneend.png");
    RegisterBlock(BLOCK_GRATE, "Grate", "textures/grate.png", "textures/grate.png");
    RegisterBlock(BLOCK_BEDROCK, "Bedrock", "textures/bedrock.png", "textures/bedrock.png");
    RegisterBlock(BLOCK_STONE, "Stone", "textures/stone.png", "textures/stone.png");
    RegisterBlock(BLOCK_DIRT, "Dirt", "textures/dirt.png", "textures/dirt.png");
    RegisterBlock(BLOCK_GRASS, "Grass", "textures/grass.png", "textures/grasstop.png");
    RegisterBlock(BLOCK_OAK_LEAVES, "Oak Leaves", "textures/oakleaves.png", "textures/oakleaves.png");
}

BlockDef* GetBlockDef(BlockType type) {
    if (BLOCK_REGISTRY.find(type) != BLOCK_REGISTRY.end()) {
        return &BLOCK_REGISTRY[type];
    }
    return nullptr;
}

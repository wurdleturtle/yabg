#pragma once

#include "raylib.h"
#include <vector>
#include <cmath> // Required for floor()
#include <stdio.h>

typedef enum {
    BLOCK_AIR = 0,
    BLOCK_OAK_LOG,
    BLOCK_BONE,
    BLOCK_GRATE,
    BLOCK_STONE,
    BLOCK_BEDROCK,
    BLOCK_DIRT,
    BLOCK_GRASS,
    BLOCK_OAK_LEAVES,
    BLOCK_COUNT
} BlockType;


// Define constants for array sizes (must be compile-time constants)
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 36
#define CHUNK_LENGTH 16

struct Chunk {
    BlockType blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH];
    Vector3 position; // The world position of the chunk's corner (e.g., 0,0,0)
    bool isLoaded;
};

struct World {
    std::vector<Chunk> chunks;
};

World gameWorld;

void InitChunk(Chunk* chunk, Vector3 position) {
    chunk->position = position;
    chunk->isLoaded = true;
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_LENGTH; z++) {
                chunk->blocks[x][y][z] = BLOCK_AIR;
            }
        }
    }
}

BlockType GetBlockAt(Vector3 pos) {
    // 1. Calculate the origin of the chunk this block belongs to
    int chunkX = (int)floor(pos.x / CHUNK_WIDTH) * CHUNK_WIDTH;
    int chunkZ = (int)floor(pos.z / CHUNK_LENGTH) * CHUNK_LENGTH;

    // 2. Calculate local coordinates within that chunk
    int localX = (int)pos.x - chunkX;
    int localY = (int)pos.y;
    int localZ = (int)pos.z - chunkZ;

    // 3. Check bounds (Height is limited to chunk height for now)
    if (localY < 0 || localY >= CHUNK_HEIGHT) return BLOCK_AIR;

    // 4. Find the chunk in the list
    for (const auto& chunk : gameWorld.chunks) {
        if ((int)chunk.position.x == chunkX && (int)chunk.position.z == chunkZ) {
            // Ensure local coords are safe before accessing
            if (localX >= 0 && localX < CHUNK_WIDTH && localZ >= 0 && localZ < CHUNK_LENGTH) {
                return chunk.blocks[localX][localY][localZ];
            }
        }
    }

    return BLOCK_AIR;
}

void SetBlockAt(Vector3 pos, BlockType type) {
    int chunkX = (int)floor(pos.x / CHUNK_WIDTH) * CHUNK_WIDTH;
    int chunkZ = (int)floor(pos.z / CHUNK_LENGTH) * CHUNK_LENGTH;

    int localX = (int)pos.x - chunkX;
    int localY = (int)pos.y;
    int localZ = (int)pos.z - chunkZ;

    if (localY < 0 || localY >= CHUNK_HEIGHT) return;

    for (auto& chunk : gameWorld.chunks) {
        if ((int)chunk.position.x == chunkX && (int)chunk.position.z == chunkZ) {
            if (localX >= 0 && localX < CHUNK_WIDTH && localZ >= 0 && localZ < CHUNK_LENGTH) {
                chunk.blocks[localX][localY][localZ] = type;
                return;
            }
        }
    }
}

#include "PerlinNoise.hpp"

void InitWorld(int initialSize) {
    PerlinNoise perlin;
    for (int x = 0; x < initialSize; x++) {
        for (int z = 0; z < initialSize; z++) {
            Chunk newChunk;
            InitChunk(&newChunk, Vector3{ (float)x * CHUNK_WIDTH, 0, (float)z * CHUNK_LENGTH });
            
            for(int i = 0; i < CHUNK_WIDTH; i++) {
                for(int k = 0; k < CHUNK_LENGTH; k++) {
                    float worldX = (x * CHUNK_WIDTH) + i;
                    float worldZ = (z * CHUNK_LENGTH) + k;
                    
                    // Generate height using Perlin noise
                    // Scale coordinates to make the terrain smoother
                    float n = perlin.noise(worldX * 0.1f, 0.0f, worldZ * 0.1f);
                    
                    // Map noise (-1 to 1) to height (1 to CHUNK_HEIGHT)
                    int height = (int)((n + 1.0f) * 0.5f * ((CHUNK_HEIGHT / 2) - 4)) + 2;
                    
                    if (height > CHUNK_HEIGHT) height = CHUNK_HEIGHT;
                    if (height < 1) height = 1;

                    for(int j = 0; j < height; j++) {
                        if (j == 0) {
                            newChunk.blocks[i][j][k] = BLOCK_BEDROCK;
                        } else if (j == height - 1) {
                            newChunk.blocks[i][j][k] = BLOCK_GRASS;
                        } else if (j == height - 2) {
                            newChunk.blocks[i][j][k] = BLOCK_DIRT;
                        } else {
                            newChunk.blocks[i][j][k] = BLOCK_STONE;
                        }
                    }
                }
            }

            gameWorld.chunks.push_back(newChunk);
        }
    }
}

void SaveWorld(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        TraceLog(LOG_ERROR, "Failed to open world file for saving.");
        return;
    }

    int chunkCount = gameWorld.chunks.size();
    fwrite(&chunkCount, sizeof(int), 1, file);

    for (const auto& chunk : gameWorld.chunks) {
        fwrite(&chunk.position, sizeof(Vector3),1, file);
        fwrite(chunk.blocks, sizeof(BlockType) * CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH, 1, file);
    }

    fclose(file);
    TraceLog(LOG_INFO, "World saved successfully.");
}

void LoadWorld(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        TraceLog(LOG_ERROR, "Failed to open world file for loading.");
        return;
    }

    gameWorld.chunks.clear();

    int chunkCount = 0;
    fread(&chunkCount, sizeof(int), 1, file);

    for (int i = 0; i < chunkCount; i++) {
        Chunk newChunk;
        newChunk.isLoaded = true;

        fread(&newChunk.position, sizeof(Vector3), 1, file);
        fread(newChunk.blocks, sizeof(BlockType) * CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH, 1, file);
        gameWorld.chunks.push_back(newChunk);
    }

    fclose(file);
    TraceLog(LOG_INFO, "World loaded successfully.");
}
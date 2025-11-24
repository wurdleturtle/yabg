#include "raylib.h"
#include <vector>
#include <cmath> // Required for floor()

typedef enum {
    BLOCK_AIR = 0,
    BLOCK_OAK_LOG,
    BLOCK_BONE,
    BLOCK_GRATE,
    BLOCK_BEDROCK
} BlockType;

// Define constants for array sizes (must be compile-time constants)
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
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

void InitWorld(int initialSize) {
    for (int x = 0; x < initialSize; x++) {
        for (int z = 0; z < initialSize; z++) {
            Chunk newChunk;
            InitChunk(&newChunk, Vector3{ (float)x * CHUNK_WIDTH, 0, (float)z * CHUNK_LENGTH });
            
            // Example: Fill the bottom layer of the chunk with GRATE blocks
            for(int i = 0; i < CHUNK_WIDTH; i++) {
                for(int k = 0; k < CHUNK_LENGTH; k++) {
                    newChunk.blocks[i][0][k] = BLOCK_BEDROCK;
                }
            }

            gameWorld.chunks.push_back(newChunk);
        }
    }
}
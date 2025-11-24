#pragma once

#include "raylib.h"
#include "rlgl.h"
#include "worldManager.cpp"
#include "wurdleapi.cpp"
#include <map>

extern BlockType GetBlockAt(Vector3 worldPos);

typedef struct cubeFace {
    Model faceModel;
    bool isVisible;
} cubeFace; 

typedef struct cubeObject {
    cubeFace Front;
    cubeFace Right;
    cubeFace Left;
    cubeFace Back;
    cubeFace Top;
    cubeFace Bottom;
    bool Transparent;
} cubeObject; 

struct TextureType {
    Texture side;
    Texture top;
};

std::map<BlockType, TextureType> TEXTURE_REGISTRY;

Texture GetBlockTexture(BlockType type) {
    return TEXTURE_REGISTRY[type].side;
};

void RegisterTexture(BlockType type, Texture texture, Texture toptexture) {
    TEXTURE_REGISTRY[type] = { texture, toptexture };
}

cubeObject InitializeLogObject(const char* sideTexture, const char* endTexture, bool transparent, BlockType type) {
    // Load Textures
    Texture minecraftTexture = LoadTexture(sideTexture);
    Texture minecraftTextureTop = LoadTexture(endTexture);

    RegisterTexture(type, minecraftTexture, minecraftTextureTop);

    // Create Models from Meshes
    Model cubeFront = LoadModelFromMesh(GenCubeMeshFront(1.0f, 1.0f, 1.0f));
    Model cubeRight = LoadModelFromMesh(GenCubeMeshRight(1.0f, 1.0f, 1.0f));
    Model cubeLeft = LoadModelFromMesh(GenCubeMeshLeft(1.0f, 1.0f, 1.0f));
    Model cubeBack = LoadModelFromMesh(GenCubeMeshBack(1.0f, 1.0f, 1.0f));
    Model cubeTop = LoadModelFromMesh(GenCubeMeshTop(1.0f, 1.0f, 1.0f));
    Model cubeBottom = LoadModelFromMesh(GenCubeMeshBottom(1.0f, 1.0f, 1.0f));

    // Apply Textures to Models
    cubeFront.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = minecraftTexture;
    cubeRight.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = minecraftTexture;
    cubeLeft.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = minecraftTexture;
    cubeBack.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = minecraftTexture;
    cubeTop.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = minecraftTextureTop;
    cubeBottom.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = minecraftTextureTop;

    // Create cubeObject from models and return

    cubeObject cube = {
        {cubeFront, true},
        {cubeRight, true},
        {cubeLeft, true},
        {cubeBack, true},
        {cubeTop, true},
        {cubeBottom, true},
        transparent
    };

    return cube;
}

bool IsOccluding(Vector3 pos) {
    BlockType type = GetBlockAt(pos);
    return (type != BLOCK_AIR);
}

int CalculateVertexAO(Vector3 side1, Vector3 side2, Vector3 corner) {
    bool s1 = IsOccluding(side1);
    bool s2 = IsOccluding(side2);
    bool c = IsOccluding(corner);

    if (s1 && s2) return 3; // Max shadow if both sides are blocked
    return (s1 ? 1 : 0) + (s2 ? 1 : 0) + (c ? 1 : 0);
}

float GetAOIntensity(int aoLevel) {
    switch (aoLevel) {
        case 0: return 1.0f;   // No occlusion
        case 1: return 0.8f;   // Slight occlusion
        case 2: return 0.6f;   // Moderate occlusion
        case 3: return 0.4f;   // Max occlusion
        default: return 1.0f;
    }
}

int GetAO(Vector3 pos, Vector3 normal, Vector3 dir1, Vector3 dir2) {
    Vector3 facePos = { pos.x + normal.x, pos.y + normal.y, pos.z + normal.z };
    Vector3 s1 = { facePos.x + dir1.x, facePos.y + dir1.y, facePos.z + dir1.z };
    Vector3 s2 = { facePos.x + dir2.x, facePos.y + dir2.y, facePos.z + dir2.z };
    Vector3 c = { facePos.x + dir1.x + dir2.x, facePos.y + dir1.y + dir2.y, facePos.z + dir1.z + dir2.z };
    return CalculateVertexAO(s1, s2, c);
}

void DrawFace(Texture texture, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3 normal, Vector3 pos) {
        float ao[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        
        if (normal.y > 0) {
            // Top face AO
            ao[0] = GetAOIntensity(GetAO(pos, normal, {-1, 0, 0}, {0, 0, 1})); // TLF
            ao[1] = GetAOIntensity(GetAO(pos, normal, {1, 0, 0}, {0, 0, 1}));  // TRF
            ao[2] = GetAOIntensity(GetAO(pos, normal, {1, 0, 0}, {0, 0, -1})); // TRB
            ao[3] = GetAOIntensity(GetAO(pos, normal, {-1, 0, 0}, {0, 0, -1}));// TLB
        } else if (normal.y < 0) {
            // Bottom face AO
            ao[0] = GetAOIntensity(GetAO(pos, normal, {-1, 0, 0}, {0, 0, 1})); // FL
            ao[1] = GetAOIntensity(GetAO(pos, normal, {1, 0, 0}, {0, 0, 1}));  // FR
            ao[2] = GetAOIntensity(GetAO(pos, normal, {1, 0, 0}, {0, 0, -1})); // BR
            ao[3] = GetAOIntensity(GetAO(pos, normal, {-1, 0, 0}, {0, 0, -1}));// BL
        } else if (normal.z > 0) {
            // Front face AO
            ao[0] = GetAOIntensity(GetAO(pos, normal, {-1, 0, 0}, {0, -1, 0})); // BL
            ao[1] = GetAOIntensity(GetAO(pos, normal, {1, 0, 0}, {0, -1, 0}));  // BR
            ao[2] = GetAOIntensity(GetAO(pos, normal, {1, 0, 0}, {0, 1, 0}));   // TR
            ao[3] = GetAOIntensity(GetAO(pos, normal, {-1, 0, 0}, {0, 1, 0}));  // TL
        } else if (normal.z < 0) {
            // Back face AO
            ao[0] = GetAOIntensity(GetAO(pos, normal, {1, 0, 0}, {0, -1, 0}));  // BR
            ao[1] = GetAOIntensity(GetAO(pos, normal, {-1, 0, 0}, {0, -1, 0})); // BL
            ao[2] = GetAOIntensity(GetAO(pos, normal, {-1, 0, 0}, {0, 1, 0}));  // TL
            ao[3] = GetAOIntensity(GetAO(pos, normal, {1, 0, 0}, {0, 1, 0}));   // TR
        } else if (normal.x > 0) {
            // Right face AO
            ao[0] = GetAOIntensity(GetAO(pos, normal, {0, 0, 1}, {0, -1, 0}));  // BF
            ao[1] = GetAOIntensity(GetAO(pos, normal, {0, 0, -1}, {0, -1, 0})); // BB
            ao[2] = GetAOIntensity(GetAO(pos, normal, {0, 0, -1}, {0, 1, 0}));  // TB
            ao[3] = GetAOIntensity(GetAO(pos, normal, {0, 0, 1}, {0, 1, 0}));   // TF
        } else if (normal.x < 0) {
            // Left face AO
            ao[0] = GetAOIntensity(GetAO(pos, normal, {0, 0, -1}, {0, -1, 0})); // BB
            ao[1] = GetAOIntensity(GetAO(pos, normal, {0, 0, 1}, {0, -1, 0}));  // BF
            ao[2] = GetAOIntensity(GetAO(pos, normal, {0, 0, 1}, {0, 1, 0}));   // TF
            ao[3] = GetAOIntensity(GetAO(pos, normal, {0, 0, -1}, {0, 1, 0}));  // TB
        }

        bool isSide = (normal.y == 0);

        rlSetTexture(texture.id);
        rlBegin(RL_QUADS);
            rlNormal3f(normal.x, normal.y, normal.z);

            rlColor4ub(255 * ao[0], 255 * ao[0], 255 * ao[0], 255);
            rlTexCoord2f(0.0f, isSide ? 1.0f : 0.0f);
            rlVertex3f(p1.x, p1.y, p1.z);

            rlColor4ub(255 * ao[1], 255 * ao[1], 255 * ao[1], 255);
            rlTexCoord2f(1.0f, isSide ? 1.0f : 0.0f);
            rlVertex3f(p2.x, p2.y, p2.z);

            rlColor4ub(255 * ao[2], 255 * ao[2], 255 * ao[2], 255);
            rlTexCoord2f(1.0f, isSide ? 0.0f : 1.0f);
            rlVertex3f(p3.x, p3.y, p3.z);

            rlColor4ub(255 * ao[3], 255 * ao[3], 255 * ao[3], 255);
            rlTexCoord2f(0.0f, isSide ? 0.0f : 1.0f);
            rlVertex3f(p4.x, p4.y, p4.z);
        rlEnd();
        rlSetTexture(0); // Unbind texture
    }



void renderCube(Vector3 cubePos, const cubeObject& cube) {
    float x = cubePos.x;
    float y = cubePos.y;
    float z = cubePos.z;
    float w = 0.5f; // Half width

    if (cube.Top.isVisible) {
        DrawFace(
            cube.Top.faceModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture,
            {x - w, y + w, z + w}, // TLF
            {x + w, y + w, z + w}, // TRF
            {x + w, y + w, z - w}, // TRB
            {x - w, y + w, z - w}, // TLB
            {0.0f, 1.0f, 0.0f},
            cubePos
        );
    }

    if (cube.Bottom.isVisible) {
        DrawFace(
            cube.Bottom.faceModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture,
            {x - w, y - w, z + w},
            {x + w, y - w, z + w},
            {x + w, y - w, z - w},
            {x - w, y - w, z - w},
            {0.0f, -1.0f, 0.0f},
            cubePos
        );
    }

    if (cube.Front.isVisible) {
        DrawFace(
            cube.Front.faceModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture,
            {x - w, y - w, z + w},
            {x + w, y - w, z + w},
            {x + w, y + w, z + w},
            {x - w, y + w, z + w},
            {0.0f, 0.0f, 1.0f},
            cubePos
        );
    }

    if (cube.Back.isVisible) {
        DrawFace(
            cube.Back.faceModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture,
            {x + w, y - w, z - w},
            {x - w, y - w, z - w},
            {x - w, y + w, z - w},
            {x + w, y + w, z - w},
            {0.0f, 0.0f, -1.0f},
            cubePos
        );
    }

    if (cube.Right.isVisible) {
        DrawFace(
            cube.Right.faceModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture,
            {x + w, y - w, z + w},
            {x + w, y - w, z - w},
            {x + w, y + w, z - w},
            {x + w, y + w, z + w},
            {1.0f, 0.0f, 0.0f},
            cubePos
        );
    }
    if (cube.Left.isVisible) {
        DrawFace(
            cube.Left.faceModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture,
            {x - w, y - w, z - w},
            {x - w, y - w, z + w},
            {x - w, y + w, z + w},
            {x - w, y + w, z - w},
            {-1.0f, 0.0f, 0.0f},
            cubePos
        );
    }
}
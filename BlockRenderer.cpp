#include "raylib.h"
#include "wurdleapi.cpp"

typedef struct cubeObject {
    Model Front;
    Model Right;
    Model Left;
    Model Back;
    Model Top;
    Model Bottom;
} cubeObject;

cubeObject InitializeLogObject(char* sideTexture, char* endTexture) {
    // Load Textures
    Texture minecraftTexture = LoadTexture(sideTexture);
    Texture minecraftTextureTop = LoadTexture(endTexture);

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
        cubeFront,
        cubeRight,
        cubeLeft,
        cubeBack,
        cubeTop,
        cubeBottom
    };

    return cube;
}

void renderCube(Vector3 cubePos, const cubeObject& cube) {
    DrawModel(cube.Front, cubePos, 1, WHITE);
    DrawModel(cube.Right, cubePos, 1, WHITE);
    DrawModel(cube.Left, cubePos, 1, WHITE);
    DrawModel(cube.Back, cubePos, 1, WHITE);
    DrawModel(cube.Top, cubePos, 1, WHITE);
    DrawModel(cube.Bottom, cubePos, 1, WHITE);
};
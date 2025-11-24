#include "raylib.h"
#include "raymath.h"
#include <string>
#include "BlockRenderer.cpp"
#include "worldManager.cpp"
#include "BlockRegistry.cpp"

int main(void)
{
    // Initialization
    const int screenWidth = 1200;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");
    DisableCursor();

    float basemovespeed = 2.0f;
    float movespeed = basemovespeed;

    InitializeBlocks();

    InitWorld(3); // Init A world, 3x3 chunks

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = Vector3{ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 30.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    double dt = 0;

    BlockType selectedBlock = BLOCK_OAK_LOG;

    Vector3 targetBlock = {0.0f, 0.0f, 0.0f};

    int cubeAmount = 0;

    SetTargetFPS(60);                   // Set the game to run at 60 frames-per-second

    

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        dt = GetFrameTime();

        camera.target = targetBlock;
        if (IsKeyDown(KEY_SPACE)){
            UpdateCamera(&camera, CAMERA_ORBITAL);
            UpdateCamera(&camera, CAMERA_ORBITAL);
        } else{
            camera.position = Vector3Add(targetBlock, {10.0f, 10.0f, 10.0f});
        }
        movespeed = basemovespeed * dt;

        // Input

        if (IsKeyPressed(KEY_D)) {
            targetBlock.x++;
        }
        if (IsKeyPressed(KEY_A)) {
            targetBlock.x--;
        }
        if (IsKeyPressed(KEY_W)) {
            targetBlock.z--;
        }
        if (IsKeyPressed(KEY_S)) {
            targetBlock.z++;
        }

        if (IsKeyPressed(KEY_Q)) {
            targetBlock.y--;
        }
        if (IsKeyPressed(KEY_E)) {
            targetBlock.y++;
        }

        // Placing Blocks

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            // Example: Place a block at the camera's target position (rounded)
            Vector3 placePos = {
                roundf(camera.target.x),
                roundf(camera.target.y),
                roundf(camera.target.z)
            };
            SetBlockAt(placePos, selectedBlock);
        }

        if (IsKeyPressed(KEY_UP)) {
             if (selectedBlock < BLOCK_COUNT - 1) {
                selectedBlock = static_cast<BlockType>(static_cast<int>(selectedBlock) + 1);
             } else {
                selectedBlock = BLOCK_AIR;
             }
        }

        // Draw
        BeginDrawing();

            ClearBackground(SKYBLUE);  

            BeginMode3D(camera);

            cubeAmount = 0;

                for (const auto& chunk : gameWorld.chunks) {
                    if (!chunk.isLoaded) continue;

                    // Code inside this runs for every block in the chunk
                    for (int x = 0; x < CHUNK_WIDTH; x++){
                        for (int y = 0; y < CHUNK_HEIGHT; y++) {
                            for (int z = 0; z < CHUNK_LENGTH; z++) {

                                // START
                                BlockType type = chunk.blocks[x][y][z];
                                
                                if (type != BLOCK_AIR) {

                                    cubeAmount++;
                                    Vector3 blockPos = {
                                        chunk.position.x + x,
                                        chunk.position.y + y,
                                        chunk.position.z + z
                                    };
                                    bool showFront, showBack, showRight, showLeft, showTop, showBottom;
                                    showFront = GetBlockAt(Vector3{blockPos.x, blockPos.y, blockPos.z + 1}) == BLOCK_AIR;
                                    showBack  = GetBlockAt(Vector3{blockPos.x, blockPos.y, blockPos.z - 1}) == BLOCK_AIR;
                                    showRight = GetBlockAt(Vector3{blockPos.x + 1, blockPos.y, blockPos.z}) == BLOCK_AIR;
                                    showLeft  = GetBlockAt(Vector3{blockPos.x - 1, blockPos.y, blockPos.z}) == BLOCK_AIR;
                                    showTop   = GetBlockAt(Vector3{blockPos.x, blockPos.y + 1, blockPos.z}) == BLOCK_AIR;
                                    showBottom= GetBlockAt(Vector3{blockPos.x, blockPos.y - 1, blockPos.z}) == BLOCK_AIR;

                                    if (type == BLOCK_OAK_LEAVES) {
                                        // Special case: Leaves are transparent, so always show all faces
                                        showFront = true;
                                        showBack = true;
                                        showRight = true;
                                        showLeft = true;
                                        showTop = true;
                                        showBottom = true;
                                    }

                                    if (showFront || showBack || showRight || showLeft || showTop || showBottom) {
                                        BlockDef* def = GetBlockDef(type);
                                        if (def) {
                                            cubeObject tempModel = def->model;
                                            tempModel.Front.isVisible = showFront;
                                            tempModel.Back.isVisible = showBack;
                                            tempModel.Right.isVisible = showRight;
                                            tempModel.Left.isVisible = showLeft;
                                            tempModel.Top.isVisible = showTop;
                                            tempModel.Bottom.isVisible = showBottom;

                                            renderCube(blockPos, tempModel);
                                        }
                                    }
                                }
                                // END
                                
                            }
                        }
                }
                }

                                // Draw Selection Wires
                rlSetLineWidth(4.0f);
                DrawCubeWires(targetBlock, 1.0f, 1.0f, 1.0f, DARKBLUE);

            EndMode3D();
            
            std::string blockName;
            if (selectedBlock == BLOCK_AIR) {
                blockName = "BLOCK_AIR";
            } else {
                BlockDef* def = GetBlockDef(selectedBlock);
                if (def) {
                    blockName = def->name;
                } else {
                    blockName = "UNKNOWN";
                }
            }

            DrawText(TextFormat("Current Selected BlockType: %s", blockName.c_str()), 10, 20, 20, DARKBLUE);
            DrawText(TextFormat("Non-Air Block Count: %0.0f", (float) cubeAmount), 10, 40, 20, DARKBLUE);
            DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    EnableCursor();
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

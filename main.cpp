#include "raylib.h"
#include "raymath.h"
#include "BlockRenderer.cpp"
#include "worldManager.cpp "

int main(void)
{
    // Initialization
    const int screenWidth = 1200;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");
    DisableCursor();

    float basemovespeed = 2.0f;
    float movespeed = basemovespeed;

    cubeObject oakObject = InitializeLogObject("textures/oak.png", "textures/oakend.png");
    cubeObject boneObject = InitializeLogObject("textures/bone.png", "textures/boneend.png");
    cubeObject grateObject = InitializeLogObject("textures/grate.png", "textures/grate.png");
    cubeObject bedrockObject = InitializeLogObject("textures/bedrock.png", "textures/bedrock.png");

    InitWorld(2); // Init A world, 2x2 chunks

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = Vector3{ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 30.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    double dt = 0;

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
            SetBlockAt(placePos, BLOCK_OAK_LOG);
        }

        // Draw
        BeginDrawing();

            ClearBackground(SKYBLUE);  

            BeginMode3D(camera);

                for (const auto& chunk : gameWorld.chunks) {
                    cubeAmount = 0;
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

                                    switch (type) {
                                        case BLOCK_OAK_LOG:
                                            renderCube(blockPos, oakObject);
                                            break;
                                        case BLOCK_BONE:
                                            renderCube(blockPos, boneObject);
                                            break;
                                        case BLOCK_GRATE:
                                            renderCube(blockPos, grateObject);
                                            break;
                                        case BLOCK_BEDROCK:
                                            renderCube(blockPos, bedrockObject);
                                            break;
                                        default:
                                            break;
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

            DrawText(TextFormat("Non-Air Block Count: %0.0f", (float) cubeAmount), 10, 40, 20, DARKBLUE);
            DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    EnableCursor();
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

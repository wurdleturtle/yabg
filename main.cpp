#include "raylib.h"
#include "raymath.h"
#include "BlockRenderer.cpp"

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
    cubeObject boneObject = InitializeLogObject("textures/bone.png", "textues/boneend.png");
    cubeObject grateObject = InitializeLogObject("textures/grate.png", "textures/grate.png");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = Vector3{ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 30.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    double dt = 0;

    int cubeAmount = 1;
    
    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    Vector3 cubeVelocity = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(60);                   // Set the game to run at 60 frames-per-second

    

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        dt = GetFrameTime();

        Vector3 targetPosition = cubePosition;
        if (cubeAmount > 0) {
            int maxLayer = (cubeAmount - 1) / 25;
            // Target the center of the top layer (5x5 grid, center is at index 2,2)
            targetPosition = Vector3Add(cubePosition, {-2.0f, (float)maxLayer, 2.0f});
        }

        camera.target = targetPosition;
        if (IsKeyDown(KEY_SPACE)){
            UpdateCamera(&camera, CAMERA_ORBITAL);
            UpdateCamera(&camera, CAMERA_ORBITAL);
        } else{
            camera.position = Vector3Subtract(Vector3Add(targetPosition, {10.0f, 10.0f, 10.0f}), cubeVelocity);
        }
        movespeed = basemovespeed * dt;

        // Input

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            cubeAmount++;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (cubeAmount > 1) cubeAmount--;
        }

        if (IsKeyDown(KEY_LEFT_ALT)) {
            cubeAmount++;
        }

        if (IsKeyDown(KEY_X)) {
            cubeAmount--;
        }

        if (IsKeyDown(KEY_Q)) {
            camera.position.y--;
        }
        if (IsKeyDown(KEY_E)) {
            camera.position.y++;
        }

        if (IsKeyDown(KEY_W)) {
            cubeVelocity.z -= movespeed;
            cubeVelocity.x -= movespeed;
        } if (IsKeyDown(KEY_S)) {
            cubeVelocity.z += movespeed;
            cubeVelocity.x += movespeed;
        }
        
        if (IsKeyDown(KEY_A)) {
            cubeVelocity.x -= movespeed;
            cubeVelocity.z += movespeed;
        } if (IsKeyDown(KEY_D)) {
            cubeVelocity.x += movespeed;
            cubeVelocity.z -= movespeed;
        }

        // cubeVelocity = Vector3Clamp(cubeVelocity, {-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f});

                    // Friction
        cubeVelocity = Vector3Multiply(cubeVelocity, { 0.85f, 0.85f, 0.85f});

        cubePosition = Vector3Add(cubePosition, cubeVelocity);

        // Draw
        BeginDrawing();

            ClearBackground(SKYBLUE);  

            BeginMode3D(camera);

                //    for (int i = 0; i <cubeAmount; i++) {
                //        renderCube(Vector3Add(cubePosition, {(float) -i, 0.0f, 0.0f}), oakObject);
                //    }

                    for (int i = 0; i < cubeAmount; i++) {
                        int layer = i / 25;
                        int remainder = i % 25;
                        int row = remainder / 5;
                        int col = remainder % 5;
                        
                        renderCube(Vector3Add(cubePosition, {(float) -row, (float) layer, (float) col}), oakObject);
                    }

                DrawGrid(10000, 1.0f);

            EndMode3D();

            DrawText(TextFormat("Oak Amount: %0.0f", (float) cubeAmount), 10, 100, 20, DARKBLUE);
            DrawText(TextFormat("VX: %0.4f, VZ, %0.4f", cubeVelocity.x, cubeVelocity.z), 10, 70, 20, DARKGRAY);
            DrawText(TextFormat("X: %0.4f, Z: %0.4f", cubePosition.x, cubePosition.z), 10, 40, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    EnableCursor();
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

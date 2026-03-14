#include "raylib.h"
#include "raymath.h"
#include <vector>

struct Blockpos {
    int x;
    int y; 
    int z;
    Color c;

    Vector3 toVector3() const {
        return {(float)x, (float)y, (float)z};
    }
};



int main() {
    InitWindow(800, 600, "Raylib + CMake");

    Camera3D camera = {};
    camera.fovy = 90;
    camera.position = {10, 10, 10};
    camera.projection = CAMERA_PERSPECTIVE;
    camera.target = {0, 0, 0};
    camera.up = {0, 1, 0};

    std::vector<Blockpos> Blocks;

    int count = 0;

    Blocks.push_back({0, 0, 0});
    
    Blockpos selectionPos = {0, 0, 0, WHITE};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        camera.position = Vector3Add(selectionPos.toVector3(), {5, 5, 5});
        camera.target = selectionPos.toVector3();

        if (IsKeyPressed(KEY_SPACE)) {
            Blocks.push_back(selectionPos);
        }

        if (IsKeyPressed(KEY_ONE)) selectionPos.c = WHITE;
        if (IsKeyPressed(KEY_TWO)) selectionPos.c = RED;
        if (IsKeyPressed(KEY_THREE)) selectionPos.c = ORANGE;
        if (IsKeyPressed(KEY_FOUR)) selectionPos.c = YELLOW;
        if (IsKeyPressed(KEY_FIVE)) selectionPos.c = GREEN;
        if (IsKeyPressed(KEY_SIX)) selectionPos.c = BLUE;

        if (IsKeyPressed(KEY_A)) {
            selectionPos.x--;
        }

        if (IsKeyPressed(KEY_D)) {
            selectionPos.x++;
        }

        if (IsKeyPressed(KEY_W)) {
            selectionPos.z--;
        }

        if (IsKeyPressed(KEY_S)) {
            selectionPos.z++;
        }

        if (IsKeyPressed(KEY_Q)) {
            selectionPos.y--;
        }

        if (IsKeyPressed(KEY_E)) {
            selectionPos.y++;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
        for (const Blockpos& block : Blocks) {
            DrawCubeV(block.toVector3(), {1, 1, 1}, block.c);
            DrawCubeWiresV({block.toVector3()}, {1, 1, 1}, BLACK);
            count++;
        }

        DrawCubeWiresV({selectionPos.toVector3()}, {1.01, 1.01, 1.01}, WHITE);

        EndMode3D();
        DrawFPS(10, 10);
        DrawCircle(25, 25, 5, selectionPos.c);
        DrawText(TextFormat("Vector Length: %0.0f", (float)count), 10, 30, 10, RED);
        count = 0;
        EndDrawing();
    }

    CloseWindow();
}

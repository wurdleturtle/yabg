#include "raylib.h"
#include "raymath.h"
#include <vector>

struct Blockpos {
    int x;
    int y; 
    int z;

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

    Blocks.push_back({0, 0, 0});
    
    Blockpos selectionPos = {0, 0, 0};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        camera.position = Vector3Add(selectionPos.toVector3(), {5, 5, 5});
        camera.target = selectionPos.toVector3();

        if (IsKeyPressed(KEY_SPACE)) {
            Blocks.push_back(selectionPos);
        }

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
            DrawCubeV(block.toVector3(), {1, 1, 1}, RED);
            DrawCubeWiresV({block.toVector3()}, {1, 1, 1}, BLACK);
        }

        DrawCubeWiresV({selectionPos.toVector3()}, {1.01, 1.01, 1.01}, WHITE);

        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}

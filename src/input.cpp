#include "input.h"

#include "raylib.h"
#include "world.h"

void HandleEditorInput(Block &selectionPos, World &world) {
  if (IsKeyPressed(KEY_ENTER)) {
    world.AddBlock(selectionPos);
  }
  if (IsKeyPressed(KEY_BACKSPACE)) {
    world.RemoveBlock(selectionPos);
  }

  if (IsKeyPressed(KEY_LEFT)) {
    selectionPos.x--;
  }

  if (IsKeyPressed(KEY_RIGHT)) {
    selectionPos.x++;
  }

  if (IsKeyPressed(KEY_UP)) {
    selectionPos.z--;
  }

  if (IsKeyPressed(KEY_DOWN)) {
    selectionPos.z++;
  }

  if (IsKeyPressed(KEY_Q)) {
    selectionPos.y--;
  }

  if (IsKeyPressed(KEY_E)) {
    selectionPos.y++;
  }
}

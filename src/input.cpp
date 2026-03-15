#include "input.h"

#include "raylib.h"
#include "world.h"

void HandleEditorInput(Block &selectionPos, World &world) {
  if (IsKeyPressed(KEY_SPACE)) {
    world.AddBlock(selectionPos);
  }
  if (IsKeyPressed(KEY_BACKSPACE)) {
    world.RemoveBlock(selectionPos);
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
}

#include "input.h"

#include "raylib.h"
#include "world.h"

void HandleEditorInput(Block &selectionPos, World &world, BlockType &type)
{

  if (IsKeyPressed(KEY_ONE))
    type = BlockType::Bedrock;
  if (IsKeyPressed(KEY_TWO))
    type = BlockType::Dirt;
  if (IsKeyPressed(KEY_THREE))
    type = BlockType::Grass;
  if (IsKeyPressed(KEY_FOUR))
    type = BlockType::Stone;
  if (IsKeyPressed(KEY_FIVE))
    type = BlockType::Sand;
  if (IsKeyPressed(KEY_SIX))
    type = BlockType::Plank;
  if (IsKeyPressed(KEY_SEVEN))
    type = BlockType::Log;
  if (IsKeyPressed(KEY_ENTER))
  {
    world.AddBlock(selectionPos, type);
  }
  if (IsKeyPressed(KEY_BACKSPACE))
  {
    world.RemoveBlock(selectionPos);
  }

  if (IsKeyPressed(KEY_LEFT))
  {
    selectionPos.x--;
  }

  if (IsKeyPressed(KEY_RIGHT))
  {
    selectionPos.x++;
  }

  if (IsKeyPressed(KEY_UP))
  {
    selectionPos.z--;
  }

  if (IsKeyPressed(KEY_DOWN))
  {
    selectionPos.z++;
  }

  if (IsKeyPressed(KEY_Q))
  {
    selectionPos.y--;
  }

  if (IsKeyPressed(KEY_E))
  {
    selectionPos.y++;
  }
}

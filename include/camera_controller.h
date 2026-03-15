#pragma once

#include "block.h"
#include "raylib.h"

void UpdateEditorCamera(Camera3D &camera, const Block &selectionPos);

Camera3D CreateDefaultEditorCamera();

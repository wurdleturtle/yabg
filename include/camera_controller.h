#pragma once

#include "raylib.h"

struct PlayerCameraState {
  float yaw = -90.0f;
  float pitch = 0.0f;
  float moveSpeed = 8.0f;
  float mouseSensitivity = 0.10f;
};

void UpdatePlayerCamera(Camera3D &camera, PlayerCameraState &state, float dt);

Camera3D CreateDefaultPlayerCamera();

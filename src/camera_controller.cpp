#include "camera_controller.h"

#include "raylib.h"
#include "raymath.h"

Camera3D CreateDefaultPlayerCamera() {
  Camera3D camera = {};
  camera.fovy = 90.0f;
  camera.position = {10.0f, 10.0f, 10.0f};
  camera.projection = CAMERA_PERSPECTIVE;
  camera.up = {0.0f, 1.0f, 0.0f};

  // Facing -Z at startup
  camera.target = Vector3Add(camera.position, {0.0f, 0.0f, -1.0f});
  return camera;
}

void UpdatePlayerCamera(Camera3D &camera, PlayerCameraState &state, float dt) {
  Vector2 mouseDelta = GetMouseDelta();
  state.yaw += mouseDelta.x * state.mouseSensitivity;
  state.pitch -= mouseDelta.y * state.mouseSensitivity;

  state.pitch = Clamp(state.pitch, -89.0f, 89.0f);

  // yaw/pitch to an actual target direction
  const float yawRad = state.yaw * DEG2RAD;
  const float pitchRad = state.pitch * DEG2RAD;

  Vector3 forward = {
      sinf(yawRad) * cosf(pitchRad),
      sinf(pitchRad),
      -cosf(yawRad) * cosf(pitchRad),
  };

  forward = Vector3Normalize(forward);

  Vector3 worldUp{0.0f, 1.0f, 0.0f};
  Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, worldUp));

  Vector3 movement = {0.0f, 0.0f, 0.0f};

  if (IsKeyDown(KEY_W))
    movement = Vector3Add(movement, forward);
  if (IsKeyDown(KEY_S))
    movement = Vector3Subtract(movement, forward);
  if (IsKeyDown(KEY_D))
    movement = Vector3Add(movement, right);
  if (IsKeyDown(KEY_A))
    movement = Vector3Subtract(movement, right);
  if (IsKeyDown(KEY_SPACE))
    movement.y += 1.0f;
  if (IsKeyDown(KEY_LEFT_CONTROL))
    movement.y -= 1.0f;

  if (Vector3LengthSqr(movement) > 0.0f) {
    movement = Vector3Normalize(movement);
    movement = Vector3Scale(movement, state.moveSpeed * dt);
    camera.position = Vector3Add(camera.position, movement);
  }

  camera.target = Vector3Add(camera.position, forward);
  camera.up = worldUp;
}

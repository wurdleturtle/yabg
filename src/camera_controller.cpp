#include "camera_controller.h"

#include "raymath.h"

Camera3D CreateDefaultEditorCamera() {
  Camera3D camera = {};
  camera.fovy = 90.0f;
  camera.position = {10.0f, 10.0f, 10.0f};
  camera.projection = CAMERA_PERSPECTIVE;
  camera.target = {0.0f, 0.0f, 0.0f};
  camera.up = {0.0f, 1.0f, 0.0f};
  return camera;
}

void UpdateEditorCamera(Camera3D &camera, const Block &selectionPos) {
  const Vector3 followOffset = {5.0f, 5.0f, 5.0f};

  const Vector3 target = selectionPos.toVector3();

  camera.target = target;

  camera.position = Vector3Add(target, followOffset);

  camera.up = {0.0f, 1.0f, 0.0f};
}

#pragma once

#include "utils.h"          // Required for: TRACELOG(), LoadFileData(), LoadFileText(), SaveFileText()
#include "rlgl.h"           // OpenGL abstraction layer to OpenGL 1.1, 2.1, 3.3+ or ES2
#include "raymath.h"        // Required for: Vector3, Quaternion and Matrix functionality
#include "raylib.h"
#include <stdio.h>          // Required for: sprintf()
#include <stdlib.h>         // Required for: malloc(), free()
#include <string.h>         // Required for: memcmp(), strlen()
#include <math.h>           // Required for: sinf(), cosf(), sqrtf(), fabsf()

Mesh GenCubeMeshFront(float width, float height, float length)
{
    Mesh mesh = { 0 };

#define CUSTOM_MESH_GEN_CUBE
#if defined(CUSTOM_MESH_GEN_CUBE)
    float vertices[] = {
        -width/2, -height/2, length/2,
        width/2, -height/2, length/2,
        width/2, height/2, length/2,
        -width/2, height/2, length/2,
    };

    float texcoords[] = {
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        // FRONT ^
    };

    mesh.vertices = (float *)RL_MALLOC(4*3*sizeof(float));
    memcpy(mesh.vertices, vertices, 4*3*sizeof(float));

    mesh.texcoords = (float *)RL_MALLOC(4*2*sizeof(float));
    memcpy(mesh.texcoords, texcoords, 4*2*sizeof(float));

    mesh.indices = (unsigned short *)RL_MALLOC(6*sizeof(unsigned short));

    int k = 0;

    // Indices can be initialized right now
    for (int i = 0; i < 6; i += 6)
    {
        mesh.indices[i] = 4*k;
        mesh.indices[i + 1] = 4*k + 1;
        mesh.indices[i + 2] = 4*k + 2;
        mesh.indices[i + 3] = 4*k;
        mesh.indices[i + 4] = 4*k + 2;
        mesh.indices[i + 5] = 4*k + 3;

        k++;
    }

    mesh.vertexCount = 24;
    mesh.triangleCount = 12;

#endif

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}

Mesh GenCubeMeshTop(float width, float height, float length)
{
    Mesh mesh = { 0 };

#define CUSTOM_MESH_GEN_CUBE
#if defined(CUSTOM_MESH_GEN_CUBE)
    float vertices[] = {
        -width/2, height/2, -length/2,
        -width/2, height/2, length/2,
        width/2, height/2, length/2,
        width/2, height/2, -length/2,
    };

    float texcoords[] = {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        // TOP ^
    };

    mesh.vertices = (float *)RL_MALLOC(4*3*sizeof(float));
    memcpy(mesh.vertices, vertices, 4*3*sizeof(float));

    mesh.texcoords = (float *)RL_MALLOC(4*2*sizeof(float));
    memcpy(mesh.texcoords, texcoords, 4*2*sizeof(float));

    mesh.indices = (unsigned short *)RL_MALLOC(6*sizeof(unsigned short));

    int k = 0;

    // Indices can be initialized right now
    for (int i = 0; i < 6; i += 6)
    {
        mesh.indices[i] = 4*k;
        mesh.indices[i + 1] = 4*k + 1;
        mesh.indices[i + 2] = 4*k + 2;
        mesh.indices[i + 3] = 4*k;
        mesh.indices[i + 4] = 4*k + 2;
        mesh.indices[i + 5] = 4*k + 3;

        k++;
    }

    mesh.vertexCount = 24;
    mesh.triangleCount = 12;

#endif

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}

Mesh GenCubeMeshRight(float width, float height, float length)
{
    Mesh mesh = { 0 };

#define CUSTOM_MESH_GEN_CUBE
#if defined(CUSTOM_MESH_GEN_CUBE)
    float vertices[] = {
        width/2, -height/2, -length/2,
        width/2, height/2, -length/2,
        width/2, height/2, length/2,
        width/2, -height/2, length/2,
    };

    float texcoords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };

    mesh.vertices = (float *)RL_MALLOC(4*3*sizeof(float));
    memcpy(mesh.vertices, vertices, 4*3*sizeof(float));

    mesh.texcoords = (float *)RL_MALLOC(4*2*sizeof(float));
    memcpy(mesh.texcoords, texcoords, 4*2*sizeof(float));

    mesh.indices = (unsigned short *)RL_MALLOC(6*sizeof(unsigned short));

    int k = 0;

    // Indices can be initialized right now
    for (int i = 0; i < 6; i += 6)
    {
        mesh.indices[i] = 4*k;
        mesh.indices[i + 1] = 4*k + 1;
        mesh.indices[i + 2] = 4*k + 2;
        mesh.indices[i + 3] = 4*k;
        mesh.indices[i + 4] = 4*k + 2;
        mesh.indices[i + 5] = 4*k + 3;

        k++;
    }

    mesh.vertexCount = 24;
    mesh.triangleCount = 12;

#endif

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}

Mesh GenCubeMeshLeft(float width, float height, float length)
{
    Mesh mesh = { 0 };

#define CUSTOM_MESH_GEN_CUBE
#if defined(CUSTOM_MESH_GEN_CUBE)
    float vertices[] = {
        -width/2, -height/2, -length/2,
        -width/2, -height/2, length/2,
        -width/2, height/2, length/2,
        -width/2, height/2, -length/2
    };

    float texcoords[] = {
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
        // LEFT ^
    };

    mesh.vertices = (float *)RL_MALLOC(4*3*sizeof(float));
    memcpy(mesh.vertices, vertices, 4*3*sizeof(float));

    mesh.texcoords = (float *)RL_MALLOC(4*2*sizeof(float));
    memcpy(mesh.texcoords, texcoords, 4*2*sizeof(float));

    mesh.indices = (unsigned short *)RL_MALLOC(6*sizeof(unsigned short));

    int k = 0;

    // Indices can be initialized right now
    for (int i = 0; i < 6; i += 6)
    {
        mesh.indices[i] = 4*k;
        mesh.indices[i + 1] = 4*k + 1;
        mesh.indices[i + 2] = 4*k + 2;
        mesh.indices[i + 3] = 4*k;
        mesh.indices[i + 4] = 4*k + 2;
        mesh.indices[i + 5] = 4*k + 3;

        k++;
    }

    mesh.vertexCount = 24;
    mesh.triangleCount = 12;

#endif

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}

Mesh GenCubeMeshBack(float width, float height, float length)
{
    Mesh mesh = { 0 };

#define CUSTOM_MESH_GEN_CUBE
#if defined(CUSTOM_MESH_GEN_CUBE)
    float vertices[] = {
        -width/2, -height/2, -length/2,
        -width/2, height/2, -length/2,
        width/2, height/2, -length/2,
        width/2, -height/2, -length/2,
    };

    float texcoords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };

    mesh.vertices = (float *)RL_MALLOC(4*3*sizeof(float));
    memcpy(mesh.vertices, vertices, 4*3*sizeof(float));

    mesh.texcoords = (float *)RL_MALLOC(4*2*sizeof(float));
    memcpy(mesh.texcoords, texcoords, 4*2*sizeof(float));

    mesh.indices = (unsigned short *)RL_MALLOC(6*sizeof(unsigned short));

    int k = 0;

    // Indices can be initialized right now
    for (int i = 0; i < 6; i += 6)
    {
        mesh.indices[i] = 4*k;
        mesh.indices[i + 1] = 4*k + 1;
        mesh.indices[i + 2] = 4*k + 2;
        mesh.indices[i + 3] = 4*k;
        mesh.indices[i + 4] = 4*k + 2;
        mesh.indices[i + 5] = 4*k + 3;

        k++;
    }

    mesh.vertexCount = 24;
    mesh.triangleCount = 12;
#endif

    UploadMesh(&mesh, false);

    return mesh;
}

Mesh GenCubeMeshBottom(float width, float height, float length)
{
    Mesh mesh = { 0 };

#define CUSTOM_MESH_GEN_CUBE
#if defined(CUSTOM_MESH_GEN_CUBE)
    float vertices[] = {
        -width/2, -height/2, -length/2,
        width/2, -height/2, -length/2,
        width/2, -height/2, length/2,
        -width/2, -height/2, length/2
    };

    float texcoords[] = {
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
    };

    mesh.vertices = (float *)RL_MALLOC(4*3*sizeof(float));
    memcpy(mesh.vertices, vertices, 4*3*sizeof(float));

    mesh.texcoords = (float *)RL_MALLOC(4*2*sizeof(float));
    memcpy(mesh.texcoords, texcoords, 4*2*sizeof(float));

    mesh.indices = (unsigned short *)RL_MALLOC(6*sizeof(unsigned short));

    int k = 0;
    for (int i = 0; i < 6; i += 6)
    {
        mesh.indices[i] = 4*k;
        mesh.indices[i + 1] = 4*k + 2;
        mesh.indices[i + 2] = 4*k + 1;
        mesh.indices[i + 3] = 4*k;
        mesh.indices[i + 4] = 4*k + 3;
        mesh.indices[i + 5] = 4*k + 2;
        k++;
    }

    mesh.vertexCount = 24;
    mesh.triangleCount = 12;
#endif

    UploadMesh(&mesh, false);
    return mesh;
}

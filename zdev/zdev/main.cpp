#include "../../include/HammerEngine/HammerEngine.h"
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

std::vector<Vertex> verticesraw = {
    // Front (tile 0,0)
    {{-0.5f, -0.5f, 0.0f},{1.0f,0.0f,0.0f},{0.0000f,0.0625f}},
    {{0.5f, -0.5f, 0.0f},{0.0f,1.0f,0.0f},{0.0625f,0.0625f}},
    {{0.5f, 0.5f, 0.0f},{0.0f,0.0f,1.0f},{0.0625f,0.0000f}},
    {{-0.5f, 0.5f, 0.0f},{1.0f,1.0f,0.0f},{0.0000f,0.0000f}},
};

std::vector<uint32_t> indicesraw = {
    0, 1, 2,
    2, 3, 0,
};

// === Entry Point ===
int main() {
    HammerEngine Engine;


    for (int x = 0; x < 500; x++) {
        for (int y = 0; y < 500; y++) {
            uint32_t offset = static_cast<uint32_t>(vertices.size());

            vertices.push_back({{-0.5f + x, -0.5f + y, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0000f, 0.0625f}}); // Bottom Left
            vertices.push_back({{ 0.5f + x, -0.5f + y, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0625f, 0.0625f}}); // Bottom Right
            vertices.push_back({{ 0.5f + x,  0.5f + y, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0625f, 0.0000f}}); // Top Right
            vertices.push_back({{-0.5f + x,  0.5f + y, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0000f, 0.0000f}}); // Top Left

            indices.push_back(offset + 0);
            indices.push_back(offset + 1);
            indices.push_back(offset + 2);
            
            indices.push_back(offset + 2);
            indices.push_back(offset + 3);
            indices.push_back(offset + 0);
        }
    }

    Engine.setMaxVertciesIndicesSize(sizeof(Vertex) * vertices.size());
    Engine.vertShaderPath = "shaders/vert.spv";
    Engine.fragShaderPath = "shaders/frag.spv";
    Engine.enableValidationLayers = true;
    Engine.WindowWidth = 1000;
    Engine.WindowHeight = 1000;
    Engine.texturePath = "textures/texture.png";
    Engine.cameraPosition = glm::vec3(0,0,2);
    Engine.cameraMode(0);
    Engine.cameraSpeed = 1;
    Engine.drawMod(0);
    Engine.triangleMode = true;

    Engine.initWindow();
    Engine.initVulkan();

    Engine.drawPassStart();
    while (!glfwWindowShouldClose(Engine.window)) {
        Engine.updateFrameTimeStart();

        Engine.updateCameraDefault3D();

        Engine.drawFrame();

        Engine.updateFrameTimeEnd();
    }
    Engine.drawPassEnd();

    return EXIT_SUCCESS;
}

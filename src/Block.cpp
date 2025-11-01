//
// Created by ju on 10/31/25.
//

#include "Block.h"
#include "World.h"
#include "Chunk.h"
#include "glm/vec2.hpp"
#include <Eigen/Dense>

#include "glm/vec4.hpp"
constexpr glm::vec3 cubeCorners[8] = {
    {-0.5f, -0.5f, -0.5f}, // 0
    { 0.5f, -0.5f, -0.5f}, // 1
    { 0.5f,  0.5f, -0.5f}, // 2
    {-0.5f,  0.5f, -0.5f}, // 3
    {-0.5f, -0.5f,  0.5f}, // 4
    { 0.5f, -0.5f,  0.5f}, // 5
    { 0.5f,  0.5f,  0.5f}, // 6
    {-0.5f,  0.5f,  0.5f}  // 7
};

// Each face is 4 indices (quad) in CCW order
constexpr glm::uvec4 cubeFaces[6] = {
    {4, 5, 6, 7}, // front
    {1, 0, 3, 2}, // back
    {0, 4, 7, 3}, // left
    {5, 1, 2, 6}, // right
    {3, 7, 6, 2}, // top
    {0, 1, 5, 4}  // bottom
};

constexpr glm::vec2 quadUVs[4] = {
    {0.0f, 0.0f},
    {1.0f, 0.0f},
    {1.0f, 1.0f},
    {0.0f, 1.0f}
};

constexpr float textureDim[6] = {
    1.0f, // front
    0.6f, // back
    0.4f, // left
    0.8f, // right
    1.0f, // top
    0.2f, // bottom
};


void Block::appendFacesVerticesAndIndices(glMeshData &to, glm::uvec3 direction) {
    // Map direction to face index (0..5)
    int faceIndex = -1;
    if (direction == glm::uvec3( 0, 0, 1)) faceIndex = 0; // front
    if (direction == glm::uvec3( 0, 0,-1)) faceIndex = 1; // back
    if (direction == glm::uvec3(-1, 0, 0)) faceIndex = 2; // left
    if (direction == glm::uvec3( 1, 0, 0)) faceIndex = 3; // right
    if (direction == glm::uvec3( 0, 1, 0)) faceIndex = 4; // top
    if (direction == glm::uvec3( 0,-1, 0)) faceIndex = 5; // bottom

    if (faceIndex == -1) return;

    std::vector<float> vertices;
    for (int i = 0; i < 4; ++i) {
        glm::vec3 pos = cubeCorners[cubeFaces[faceIndex][i]] + glm::vec3(position);
        glm::vec2 uv = quadUVs[i];
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);
        vertices.push_back(uv.x);
        vertices.push_back(uv.y);
        vertices.push_back(textureDim[faceIndex]);
    }

    unsigned int indices[] = {0, 1, 2, 2, 3, 0};
    for (auto &i : indices) i += to.index;

    to.indices.insert(to.indices.end(), std::begin(indices), std::end(indices));
    to.vertices.insert(to.vertices.end(), vertices.begin(), vertices.end());
    to.index += 4;
}

void Block::generateFaces( glMeshData & data, Chunk * chunk) {
    if (air) {
        return;
    }
    glm::ivec3 offsets [6]= {
        {1,0,0},
        {-1,0,0},
        {0,1,0},
        {0,-1,0},
        {0,0,1},
        {0,0,-1},
    };
    for (auto offset: offsets) {
        glm::uvec3 pos = position - chunk->getChunkPositionOffset() + offset;
        if (
            pos.y >= Chunk::DIMENSIONS.y||
            pos.x >= Chunk::DIMENSIONS.x||
            pos.z >= Chunk::DIMENSIONS.z||
            pos.x < 0||
            pos.y < 0||
            pos.z < 0
            ) {continue; }
        const Block& block = chunk->blockAt(pos);
        bool fill = false;
        fill = block.isAir();
        if (fill) {
            appendFacesVerticesAndIndices(data, offset);
        }
    }
}

bool Block::generateFacesBetweenChunks(glMeshData &to, glm::ivec3 direction, World *world) {
    Block* block = world->getBlockAt(position + direction);
    if (block == nullptr) {
        return false;
    }
    if (!block->isAir()) {
        return false;
    }
    appendFacesVerticesAndIndices(to, direction);
    return true;
}

//
// Created by ju on 10/31/25.
//

#pragma once
#include <vector>

#include "Block.h"
#include "ChunkMeshDataStruct.h"
#include "glm/vec3.hpp"

class Chunk {
    static constexpr glm::uvec3 DIMENSIONS = glm::uvec3(200,256,200);
    Block blocks[DIMENSIONS.x][DIMENSIONS.y][DIMENSIONS.z];

public:
    glMeshData data;
    bool blockAt(glm::uvec3 pos);
    Chunk();
};


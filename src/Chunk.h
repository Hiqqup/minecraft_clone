//
// Created by ju on 10/31/25.
//

#pragma once
#include <vector>

#include "Block.h"
#include "ChunkMeshDataStruct.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class Chunk {
    static constexpr glm::uvec3 DIMENSIONS = glm::uvec3(16,128,16);
    Block blocks[DIMENSIONS.x][DIMENSIONS.y][DIMENSIONS.z];
    glm::ivec3 chunkPositionOffset;

public:
    [[nodiscard]] glm::ivec3 getChunkPositionOffset() const {
        return chunkPositionOffset;
    }

    glMeshData data;
    bool blockAt(glm::uvec3 pos);
    Chunk(const glm::ivec2 & chunkPositionUnscaled);
};


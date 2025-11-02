//
// Created by ju on 10/31/25.
//

#pragma once

#include "Block.h"
#include "Camera.h"
#include "ChunkMeshDataStruct.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class World;
class Chunk {
public:
    static constexpr glm::uvec3 DIMENSIONS = glm::uvec3(16,128,16);
    private:
    unsigned int heightMap[DIMENSIONS.x * DIMENSIONS.z];
    std::array<Block, DIMENSIONS.x*DIMENSIONS.y*DIMENSIONS.z> blocks;
    glm::ivec3 chunkPositionOffset;

public:
    [[nodiscard]] glm::ivec3 getChunkPositionOffset() const {
        return chunkPositionOffset;
    }

    glMeshData data;

    Block &blockAt(glm::ivec3 pos);
    explicit Chunk(const glm::ivec2 & chunkPositionUnscaled);
    void patchUpBorders(World * world, glm::ivec2 chunkIndex);
};


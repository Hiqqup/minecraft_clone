//
// Created by ju on 10/31/25.
//

#pragma once
#include "Block.h"
#include "ChunkMeshDataStruct.h"
#include "glm/vec3.hpp"



class Chunk;
class World;
class Block {
    glm::ivec3 position;
    bool air;
public:
    [[nodiscard]]bool isAir() const {
        return air;
    }
    void setProps(const glm::ivec3 &position, const bool air) {
        this->position = position;
        this->air = air;
    }
    void appendFacesVerticesAndIndices(glMeshData &to, glm::ivec3 direction) const;
    void generateFaces( glMeshData & data, Chunk * chunk) const;

    bool generateFacesBetweenChunks(glMeshData &to, const glm::ivec3 & direction, World *world) const;
};

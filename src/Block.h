//
// Created by ju on 10/31/25.
//

#pragma once
#include "ChunkMeshDataStruct.h"
#include "glm/vec3.hpp"



class Chunk;
class Block {
    glm::uvec3 position;
    bool air;
public:
    [[nodiscard]]bool isAir() const {
        return air;
    }
    void setProps(const glm::uvec3 &position, const bool air) {
        this->position = position;
        this->air = air;
    }
    void appendFacesVerticesAndIndices(glMeshData &to, glm::uvec3 direction);
    void generateFaces( glMeshData & data, Chunk * chunk);
};

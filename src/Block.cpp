//
// Created by ju on 10/31/25.
//

#include "Block.h"

#include "Chunk.h"
#include "glm/vec2.hpp"
#include <Eigen/Dense>
constexpr float frontFace[] = {
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
       };

   constexpr float backFace[] = {
       -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
   };


    constexpr float leftFace[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
    };

    constexpr float rightFace[] = {
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
    };

    constexpr float bottomFace[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    };

    constexpr float topFace[] = {
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f
    };


void Block::appendFacesVerticesAndIndices(glMeshData &to, glm::uvec3 direction) {
    std::vector<float> vertices ;
    if (direction.x == 1) {
        vertices= std::vector<float>(std::begin(rightFace), std::end(rightFace));
    }
    if (direction.x == -1) {
        vertices= std::vector<float>(std::begin(leftFace), std::end(leftFace));
    }
    if (direction.y == 1) {
        vertices= std::vector<float>(std::begin(topFace), std::end(topFace));
    }
    if (direction.y == -1) {
        vertices= std::vector<float>(std::begin(bottomFace), std::end(bottomFace));
    }
    if (direction.z == 1) {
        vertices= std::vector<float>(std::begin(frontFace), std::end(frontFace));
    }
    if (direction.z == -1) {
        vertices= std::vector<float>(std::begin(backFace), std::end(backFace));
    }


for (size_t i = 0; i < vertices.size(); i += 5) {
    vertices[i + 0] += position.x;
    vertices[i + 1] += position.y;
    vertices[i + 2] += position.z;
}

    unsigned int indices[] ={ 0, 1, 2, 2, 3, 0};
    for (int i = 0; i < std::size(indices); i ++) {
        indices[i] += to.index;
    }
    to.indices.insert( to.indices.end(), std::begin(indices), std::end(indices) );
    to.vertices.insert(to.vertices.end(), vertices.begin(), vertices.end());
    to.index +=4;
}

void Block::generateFaces( glMeshData & data, Chunk * chunk) {
    if (air) {
        return;
    }
    glm::uvec3 offsets [6]= {
        {1,0,0},
        {-1,0,0},
        {0,1,0},
        {0,-1,0},
        {0,0,1},
        {0,0,-1},
    };
    for (auto offset: offsets) {
        glm::uvec3 pos = position + offset;
        if (!chunk->blockAt(pos)) {
            appendFacesVerticesAndIndices(data, offset);
        }
    }
}

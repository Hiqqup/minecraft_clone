//
// Created by ju on 10/31/25.
//

#pragma once
#include <vector>

#include "Chunk.h"


class ChunkMesh {

public:
    Chunk chunk;
private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    int numberOfIndices;
public:
    ChunkMesh(glm::ivec2 chunkPosition);
    void draw()const;
    ~ChunkMesh();

};

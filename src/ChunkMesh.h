//
// Created by ju on 10/31/25.
//

#pragma once
#include <vector>

#include "Chunk.h"


class ChunkMesh {

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    int numberOfIndices;
public:
    explicit ChunkMesh(const Chunk & chunk);
    void draw()const;
    ~ChunkMesh();

};

//
// Created by ju on 10/31/25.
//

#pragma once
#include <vector>

#include "Chunk.h"


class ChunkMesh {

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    int numberOfIndices;
public:
    ChunkMesh(const Chunk & chunk);
    void draw()const;
    ~ChunkMesh();

};

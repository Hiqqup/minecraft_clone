//
// Created by ju on 11/1/25.
//

#pragma once
#include "ChunkMesh.h"

class World {
    static constexpr glm::uvec2 RENDER_DISTANCE = glm::uvec2(8, 8);

    Chunk* chunks[RENDER_DISTANCE.x][RENDER_DISTANCE.y];
    ChunkMesh* meshes[RENDER_DISTANCE.x][RENDER_DISTANCE.y];
public:
    World();
    Block* getBlockAt(glm::ivec3 position);
    void draw()const ;
    ~World() ;
};


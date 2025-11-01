//
// Created by ju on 11/1/25.
//

#include "World.h"

World::World() {
    for (int x = 0; x < RENDER_DISTANCE.x; x++) {
        for (int y = 0; y < RENDER_DISTANCE.y; y++) {
            chunks[x][y] = new Chunk(glm::ivec2{x,y});
        }
    }

    for (int x = 0; x < RENDER_DISTANCE.x; x++) {
        for (int y = 0; y < RENDER_DISTANCE.y; y++) {
            chunks[x][y]->patchUpBorders(this);
        }
    }
    for (int x = 0; x < RENDER_DISTANCE.x; x++) {
        for (int y = 0; y < RENDER_DISTANCE.y; y++) {
            meshes[x][y] = new ChunkMesh(*chunks[x][y]);
        }
    }
}//
Block * World::getBlockAt(glm::ivec3 position) {
    if (position.x < 0 || position.z < 0||
        position.x >= RENDER_DISTANCE.x * Chunk::DIMENSIONS.x||
        position.z >= RENDER_DISTANCE.y * Chunk::DIMENSIONS.z
        ) {
        return nullptr;
    }
    glm::ivec2 chunkIndex = {
        (static_cast<float>(position.x) /static_cast<float> (Chunk::DIMENSIONS.x)),
        (static_cast<float>(position.z)/ static_cast<float>(Chunk::DIMENSIONS.z))
    };
    glm::ivec3 inChunkPosition =glm::ivec3(position) -glm::ivec3(
        chunkIndex.x * Chunk::DIMENSIONS.x,0, chunkIndex.y*Chunk::DIMENSIONS.z ) ;

    return &chunks[chunkIndex.x][chunkIndex.y]->blockAt(inChunkPosition);
}

void World::draw() const {
    for (int x = 0; x < RENDER_DISTANCE.x; x++) {
        for (int y = 0; y < RENDER_DISTANCE.y; y++) {
            meshes[x][y]->draw();
        }
    }
}

World::~World() {
    for (int x = 0; x < RENDER_DISTANCE.x; x++) {
        for (int y = 0; y < RENDER_DISTANCE.y; y++) {
            delete chunks[x][y];
            delete meshes[x][y];
        }
    }
}

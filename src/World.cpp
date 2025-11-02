//
// Created by ju on 11/1/25.
//

#include "World.h"

#include <cmath>
#include <iostream>
#include <ranges>


Block * World::getBlockAt(glm::ivec3 position) {
    glm::ivec2 chunkIndex = {
    std::floor(static_cast<float>(position.x) /static_cast<float>( Chunk::DIMENSIONS.x)),
        std::floor(static_cast<float>(position.z)/static_cast<float>( Chunk::DIMENSIONS.z))
    };
    if (!chunks.contains(chunkIndex)) {
        return nullptr;
    }
    const glm::ivec3 inChunkPosition =glm::ivec3(position) -glm::ivec3(
        chunkIndex.x * Chunk::DIMENSIONS.x,0, chunkIndex.y*Chunk::DIMENSIONS.z ) ;

    return &chunks[{chunkIndex.x,chunkIndex.y}]->blockAt(inChunkPosition);
}

void World::draw() const {
    for (const auto &key: chunks | std::views::keys) {
        meshes.at(key)->draw();
    }
}

World::~World() {
    for (const auto &key: chunks | std::views::keys) {
            delete chunks[key];
            delete meshes[key];
    }
}

void World::updatePlayerPositionRenderNewChunks(glm::ivec2 playerPosition) {
     const glm::ivec2 newPlayerChunkIndex = {
    std::floor(static_cast<float>(playerPosition.x) /static_cast<float>( Chunk::DIMENSIONS.x)),
        std::floor(static_cast<float>(playerPosition.y)/static_cast<float>( Chunk::DIMENSIONS.z))
    };
    for (int renderDistanceOffsetX = -RENDER_DISTANCE.x; renderDistanceOffsetX <= RENDER_DISTANCE.x; ++renderDistanceOffsetX) {
        for (int renderDistanceOffsetY = -RENDER_DISTANCE.y; renderDistanceOffsetY <= RENDER_DISTANCE.y; ++renderDistanceOffsetY) {
            glm::ivec2 renderDistanceOffset = {renderDistanceOffsetX, renderDistanceOffsetY};
            renderNewChunk(newPlayerChunkIndex + renderDistanceOffset);
        }
    }
}

void World::renderNewChunk(glm::ivec2 index) {
    if (chunks.contains(index)) {
        return;
    }
    chunks[index] = new Chunk(index);
    chunks[index]->patchUpBorders(this,index);
    glm::ivec2 neighbors[4] = {
        {1,0},
        {-1,0},
        {0, 1,},
        {0,-1},
    };
     for (const auto &neighbor: neighbors) {
         if (!chunks.contains(index+ neighbor)) {
             continue;
         }
         chunks[index +neighbor]->patchUpBorders(this, neighbor);
         delete meshes[index +neighbor];
         meshes[index +neighbor] = new ChunkMesh(*chunks[index + neighbor]);
     }
    meshes[index] = new ChunkMesh(*chunks[index]);
}

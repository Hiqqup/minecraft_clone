//
// Created by ju on 10/31/25.
//

#include "Chunk.h"
#define STB_PERLIN_IMPLEMENTATION
#include <stb_perlin.h>

bool Chunk::blockAt(glm::uvec3 pos) {
    if (
        pos.y >= DIMENSIONS.y||
        pos.y < 0
        ) {return false; }
    if (
        pos.x >= DIMENSIONS.x||
        pos.z >= DIMENSIONS.z||
        pos.x < 0||
        pos.z < 0
        ) {return true; }
    return !blocks[pos.x][pos.y][pos.z].isAir();
}
Chunk::Chunk(const glm::ivec2 & chunkPositionUnscaled):
    chunkPositionOffset ( glm::ivec3(chunkPositionUnscaled.x * DIMENSIONS.x, 0 ,chunkPositionUnscaled.y* DIMENSIONS.z))
{
    unsigned int heightMap[DIMENSIONS.x][DIMENSIONS.z];

    for (int x = 0; x < DIMENSIONS.x; x++) {
        for (int z = 0; z < DIMENSIONS.z; z++) {
            constexpr float scale = 0.1;
            float perlin = stb_perlin_noise3(
                (x+chunkPositionOffset.x)* scale,(z+chunkPositionOffset.z)*scale, 0,0,0,0);
            float perlinNormalized = (perlin + 1.0f ) * 0.5f;
            heightMap[x][z] = 30 +static_cast<int>( perlinNormalized * 20);
        }
    }

    for (int x = 0; x < DIMENSIONS.x; x++) {
        for (int y = 0; y < DIMENSIONS.y; y++) {
            for (int z = 0; z < DIMENSIONS.z; z++) {
                blocks[x][y][z].setProps(glm::ivec3(x, y, z) + chunkPositionOffset, y > heightMap[x][z]);
            }
        }
    }
    for (int x = 0; x < DIMENSIONS.x; x++) {
        for (int y = 0; y < DIMENSIONS.y; y++) {
            for (int z = 0; z < DIMENSIONS.z; z++) {
                blocks[x][y][z].generateFaces(data, this);
            }
        }
    }
}


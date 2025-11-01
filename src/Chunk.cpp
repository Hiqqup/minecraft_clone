//
// Created by ju on 10/31/25.
//

#include "Chunk.h"
#define STB_PERLIN_IMPLEMENTATION
#include <stb_perlin.h>

bool Chunk::blockAt(glm::uvec3 pos) {
    if ( pos.x >= DIMENSIONS.x||
        pos.y >= DIMENSIONS.y||
        pos.z >= DIMENSIONS.z||
        pos.x < 0||
        pos.y < 0||
        pos.z < 0
        ) {return false;
    }
    return !blocks[pos.x][pos.y][pos.z].isAir();
}
Chunk::Chunk() {
    unsigned int heightMap[DIMENSIONS.x][DIMENSIONS.z];

    for (int x = 0; x < DIMENSIONS.x; x++) {
        for (int z = 0; z < DIMENSIONS.z; z++) {
            constexpr float scale = 0.15;
            float perlin = stb_perlin_noise3(x* scale,z*scale, 0,0,0,0);
            float perlinNormalized = (perlin + 1.0f ) * 0.5f;
            heightMap[x][z] = 30 +static_cast<int>( perlinNormalized * 20);
        }
    }

    for (int x = 0; x < DIMENSIONS.x; x++) {
        for (int y = 0; y < DIMENSIONS.y; y++) {
            for (int z = 0; z < DIMENSIONS.z; z++) {
                blocks[x][y][z].setProps({x, y, z}, y > heightMap[x][z]);
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


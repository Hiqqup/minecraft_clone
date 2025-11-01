//
// Created by ju on 10/31/25.
//

#include "World.h"
#include "Chunk.h"
#define STB_PERLIN_IMPLEMENTATION
#include <stb_perlin.h>

Block &Chunk::blockAt(glm::uvec3 pos) {
    return blocks[pos.x][pos.y][pos.z];
}
Chunk::Chunk(const glm::ivec2 & chunkPositionUnscaled):
    chunkPositionOffset ( glm::ivec3(chunkPositionUnscaled.x * DIMENSIONS.x, 0 ,chunkPositionUnscaled.y* DIMENSIONS.z))
{

    for (int x = 0; x < DIMENSIONS.x; x++) {
        for (int z = 0; z < DIMENSIONS.z; z++) {
            constexpr float scale = 0.1;
            float perlin = stb_perlin_noise3(
                (x+chunkPositionOffset.x)* scale,(z+chunkPositionOffset.z)*scale, 0,0,0,0);
            float perlinNormalized = (perlin + 1.0f ) * 0.5f;
            //perlinNormalized   = 0;
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

void Chunk::patchUpBorders(World *world) {
  struct Border {
        glm::ivec3 start;     // starting coordinate (x, y placeholder, z)
        glm::ivec3 step;      // which axis to iterate along
        glm::ivec3 direction; // direction for face generation
        unsigned int length;  // how many iterations
    };

    Border borders[] = {
        {{0, 0, 0}, {1, 0, 0}, {0, 0, -1}, DIMENSIONS.x},          // front
        {{0, 0, DIMENSIONS.z - 1}, {1, 0, 0}, {0, 0, 1}, DIMENSIONS.x}, // back
        {{0, 0, 0}, {0, 0, 1}, {-1, 0, 0}, DIMENSIONS.z},          // left
        {{DIMENSIONS.x - 1, 0, 0}, {0, 0, 1}, {1, 0, 0}, DIMENSIONS.z}   // right
    };

    for (const auto& border : borders) {
        glm::ivec3 pos = border.start;
        for (unsigned int i = 0; i < border.length; i++) {
            int y = heightMap[pos.x][pos.z];
            bool propergateDown = true;
            while (propergateDown) {
                propergateDown = blocks[pos.x][y][pos.z].generateFacesBetweenChunks(
                    data, border.direction, world);
                y -= 1;
                if (y<0) {
                    break;
                }
            }
            pos += border.step;
        }
    }
}


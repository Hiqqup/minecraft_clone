//
// Created by ju on 10/31/25.
//

#include "World.h"
#include "Chunk.h"
#define STB_PERLIN_IMPLEMENTATION
#include <stb_perlin.h>

int blockArray3to1d(const int x, const int y,const int z) {
    return x * (Chunk::DIMENSIONS.y * Chunk::DIMENSIONS.z) + y * Chunk::DIMENSIONS.z + z;
}
int heightMapArray2to1d(const int x, const int z) {
    return x *  Chunk::DIMENSIONS.z + z;
}
Block &Chunk::blockAt(glm::ivec3 pos) {
    return blocks[blockArray3to1d(pos.x,pos.y,pos.z)];
}
Chunk::Chunk(const glm::ivec2 & chunkPositionUnscaled):
    chunkPositionOffset ( glm::ivec3(chunkPositionUnscaled.x * DIMENSIONS.x, 0 ,chunkPositionUnscaled.y* DIMENSIONS.z))
{

    for (int x = 0; x < DIMENSIONS.x; x++) {
        for (int z = 0; z < DIMENSIONS.z; z++) {
            constexpr float scale = 0.1;
            float perlin = stb_perlin_noise3(
                static_cast<float>(x+chunkPositionOffset.x)* scale,
                static_cast<float>(z+chunkPositionOffset.z)*scale,
                //0,
                0,0,0,0);
            float perlinNormalized = (perlin + 1.0f ) * 0.5f;
            //perlinNormalized   = 0;
            heightMap[heightMapArray2to1d(x,z)] = 30 +static_cast<int>( perlinNormalized * 20);
        }
    }

    for (int x = 0; x < DIMENSIONS.x; x++) {
        for (int y = 0; y < DIMENSIONS.y; y++) {
            for (int z = 0; z < DIMENSIONS.z; z++) {
                blocks[blockArray3to1d(x,y,z)].setProps(glm::ivec3(x, y, z) + chunkPositionOffset, y > heightMap[heightMapArray2to1d(x,z)]);
            }
        }
    }
    for (int x = 0; x < DIMENSIONS.x; x++) {
        for (int y = 0; y < DIMENSIONS.y; y++) {
            for (int z = 0; z < DIMENSIONS.z; z++) {
                blocks[blockArray3to1d(x,y,z)].generateFaces(data, this);
            }
        }
    }
}

void Chunk::patchUpBorders(World *world, glm::ivec2 chunkIndex) {
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
        if (!world->chunks.contains(chunkIndex + glm::ivec2(border.direction.x,border. direction.z))) {
            continue;
        }

        for (unsigned int i = 0; i < border.length; i++) {
            int y = static_cast<int>(heightMap[heightMapArray2to1d( pos.x,pos.z)]);
            bool propergateDown = true;
            while (propergateDown) {
                propergateDown = blocks[blockArray3to1d(pos.x,y,pos.z)].generateFacesBetweenChunks(
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


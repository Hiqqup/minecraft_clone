//
// Created by ju on 10/31/25.
//

#include "Chunk.h"

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
    for (int x = 0; x < DIMENSIONS.x; x++) {
        for (int y = 0; y < DIMENSIONS.y; y++) {
            for (int z = 0; z < DIMENSIONS.z; z++) {
                blocks[x][y][z].setProps({x, y, z}, y > 30);
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


//
// Created by ju on 11/1/25.
//

#pragma once
#include "ChunkMesh.h"
#include "glm/vec2.hpp"


class ChunkMeshRenderDistance {
    static constexpr glm::uvec2 RENDER_DISTANCE = glm::uvec2(20, 20);
    ChunkMesh chunks[RENDER_DISTANCE.x][RENDER_DISTANCE.y];
};

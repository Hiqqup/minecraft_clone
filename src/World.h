//
// Created by ju on 11/1/25.
//

#pragma once
#include "Camera.h"
#include "ChunkMesh.h"


class World {
    static constexpr glm::ivec2 RENDER_DISTANCE = glm::uvec2(4, 4);
    struct iVec2_hash {
        std::size_t operator()(const glm::ivec2& v) const noexcept {
            // Combine the two integer hashes
            // A simple, effective hash combiner
            std::size_t h1 = std::hash<int>()(v.x);
            std::size_t h2 = std::hash<int>()(v.y);
            return h1 ^ (h2 << 1); // or use a better hash combiner if needed
        }
    };
public:
    std::unordered_map<glm::ivec2, Chunk*, iVec2_hash> chunks;
private:
    std::unordered_map<glm::ivec2, ChunkMesh*, iVec2_hash> meshes;
public:
    World() = default;
    Block* getBlockAt(glm::ivec3 position);
    void draw()const ;
    ~World() ;
    void updatePlayerPositionRenderNewChunks(glm::ivec2 playerPosition);
    void renderNewChunk(glm::ivec2 index);
};


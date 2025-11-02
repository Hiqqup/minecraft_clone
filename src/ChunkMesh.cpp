//
// Created by ju on 10/31/25.
//

#include "ChunkMesh.h"

#include <cstring>
#include <glad/glad.h>

#include "Chunk.h"
#include "glm/detail/func_packing_simd.inl"


template<typename T>
GLuint createBuffer(GLuint bufferType, const std::vector<T> &bufferData) {
    unsigned int buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(bufferType, buffer);
    glBufferData(bufferType, bufferData.size() * sizeof(T), bufferData.data(), GL_STATIC_DRAW);
    return buffer;
}


ChunkMesh::ChunkMesh(const Chunk & chunk):
    VAO(),
    VBO (createBuffer( GL_ARRAY_BUFFER,chunk.data.vertices)),
    EBO ((createBuffer(GL_ELEMENT_ARRAY_BUFFER, chunk.data.indices))),
    numberOfIndices(static_cast<int>(chunk.data.indices.size()))
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void ChunkMesh::draw() const {

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, nullptr);
}

ChunkMesh::~ChunkMesh() {
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

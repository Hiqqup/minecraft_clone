//
// Created by ju on 10/31/25.
//

#include "Mesh.h"

#include <cstring>
#include <random>
#include <bits/fs_fwd.h>
#include <glad/glad.h>

#include "Chunk.h"
#include "glm/vec3.hpp"
#include "glm/detail/func_packing_simd.inl"


template<typename T>
GLuint createBuffer(GLuint bufferType, const std::vector<T> &bufferData) {
    unsigned int buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(bufferType, buffer);
    glBufferData(bufferType, bufferData.size() * sizeof(T), bufferData.data(), GL_STATIC_DRAW);
    return buffer;
}

Chunk chunk;

Mesh::Mesh():
    VBO (createBuffer( GL_ARRAY_BUFFER,chunk.data.vertices)),
    EBO ((createBuffer(GL_ELEMENT_ARRAY_BUFFER, chunk.data.indices))),
    numberOfIndices(chunk.data.indices.size())
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)( 3* sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Mesh::draw() const {

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, nullptr);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

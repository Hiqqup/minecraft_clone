//
// Created by ju on 10/31/25.
//

#pragma once
#include <vector>


class Mesh {


    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    int numberOfIndices;
public:
    Mesh();
    void draw()const;
    ~Mesh();

};

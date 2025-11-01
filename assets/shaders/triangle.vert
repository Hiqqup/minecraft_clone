#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aTexDim;
uniform mat4 mvp;
out vec2 texCoord;
out float texDim;
void main() {
    gl_Position =  mvp *vec4(aPos.xyz, 1.0);
    texCoord = aTexCoord;
    texDim = aTexDim;
}


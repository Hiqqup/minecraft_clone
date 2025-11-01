#version 460 core
out vec4 fragColor;
in vec2 texCoord;
in float texDim;

uniform sampler2D ourTexture;
void main() {
    vec4 textureColor = texture(ourTexture, texCoord);
    fragColor = vec4(textureColor.xyz * texDim, 1.0);
}
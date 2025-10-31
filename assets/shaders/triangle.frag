#version 460 core
out vec4 fragColor;
in vec2 texCoord;

uniform sampler2D ourTexture;
void main() {
    fragColor = texture(ourTexture, texCoord);
    //fragColor = vec4(texCoord, 0.0, 1.0);
}
#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform vec4 ourColor;
uniform sampler2D ourTexture;

void main() {
  FragColor = texture2D(ourTexture, texCoord) * (vertexColor + ourColor);
}
#version 330

attribute vec4 vertex;
attribute vec2 value;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
varying vec2 val;

void main() {
    val = value;
    gl_Position = projectionMatrix * viewMatrix * vertex;
}

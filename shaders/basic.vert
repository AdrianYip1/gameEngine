#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexPos;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 modelM;
uniform mat4 viewM;
uniform mat4 projectionM;;

void main() {
    gl_Position = projectionM * viewM * modelM * vec4(aPos, 1.0);
    TexCoord = vec2(aTexPos.x, aTexPos.y);
}
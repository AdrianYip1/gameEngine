#version 330 core 
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal; 
out vec3 FragPos;

uniform mat4 modelM;
uniform mat4 viewM;
uniform mat4 projectionM;

void main() {
    gl_Position = projectionM * viewM * modelM * vec4(aPos, 1);
    FragPos = vec3(modelM * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(modelM))) * aNormal;    
}
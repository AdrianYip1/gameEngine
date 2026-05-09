#version 330 core 

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;


struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light lights;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;

void main() {
    vec3 result = vec3(0.0);


        vec3 ambient = lights.ambient * vec3(texture(material.diffuse, TexCoords));

        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lights.direction);
        float rawDiff = dot(norm, lightDir);
        float diff = max(rawDiff, 0.0);
        vec3 diffuse = lights.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = rawDiff > 0.0 ? pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) : 0.0;
        vec3 specular = lights.specular * spec * vec3(texture(material.specular, TexCoords));

        result += ambient + diffuse + specular;
    

    FragColor = vec4(result, 1.0);
}
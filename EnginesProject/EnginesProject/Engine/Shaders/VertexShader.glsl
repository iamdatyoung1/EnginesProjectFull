#version 450 core
//This has to be in order
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;


out vec3 Normal;
out vec2 TexCoords;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
//The code below with position can only be in vertex
    gl_Position = projection * view *  model * vec4(position, 1.0f);
	TexCoords = texCoords;
	TexCoords = vec2(texCoords.x, 1.0 - texCoords.y);
	transpose(inverse(model));
	Normal =  mat3(inverse(transpose(model))) * normal;
	FragPos = vec3(model * vec4(position, 1.0));
}
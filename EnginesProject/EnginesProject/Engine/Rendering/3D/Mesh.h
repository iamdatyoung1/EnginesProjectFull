#ifndef MESH_H
#define MESH_H
//acces to all opengl api
#include <glew.h>
//dynamic size array
#include <vector>
//anytime want to acces start with glm/glm the hpp means its a c++ file
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include <iostream>
#include "../../Graphics/MaterialHandler.h"


struct Vertex {
	//you could use using namespace
	glm::vec3 position;
	glm::vec3 normal;
	//has to be vec2
	glm::vec2 textureCoordinates;
	//it will be removed later but for now keep	glm::vec3 colour;

};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector <unsigned int> meshIndices;
	Material material;
};
class Mesh
{
public: 
	//taking in a vector of type vertex
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, std::vector<glm::mat4>& instances_);

private:
	void GenerateBuffers();
	//VAO stands for vertex array object and VBO stands for object buffer
	
	GLuint VAO, VBO;
	SubMesh subMesh;
	GLuint shaderProgram;
	//location
	GLuint modelLoc, viewLoc, projectionLoc, textureLoc;

	GLuint ViewPosition, LightsPosition, LightsAmbient, LightsDiffuse, SpecularVaulue, LightsColourV;
	GLuint diffuseMapLoc, shininessLoc, transparencyLoc, ambientLoc, diffuseLoc, specularLoc;
};
#endif

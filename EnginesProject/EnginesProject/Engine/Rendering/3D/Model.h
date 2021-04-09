#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "LoadOBJModel.h"
class Model
{
public:
	//default of 0
	//one path is for the obj and the other is for the mtl file
	Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_);
	~Model();
	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);
	//we need a getter and setter
	//they have const cause we arnt changing values
	unsigned int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(unsigned int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	glm::mat4 GetTransform(unsigned int index_) const;
	GLuint GetShaderProgram() const;

private:
	glm::mat4 CreateTransform(glm::vec3 position_, float angle, glm::vec3 rotation_, glm::vec3 scale_)const;
	void LoadModel();

	std::vector<Mesh*> meshes;
	GLuint shaderProgram;
	std::vector<glm::mat4> modelInstances;
	LoadOBJModel* obj;
};
#endif

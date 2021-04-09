#include "Mesh.h"
//VBO and VAO has to be 0 cause it cant go higher
// sets to empty vector



Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), shaderProgram(0), modelLoc(0), 
viewLoc(0), projectionLoc(0), textureLoc(0), ViewPosition(0), LightsPosition(0), 
LightsAmbient(0), LightsDiffuse(0), SpecularVaulue(0), LightsColourV(0)
{
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	//deletes the vao and vbo because opengl has its own way of deleteting
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//clearing vertex list
	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}
	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_)
{
	//set uniform variable
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glBindVertexArray(VAO);
	//looking for location
	glEnable(GL_DEPTH_TEST);

	

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	

	glUniform3fv(ViewPosition, 1, glm::value_ptr(camera_->GetPosition()));
	glUniform3fv(LightsPosition, 1, glm::value_ptr(camera_->GetLightsources()[0]->Getposition()));
    //Ask prof about this
	glUniform1f(LightsAmbient, camera_->GetLightsources()[0]->GetambientV());
	glUniform1f(LightsDiffuse, camera_->GetLightsources()[0]->GetdiffuseV());
	glUniform1f(SpecularVaulue, camera_->GetLightsources()[0]->GetspecularV());
	glUniform3fv(LightsColourV, 1, glm::value_ptr(camera_->GetLightsources()[0]->GetLightColour()));
	//setting model matrix 4 by 4
	glUniform3fv(ambientLoc, 1, value_ptr(subMesh.material.ambient));
	glUniform3fv(specularLoc, 1, value_ptr(subMesh.material.specular));
	glUniform3fv(diffuseLoc, 1, value_ptr(subMesh.material.diffuse));
	glUniform1f(shininessLoc, subMesh.material.shininess);
	glUniform1f(transparencyLoc, subMesh.material.transparency);
	glUniform1i(diffuseMapLoc, 0);

	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
}

void Mesh::GenerateBuffers()
{
	//generate our vao and vbo
	//only want to make 1
	//Vbo hold the data and vao splits it up
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	//We are then binding it to array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex),
		&subMesh.vertexList[0], GL_STATIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	//this tells us how its created
	//first part is the position and the second is the size
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//Normal
	//we increase each time
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//Tex Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	//colour
	//bind the buffer rate to zero
	

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//has to match whats in the shader
	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	//Set these uniform locations

	ViewPosition = glGetUniformLocation(shaderProgram, "cameraPosition");
	//std::cout << ViewPosition << std::endl;
	LightsPosition = glGetUniformLocation(shaderProgram, "light.lightPos");
	//std::cout << LightsPosition << std::endl;
	LightsAmbient = glGetUniformLocation(shaderProgram, "light.ambientV");
	//std::cout << LightsAmbient << std::endl;
	LightsDiffuse = glGetUniformLocation(shaderProgram, "light.diffuseV");
	//std::cout << LightsDiffuse << std::endl;
	SpecularVaulue = glGetUniformLocation(shaderProgram, "light.specularV");
//	std::cout << SpecularVaulue << std::endl;
	LightsColourV = glGetUniformLocation(shaderProgram, "light.lightColour");
	//std::cout << LightsColourV << std::endl;

	diffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	shininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	ambientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	diffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	specularLoc = glGetUniformLocation(shaderProgram, "material.specular");

}

#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : currentMaterial(Material())
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(200);

}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();

}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

void LoadOBJModel::PostProccessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;
	
	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannont open OBJ file" + filePath_,
			"LoadObjModel.cpp", __LINE__);
		return;
	}
	std::string line;

	while (std::getline(in, line))
	{
		//Vertex Data
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
		}
		
		//normal data, you will be looking in the sheet for the "VN" which is normal data
		else if (line.substr(0, 3) == "vn ")
		{
			std::stringstream vn(line.substr(3));
			float x, y, z;
			vn >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		

		//texture data "VT" for the texture
     	else if (line.substr(0, 3) == "vt ")
		{
			std::stringstream vn(line.substr(3));
			float x, y;
			vn >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}
		


		//face data "F" is for face dat.  ex 1/1/1 it goes vertex, texture, then normal.
		else if (line.substr(0, 2) == "f ")
		{
			std::stringstream f(line.substr(2));
			unsigned int vertexOne[3], vertexTwo[3], vertexThree[3];
			for (int i = 0; i < 3; i++)
			{
				f >> vertexOne[i];
				vertexOne[i] -= 1;
				f.ignore(1, vertexOne[i]);
			}

			for (int i = 0; i < 3; i++) 
			{
				f >> vertexTwo[i];
				vertexTwo[i] -= 1;
				f.ignore(1, vertexTwo[i]);
			}
			for (int i = 0; i < 3; i++)
			{
				f >> vertexThree[i];
				vertexThree[i] -= 1;
				f.ignore(1, vertexThree[i]);
			}
			indices.push_back(vertexOne[0]); textureIndices.push_back(vertexOne[1]); normalIndices.push_back(vertexOne[2]);
			indices.push_back(vertexTwo[0]); textureIndices.push_back(vertexTwo[1]); normalIndices.push_back(vertexTwo[2]);
			indices.push_back(vertexThree[0]); textureIndices.push_back(vertexThree[1]); normalIndices.push_back(vertexThree[2]);

		}
	
		//New Mesh
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProccessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProccessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
	
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}

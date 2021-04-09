#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader() {

}
void MaterialLoader::LoadMaterial(std::string filePath_) {
	std::ifstream in(filePath_.c_str(),std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open MTL file: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}

	//Cretae new material object.
	Material m = Material();
	std::string matName = "";
	std::string line;
	//Read through file...
	while (getline(in, line))
	{
		//...until it reads "newmtl "
		if (line.substr(0, 7) == "newmtl ")
		{
			//Then check if a material ahs already been created (for mtl files with multiple materials in them) and set up to make a new one if true.
			if (m.diffuseMap != 0)
			{
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			//Run LoadTexture on the texture's name and set return to the material's diffuseMap.
			//Then set the material's name for later use.
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		//Same as above but for diffuse data.
		else if (line.substr(0, 4) == "\tKd ")
		{
			std::stringstream kd(line.substr(4));
			float x, y, z;
			kd >> x >> y >> z;
			m.diffuse =glm::vec3(x, y, z);
		}
		//Specular data.
		else if (line.substr(0, 4) == "\tKs ")
		{
			std::stringstream ks(line.substr(4));
			float x, y, z;
			ks >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
		}
		//Ambient data.
		else if (line.substr(0, 4) == "\tKa ")
		{
		std::stringstream ka(line.substr(4));
			float x, y, z;
			ka >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
		}
		//Transparency data.
		else if (line.substr(0, 3) == "\td ")
		{
			std::stringstream d(line.substr(3));
			float transparency_;
			d >> transparency_;
			m.transparency = transparency_;
		}
		//Shininess data.
		else if (line.substr(0, 2) == "\tNs")
		{
			std::stringstream ns(line.substr(0, 4));
			float shininess_;
			ns >> shininess_;
			m.shininess = shininess_;
		}
	}

	//Add the material to the materials list if nothing went wrong.
	if (m.diffuseMap != 0)
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}

	//Close the file.
	in.close();
	
}

GLuint MaterialLoader::LoadTexture(std::string fileName_) {
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}
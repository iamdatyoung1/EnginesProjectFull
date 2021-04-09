#include "ShaderHandler.h"

std::unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;
std::unordered_map<std::string, GLuint> ShaderHandler::programs = std::unordered_map<std::string, GLuint>();

ShaderHandler::ShaderHandler()
{

}

ShaderHandler::~ShaderHandler()
{
	OnDestroy();
}
ShaderHandler* ShaderHandler::GetInstance()
{
	//Checks shader instance  and will always return pointer
	if (shaderInstance.get() == nullptr) {
		shaderInstance.reset(new ShaderHandler);
	}
	return nullptr;
}

void ShaderHandler::CreateProgram(const std::string& shaderName_, 
	const std::string& vertexShaderFileName_, 
	const std::string& fragmentShaderFileName_)
{
	//We first read files 
	std::string vertexShaderCode = ReadShader(vertexShaderFileName_);
	std::string fragmentShaderCode = ReadShader(fragmentShaderFileName_);

	if (vertexShaderCode == "" || fragmentShaderCode == "") {
		return;
	}
	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, shaderName_);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, shaderName_);

	if (vertexShader == 0 || fragmentShader == 0) {
		return;
	}
	GLint linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	//create link result and attach both frag and vert
	if (!linkResult) {
		GLint infoLogLenght = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLenght);
		std::vector<char> programLog(infoLogLenght);
		glGetProgramInfoLog(program, infoLogLenght, NULL, &programLog[0]);
		std::string programString(programLog.begin(), programLog.end());
		Debug::Error("Failed to link shader" + shaderName_ + ".Error:" + programString, "ShaderHandler.cpp", __LINE__);
		//properly delete memmory when there is a error
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteShader(program);
		return;
	}
	//if nothing has gone wrong
	programs[shaderName_] = program;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

GLuint ShaderHandler::GetShader(const std::string& shaderName_)
{
	//The program will find the shader name and if it is not equal to the programs end then we return the shaderName_
	//iterates through the map and find if the key matches
	//if we cant find the key then return 0;
	if (programs.find(shaderName_) != programs.end()) {
		return programs[shaderName_];
	}
	return 0;
}

void ShaderHandler::OnDestroy()
{
	//We call opengl delete program function for every shader that we create.
	if (programs.size() > 0) {
		for (auto p : programs) {
			glDeleteProgram(p.second);
		}
		programs.clear();
	}
}

std::string ShaderHandler::ReadShader(const std::string& filePath_)
{
	//pass in file that we want to read and then outputs it to a string
	//"Try" means it will try it out and "Catch" means it will try and catch the excepetions 
	//
	std::string shaderCode = "";
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	try {
		file.open(filePath_);
		std::stringstream tmpStream;
		tmpStream << file.rdbuf();
		file.close();
		shaderCode = tmpStream.str();
	}
	//print out to debug and say something went wrong if it did
	catch (std::ifstream::failure error_) {
		Debug::Error("Could not read the shader:" + filePath_, "ShaderHandler.cpp", __LINE__);
       //we have to return something so we return an empty string
		return "";
	}
	return shaderCode;
}

GLuint ShaderHandler::CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_)
{
	//The shader program is made up of multiple shader objects
	//This will create those
	GLint compileResult = 0;
	//This line will create shader
	GLuint shader = glCreateShader(shaderType_);
	const char* shaderCodePtr = source_.c_str();
	const int shaderCodeSize = source_.size();
	//once shader is created we will try to pass in the source of the shader
	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	// This code down here is error checking for compile shader line
	if (!compileResult) {
		GLint infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::string shaderString(shaderLog.begin(), shaderLog.end());
		Debug::Error("Error compiling shader" + shaderName_ + ". Error: \n" + shaderString, "ShaderHandler.cpp", __LINE__);
		return 0;
	}

	return shader;
}

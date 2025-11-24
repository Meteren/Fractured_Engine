#include "ShaderLoader.h"

namespace FRACTURED_RENDERING {

	std::shared_ptr<Shader> ShaderLoader::createShader(const std::string vShaderPath, const std::string fShaderPath)
	{
		int shaderProgram = createShaderProgram(vShaderPath,fShaderPath);

		if (shaderProgram == -1) {
			printf("Program can't be created.\n");
			return nullptr;
		}
		else {
			printf("Program successfully created.");
			return std::make_shared<Shader>(shaderProgram);
		}

	}

	char* ShaderLoader::loadShader(const std::string shaderPath)
	{
		std::fstream file(shaderPath);

		if (!file.is_open()) {
			printf("Can't open file.");
			return nullptr;
		}
			
		std::string line = "";

		std::string content = "";

		while (!file.eof()) {
			getline(file, line);
			content.append(line + "\n");
		}

		file.close();

		char* cBuffer = new char[content.size() + 1];

		std::copy(content.begin(), content.end(), cBuffer);

		cBuffer[content.size()] = '\0';

		printf("%s\n", cBuffer);

		return cBuffer;

	}

	int ShaderLoader::createShaderProgram(const std::string vShaderPath, const std::string fShaderPath)
	{
		char* vShaderContent = loadShader(vShaderPath);

		if (!vShaderContent) {
			printf("Can't read vertex shader.\n");
			return -1;
		}
			
		char* fShaderContent = loadShader(fShaderPath);

		if (!fShaderContent) {
			printf("Can't read fragment shader.\n");
			return -1;
		}		

		int vShader = compileShaderProgram(GL_VERTEX_SHADER,vShaderContent);

		delete[] vShaderContent;

		if (vShader == -1) {
			return -1;
		}

		int fShader = compileShaderProgram(GL_FRAGMENT_SHADER, fShaderContent);

		delete[] fShaderContent;

		if (fShader == -1) {
			return -1;
		}

		int program = glCreateProgram();

		glAttachShader(program, vShader);
		glAttachShader(program, fShader);
		glLinkProgram(program);

		glDetachShader(program, vShader);
		glDetachShader(program, fShader);
		glDeleteShader(vShader);
		glDeleteShader(fShader);

		if (!checkProgramStatus(GL_LINK_STATUS, program))
			return -1;

		glValidateProgram(program);

		if (!checkProgramStatus(GL_VALIDATE_STATUS, program))
			return -1;

		return program;

	}

	int ShaderLoader::compileShaderProgram(GLenum shaderType, const char* shaderContent)
	{
		int shader = glCreateShader(shaderType);

		glShaderSource(shader, 1, &shaderContent, NULL);

		glCompileShader(shader);

		int status;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if (!status) {
			char infoBuffer[512];
			glGetShaderInfoLog(shader,512,NULL,infoBuffer);

			printf("Shader can't be compiled -- Type of: %i -- %s\n", shaderType, infoBuffer);

			return -1;

		}

		return shader;

	}

	bool ShaderLoader::checkProgramStatus(GLenum type, int& program)
	{
		int status;

		glGetProgramiv(program, type, &status);

		if (!status) {
			char infoBuffer[512];
			glGetProgramInfoLog(program, 512, NULL, infoBuffer);
			printf("Error while chekcing program status -- Type of: %i -- %s\n", type, infoBuffer);
			return false;
		}

		return true;
	}

}


#pragma once

#include <glad/glad.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <memory>
#include "Shader.h"


namespace FRACTURED_RENDERING {

	class ShaderLoader
	{
	public:

		ShaderLoader() = delete;

		static std::shared_ptr<Shader> createShader(const std::string vShaderPath, const std::string fShaderPath);


	private:
		static char* loadShader(const std::string shaderPath);

		static int createShaderProgram(const std::string vShaderPath, const std::string fShaderPath);

		static int compileShaderProgram(GLenum shaderType, const char* shaderContent);

		static bool checkProgramStatus(GLenum type, int& program);


	};
}



#pragma once

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace FRACTURED_RENDERING {
	class Shader
	{
	public:

		Shader() : programID(0) {}

		Shader(int programID) : programID{programID}{}

		~Shader(){ 
			if (!programID)
				glDeleteProgram(programID);
		}

		void useShaderProgram() const { glUseProgram(programID); }

		void setFloat(float value) { glUniform1f(programID, value); }

		void setFloat2(const std::string u_name,float value1, float value2){
			int location = glGetUniformLocation(programID, u_name.c_str());
			glUniform2f(location, value1, value2); 
		}

		void setFloat3(const std::string u_name,float value1, float value2, float value3) { 
			int location = glGetUniformLocation(programID, u_name.c_str());
			glUniform3f(location, value1, value2, value3); 
		}

		void setFloat4(const std::string u_name, float value1, float value2, float value3, float value4) { 
			int location = glGetUniformLocation(programID, u_name.c_str());
			glUniform4f(location, value1, value2, value3, value4); 
		}

		void setMatrix4(const std::string u_name,glm::mat4& mat) { 
			int location = glGetUniformLocation(programID, u_name.c_str());
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat)); 
		}

		void setInt1(std::string u_name,int value) {
			int location = glGetUniformLocation(programID, u_name.c_str());
			glUniform1i(location, value);
		}


	private:

		int programID;
	};

}


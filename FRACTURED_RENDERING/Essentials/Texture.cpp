#include "Texture.h"

namespace FRACTURED_RENDERING {

	void Texture::useTexture(GLenum unit)
	{
		//Later, texture can be bind here
		//Also there would be a need to a shader uniform attachment that should be done here later.(etc glUniform1i(loc,value))
		glActiveTexture(unit);
		bind();

	}
	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void Texture::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}



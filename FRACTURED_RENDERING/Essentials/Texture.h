#pragma once

#include <glad/glad.h>
#include <string>


namespace FRACTURED_RENDERING {

	class Texture
	{
	public:

		enum class TextureType {
			PIXEL = 0,BLENDED,NONE
		};

		Texture() : textureID{ 0 }, width{ 0 }, height{ 0 }, texturePath{ "" }, textureType{ TextureType::NONE } {}

		Texture(unsigned int textureID, int width, int height, const std::string& texturePath, TextureType textureType) 
			: textureID{ textureID }, width{ width }, height{ height }, texturePath{ texturePath }, textureType{textureType} {}

		void useTexture(GLenum unit);

		void bind();

		void unbind();

	private:
		unsigned int textureID;
		int width, height;
		TextureType textureType;
		std::string texturePath;

	};
}




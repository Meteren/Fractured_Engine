#include "TextureLoader.h"

namespace FRACTURED_RENDERING {

	std::shared_ptr<Texture> FRACTURED_RENDERING::TextureLoader::createTexture(Texture::TextureType textureType, const std::string& texturePath)
	{
		unsigned int textureID;
		int width, height;

		if (!loadTexture(textureID,width,height,texturePath,textureType)) {
			printf("Something went wrong while loading texture.\n");
			return nullptr;
		}

		return std::make_shared<Texture>(textureID,width,height,texturePath,textureType);
	}

	bool TextureLoader::loadTexture(unsigned int& textureID, int& width, int& height, const std::string& texturePath, Texture::TextureType textureType)
	{
		int channels = 0;

		unsigned char* textureData = SOIL_load_image(texturePath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

		flipTexture(width, height, channels, textureData);

		if (!textureData) {
			printf("Texture couldn't be loaded. \n");
			return false;
		}

		GLenum textureFormat = GL_RGBA;

		switch (channels) {
		case 3:
			textureFormat = GL_RGB;
			break;
		case 4:
			textureFormat = GL_RGBA;
			break;
		}

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		switch (textureType) {
		case Texture::TextureType::BLENDED:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case Texture::TextureType::PIXEL:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE ,textureData);
		glGenerateMipmap(GL_TEXTURE_2D); //Can be unnecessary

		glBindTexture(GL_TEXTURE_2D, 0);

		SOIL_free_image_data(textureData);

		return true;
	}

	void TextureLoader::flipTexture(int width, int height,int channels, unsigned char* textureData)
	{
		int stride = width * channels;

		unsigned char* top;
		unsigned char* bottom;
		unsigned char temp;

		for (int y = 0; y < height / 2; y++) {

			top = textureData + stride * y;
			bottom = textureData + (height - 1 - y) * stride;

			for (int x = 0; x < stride; x++) {

				temp = top[x];
				top[x] = bottom[x];
				bottom[x] = temp;
			}

		}

	}

}


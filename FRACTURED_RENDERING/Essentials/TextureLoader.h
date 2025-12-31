#pragma once

#include <memory>
#include "Texture.h"
#include <string>
#include <stdio.h>
#include <SOIL/SOIL.h>


namespace FRACTURED_RENDERING {

	class TextureLoader {

	public:

		TextureLoader() = delete;

		static std::shared_ptr<Texture> createTexture(Texture::TextureType textureType, const std::string& texturePath);

	private:

		static bool loadTexture(unsigned int& textureID, int& width, int& height, const std::string& texturePath, Texture::TextureType blendType = Texture::TextureType::PIXEL);
		static void flipTexture(int width, int height, int channels, unsigned char* textureData);

	};
}



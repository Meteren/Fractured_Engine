#pragma once

#include <memory>
#include "Texture.h"
#include <SOIL/SOIL.h>
#include <string>
#include <stdio.h>


namespace FRACTURED_RENDERING {

	class TextureLoader {

	public:

		TextureLoader() = delete;

		static std::shared_ptr<Texture> createTexture(Texture::TextureType textureType, const std::string& texturePath);

	private:

		static bool loadTexture(unsigned int& textureID, int& width, int& height, const std::string& texturePath, Texture::TextureType blendType = Texture::TextureType::PIXEL);

	};
}



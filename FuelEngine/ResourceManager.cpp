#include "FuelEnginePCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>


void fuel::ResourceManager::IInit(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<fuel::Texture2D> fuel::ResourceManager::ILoadTexture(const std::string& file) const
{
	const auto fullPath = m_DataPath + "Sprites/" + file;
	auto texture = IMG_LoadTexture(Renderer::GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<fuel::Font> fuel::ResourceManager::ILoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + "Fonts/", file, size);
}

bool fuel::ResourceManager::IDoesFileExist(const std::string& filePath)
{
	if (filePath != "")
	{
		return std::experimental::filesystem::exists(m_DataPath + filePath);
	}
	return false;
}

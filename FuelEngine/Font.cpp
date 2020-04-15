#include "FuelEnginePCH.h"
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* fuel::Font::GetFont() const {
	return m_Font;
}

fuel::Font::Font(const std::string& dataPath, const std::string& fontName, unsigned int size) : m_Font(nullptr), m_FontName(fontName), m_Size(size)
{
	const std::string fullPath{ dataPath + fontName };
	m_Font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_Font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

fuel::Font::~Font()
{
	TTF_CloseFont(m_Font);
}

const std::string& fuel::Font::GetName() const
{
	return m_FontName;
}

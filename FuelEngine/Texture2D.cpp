#include "FuelEnginePCH.h"
#include "Texture2D.h"
#include <SDL.h>

fuel::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* fuel::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

fuel::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}

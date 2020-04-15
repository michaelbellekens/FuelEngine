#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace fuel
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		static void Init(SDL_Window* window) { GetInstance().IInit(window); }
		static void Render() { GetInstance().IRender(); }
		static void Destroy() { GetInstance().IDestroy(); }

		static void RenderTexture(const Texture2D& texture, float x, float y) { GetInstance().IRenderTexture(texture, x, y); }
		static void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) { GetInstance().IRenderTexture(texture, x, y, width, height); }

		static SDL_Renderer* GetSDLRenderer() { return GetInstance().IGetSDLRenderer(); }
	private:
		void IInit(SDL_Window* window);
		void IRender() const;
		void IDestroy();

		void IRenderTexture(const Texture2D& texture, float x, float y) const;
		void IRenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* IGetSDLRenderer() const { return m_Renderer; }
		
		SDL_Renderer* m_Renderer{};
	};
}


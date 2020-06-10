#include "FuelEnginePCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "Editor.h"
#include "EngineSettings.h"

void fuel::Renderer::IInit(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	ImGui::CreateContext();
	ImGuiSDL::Initialize(m_Renderer, EngineSettings::GetWindowWidth(), EngineSettings::GetWindowHeight());
	Editor::Initialize();
}

void fuel::Renderer::IRender() const
{
#ifdef RunEditor
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::NewFrame();
#endif
	
	SDL_RenderClear(m_Renderer);
	SceneManager::Render();

#ifdef RunEditor
	Editor::DrawEditor();
	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
#endif
	
	SDL_RenderPresent(m_Renderer);
}

void fuel::Renderer::IDestroy()
{	
	if (m_Renderer != nullptr)
	{
		ImGuiSDL::Deinitialize();
		
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;

		ImGui::DestroyContext();
	}
}

void fuel::Renderer::IRenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void fuel::Renderer::IRenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void fuel::Renderer::IRenderSprite(const Texture2D& texture, const SDL_Rect& destRect, const SDL_Rect& srcRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &destRect);
}

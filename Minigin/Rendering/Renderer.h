#pragma once
#include <SDL.h>
#include "../Engine/DesignPatterns/Singleton.h"


namespace dae
{
	class CameraComponent;
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer> {
		SDL_Renderer*    m_renderer{};
		SDL_Window*      m_window{};
		SDL_Color        m_clearColor{};
		CameraComponent* m_pCurrentCamera{nullptr};

	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, double angle, bool isUI) const;
		void RenderTexture(const Texture2D& texture, float x, float y, double angle, const SDL_Rect* sourceRect, bool isUI) const;
		void RenderTexture(const Texture2D& texture, float x, float y, double angle, float width, float height, bool isUI) const;
		void RenderTexture(const Texture2D& texture, float x, float y, double angle, float width, float height, const SDL_Rect* sourceRect, bool isUI) const;
		void SetCamera(CameraComponent* cam);
		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void             SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

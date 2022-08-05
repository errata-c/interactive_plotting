#pragma once
#include <memory>
#include <iplot/Types.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>



namespace iplot {
	class Renderer {
	public:
		Renderer();
		~Renderer();
		//Renderer(Renderer&& other) noexcept;

		ivec2 getViewport();
		void setViewport(const ivec2 & _view);

		void testDraw(sf::RenderWindow & window);
	private:
		// The current viewport, and the reserved texture memory.
		// The texture reserve is to make it possible to resize the window quickly without tons of unneeded allocs.
		ivec2 mviewport, mreserve;

		sf::Texture mtexture;
		sf::Sprite msprite;

		std::unique_ptr<char[]> pixels;
	};
}
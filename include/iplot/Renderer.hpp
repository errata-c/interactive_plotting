#pragma once
#include <memory>
#include <iplot/Types.hpp>
#include <iplot/Document.hpp>

#include <ez/BitFlags.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class BLContext;

namespace iplot {
	enum class GridHighlight {
		Horizontal = 0,
		Vertical = 1,
		_None = 0,
		_All = 3,
		_Count = 2,
		_EnableOperators
	};
	using GridHighlights = ez::BitFlags<GridHighlight>;

	class Renderer {
	public:
		Renderer();
		~Renderer();
		//Renderer(Renderer&& other) noexcept;

		ivec2 getViewport();
		void setViewport(const ivec2 & _view);

		void drawGrid(BLContext & ctx, const Document& doc, const GridHighlights & hl);
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
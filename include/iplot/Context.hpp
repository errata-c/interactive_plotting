#pragma once
#include <iplot/Types.hpp>
#include <iplot/Renderer.hpp>
#include <iplot/Document.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

namespace iplot {
	class Context {
	public:
		Context(int w, int h);
		~Context();

		int run();

	private:
		Document mdoc;
		ivec2 mviewport;

		path mfilepath;

		sf::RenderWindow mwindow;

		Renderer mrenderer;
	};
}
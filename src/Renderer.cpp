#include <iplot/Renderer.hpp>

#include <blend2d.h>

namespace iplot {
	Renderer::Renderer()
		: mviewport(0, 0)
		, mreserve(0, 0)
	{}
	Renderer::~Renderer()
	{}

	ivec2 Renderer::getViewport() {
		return mviewport;
	}
	void Renderer::setViewport(const ivec2& _view) {
		// Make sure we don't do anything stupid.
		if (_view.x == 0 || _view.y == 0) {
			return;
		}

		if (mreserve.x == 0 || mreserve.y == 0) {
			// Initialize the texture memory.
			if (!mtexture.create(_view.x, _view.y)) {
				assert(false);
			}
			pixels.reset(new char[_view.x * _view.y * 4]);

			mviewport = _view;
			mreserve = mviewport;
		}
		else if (_view.x > mreserve.x || _view.y > mreserve.y) {
			// Update the reserve storage.
			// Multiply the mreserve size by 1.5, if the new size is too small just pick the desired size directly.
			ivec2 cap = mreserve;
			if (_view.x > mreserve.x) {
				cap.x = std::max(double(_view.x), cap.x * 1.5);
			}
			if (_view.y > mreserve.y) {
				cap.y = std::max(double(_view.y), cap.y * 1.5);
			}

			if (!mtexture.create(cap.x, cap.y)) {
				assert(false);
			}
			pixels.reset(new char[cap.x * cap.y * 4]);

			mviewport = _view;
			mreserve = cap;
		}
		else {
			// No reallocations needed.
			mviewport = _view;
		}

		msprite.setTexture(mtexture);
		msprite.setTextureRect(sf::IntRect(0, 0, mviewport.x, mviewport.y));
	}

	void Renderer::drawGrid(BLContext& ctx, const Document& doc, const GridHighlights& hl) {
		if (mviewport.x == 0 || mviewport.y == 0) {
			return;
		}

		struct GDelta {
			double delta;
			int count;
		};

		auto calcDelta = [](double zoom) -> GDelta {
			const double ln10 = 2.30258509299;

			double base = std::log10(zoom);
			double factor = std::floor(base);
			double fract = base - factor;
			double mult = std::exp(factor * ln10);

			const double p1 = 0.176091259056;
			const double p2 = 0.54406804435;
			const double p3 = 0.875061263392;

			if (fract < p1) {
				// 0.2
				return { mult * 0.2, 4 };
			}
			else if (fract < p2) {
				// 0.5
				return { mult * 0.5, 5 };
			}
			else if (fract < p3) {
				// 1
				return { mult, 5 };
			}
			else {
				// 2
				return { mult * 2.0, 4 };
			}
		};

		GDelta xdelta, ydelta;
		xdelta = calcDelta(doc.zoom.x);
		ydelta = calcDelta(doc.zoom.y);

		vec2 origin = -doc.pan;

		// Draw the center lines if the origin x or y is within the render region
		if (std::abs(origin.x) < doc.zoom.x) {

		}
		if (std::abs(origin.y) < doc.zoom.y) {

		}

		// Draw the subgrid first
		// Calculate where the first line will go, then draw all the middle lines one by one. 
		

		// Draw the primary grid


		
		BLPath path;

	}

	void Renderer::testDraw(sf::RenderWindow& window) {
		// Early return, no render needed.
		if (mviewport.x == 0 || mviewport.y == 0) {
			return;
		}

		/// Blend2D is SO much easier than skia, skia docs are absolute garbage.

		BLResult result;
		BLImage img;
		result = img.createFromData(mviewport.x, mviewport.y, BL_FORMAT_PRGB32, pixels.get(), mviewport.x * 4);
		assert(result == BL_SUCCESS);

		BLContext ctx(img);

		// Clear the image.
		ctx.setCompOp(BL_COMP_OP_SRC_COPY);
		ctx.fillAll();

		// Fill some path.
		BLPath path;
		path.moveTo(26, 31);
		path.cubicTo(642, 132, 587, -136, 25, 464);
		path.cubicTo(882, 404, 144, 267, 27, 31);

		ctx.setCompOp(BL_COMP_OP_SRC_OVER);
		ctx.setFillStyle(BLRgba32(0xFFFFFFFF));
		ctx.fillPath(path);

		// Detach the rendering context from `img`.
		ctx.end();

		mtexture.update((const sf::Uint8*)pixels.get(), mviewport.x, mviewport.y, 0, 0);
		window.draw(msprite);
	}
}
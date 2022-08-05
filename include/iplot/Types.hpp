#pragma once
#include <ez/geo/MMRect.hpp>
#include <filesystem>

namespace iplot {
	using rect2 = ez::MMRect<float, 2>;
	using irect2 = ez::MMRect<int, 2>;
	using vec2 = glm::vec2;
	using ivec2 = glm::ivec2;

	using path = std::filesystem::path;
}
cmake_minimum_required(VERSION 3.20)

project(INTERACTIVE_PLOTTING
VERSION 0.1.0
LANGUAGES C CXX)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(GLEW REQUIRED)

find_package(blend2d CONFIG REQUIRED)

find_package(ez-bitflags CONFIG REQUIRED)
find_package(ez-math CONFIG REQUIRED)
find_package(ez-geo CONFIG REQUIRED)


add_library(iplot STATIC
	"src/Context.cpp"
	"src/Renderer.cpp"
)
target_compile_features(iplot PUBLIC cxx_std_17)
target_include_directories(iplot PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/include"
)
target_link_libraries(iplot PUBLIC
	imgui::imgui
	ImGui-SFML::ImGui-SFML
	sfml-system
	sfml-window
	sfml-graphics
	GLEW::GLEW
	
	blend2d::blend2d

	ez::math
	ez::geo
	ez::bitflags
)

add_executable(test_exe
	"test/test.cpp"
)
target_link_libraries(test_exe 
PRIVATE 
	iplot
)

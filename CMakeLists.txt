cmake_minimum_required(VERSION 3.20)

project(INTERACTIVE_PLOTTING
VERSION 0.1.0
LANGUAGES C CXX)

find_package(SFML COMPONENTS system window CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(GLEW REQUIRED)

add_executable(test_exe
"test/test.cpp"
)
target_compile_features(test_exe PRIVATE cxx_std_17)
target_link_libraries(test_exe 
PRIVATE 
	imgui::imgui
	ImGui-SFML::ImGui-SFML
	sfml-system
	sfml-window
	GLEW::GLEW
)

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <GL/glew.h>

#include "imgui.h"
#include "imgui-SFML.h"

#include <thread>

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 600), "ImGui + SFML = <3");
    window.setFramerateLimit(60);


    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }


    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        ImGui::SetNextWindowPos({ 0,0 });
        ImGui::Begin("Hello, world!", 0, 
            ImGuiWindowFlags_::ImGuiWindowFlags_NoMove
            //ImGuiWindowFlags_::ImGuiW
        );
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        glClearColor(247 / 255.f, 250 / 255.f, 255 / 255.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ImGui::SFML::Render(window);
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    ImGui::SFML::Shutdown();

	return 0;
}
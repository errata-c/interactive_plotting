#include <iplot/Context.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <GL/glew.h>

#include "imgui.h"
#include "imgui-SFML.h"

#include <thread>

namespace iplot {
	Context::Context(int w, int h) 
        : mdoc{
            vec2(1.f, 1.f),
            vec2(0.f, 0.f)
          }
		, mviewport(w, h)
	{
		// Filepath needs to be initialized by the user in some way.
		// But we can initialize the window
		mwindow.create(sf::VideoMode(w, h), "iplot", 7u, sf::ContextSettings(8, 8, 0, 4, 5));
		mwindow.setVerticalSyncEnabled(true);

        auto size = mwindow.getViewport(mwindow.getView());
        mviewport = { size.width, size.height };
        mrenderer.setViewport(mviewport);
	}
	Context::~Context() {
		
	}

	int Context::run() {
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            /* Problem: glewInit failed, something is seriously wrong. */
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        }

        ImGui::SFML::Init(mwindow);

        sf::Clock deltaClock;
        while (mwindow.isOpen()) {
            sf::Event event;
            while (mwindow.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(mwindow, event);

                if (event.type == sf::Event::Closed) {
                    mwindow.close();
                }
                else if (event.type == sf::Event::Resized) {
                    auto size = mwindow.getViewport(mwindow.getView());
                    mviewport = {size.width, size.height};
                    mrenderer.setViewport(mviewport);
                }
            }

            ImGui::SFML::Update(mwindow, deltaClock.restart());

            ImGui::ShowDemoWindow();

            ImGui::SetNextWindowPos({ -1,0 });
            ImGui::SetNextWindowSize(ImVec2(256, mviewport.y+1), ImGuiCond_Always);
            if (ImGui::Begin("Context", 0,
                ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings |
                ImGuiWindowFlags_::ImGuiWindowFlags_NoResize
            )) {
                ImGui::Button("Look at this pretty button");
            }
            ImGui::End();

            mwindow.clear();
            // Draw things here:
            mrenderer.testDraw(mwindow);

            // Draw the imgui stuff here:
            ImGui::SFML::Render(mwindow);
            
            // Display the window.
            mwindow.display();

            //std::this_thread::sleep_for(std::chrono::milliseconds(8));
        }

        ImGui::SFML::Shutdown();

		return 0;
	}
}
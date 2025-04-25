//
// Created by Vlad on 4/25/2025.
//
#include "window_manager.hpp"

#include <stdexcept>
#include <Windows.h>
#include "GL/glew.h"
#include "gl/GL.h"
#include "SDL3/SDL.h"
#include "core/shader_program.hpp"

namespace rose_engine
{
    window_manager::window_manager() : m_sdl_window(nullptr), m_gl_context(nullptr), m_opened(true)
    {
        m_sdl_window = SDL_CreateWindow("RoseEngine", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

        m_gl_context = SDL_GL_CreateContext(m_sdl_window);

        if (glewInit() != GLEW_OK)
            throw std::runtime_error("Failed to init GLEW");
    }

    void window_manager::run()
    {
        SDL_GL_MakeCurrent(m_sdl_window, m_gl_context);




        const auto shader = shader_program("shaders/wireframe");


        while (m_opened)
        {
            SDL_Event ev;

            while (SDL_PollEvent(&ev))
                process_event(ev);


            int w, h;

            SDL_GetWindowSizeInPixels(m_sdl_window, &w, &h);
            glViewport(0, 0, w, h);
            glClearColor(0.f, 0.f, 0.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);

            SDL_GL_SwapWindow(m_sdl_window);
        }
    }

    void window_manager::process_events()
    {
        SDL_Event ev;

        while (SDL_PollEvent(&ev))
            process_event(ev);
    }

    void window_manager::process_event(SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
                m_opened = false;
                break;

            default:
                break;
        }
    }

}

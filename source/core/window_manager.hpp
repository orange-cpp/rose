//
// Created by Vlad on 4/25/2025.
//

#pragma once
struct SDL_Window;
struct SDL_GLContextState;
union SDL_Event;

namespace rose_engine
{
    class window_manager
    {
    public:
        explicit window_manager();

        void run();

    private:
        void process_events();

        void process_event(SDL_Event& event);

        SDL_Window* m_sdl_window;
        SDL_GLContextState* m_gl_context;
        bool m_opened;
    };
}

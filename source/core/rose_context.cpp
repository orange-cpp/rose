//
// Created by Vlad on 4/25/2025.
//
#include "rose_context.hpp"

#include <GL/glew.h>
#include <SDL3/SDL.h>

namespace rose_engine
{
    rose_context::rose_context()
    {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    }

    rose_context& rose_context::get_instance()
    {
        static rose_context ctx;

        return ctx;
    }

    rose_context::~rose_context()
    {
        SDL_Quit();
    }
}

//
// Created by Vlad on 4/25/2025.
//
#include "window_manager.hpp"

#include <print>
#include <stdexcept>
#include <Windows.h>
#include <GL/glew.h>
#include <gl/GL.h>
#include <SDL3/SDL.h>

#include "omath/engines/opengl_engine/formulas.hpp"
#include "omath/engines/source_engine/camera.hpp"
#include "omath/engines/source_engine/formulas.hpp"
#include "opengl/gl_program.hpp"
#include "opengl/gl_shader.hpp"

std::vector<omath::Vector3<float>> vertices = {
    {-1,-1,-1},{ 1,-1,-1},{ 1, 1,-1}, {-1,-1,-1},{ 1, 1,-1},{-1, 1,-1},
    {-1,-1, 1},{ 1,-1, 1},{ 1, 1, 1}, {-1,-1, 1},{ 1, 1, 1},{-1, 1, 1},
    {-1,-1,-1},{-1, 1,-1},{-1, 1, 1}, {-1,-1,-1},{-1, 1, 1},{-1,-1, 1},
    { 1,-1,-1},{ 1, 1,-1},{ 1, 1, 1}, { 1,-1,-1},{ 1, 1, 1},{ 1,-1, 1},
    {-1,-1,-1},{-1,-1, 1},{ 1,-1, 1}, {-1,-1,-1},{ 1,-1, 1},{ 1,-1,-1},
    {-1, 1,-1},{-1, 1, 1},{ 1, 1, 1}, {-1, 1,-1},{ 1, 1, 1},{ 1, 1,-1}
};

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


        auto program = opengl::program
        {
            opengl::shader{"shaders/wireframe.vert", GL_VERTEX_SHADER},
            opengl::shader{"shaders/wireframe.frag", GL_FRAGMENT_SHADER}
        };


        omath::source_engine::Camera camera({-10, 0, 0}, {}, {800, 600}, omath::projection::FieldOfView::from_degrees(90.f), 0.01, 1000);

        GLuint vao, vbo;
        glGenVertexArrays(1,&vao);
        glGenBuffers(1,&vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     vertices.size()*sizeof(omath::Vector3<float>),
                     vertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(omath::Vector3<float>),(void*)0);
        glBindVertexArray(0);


        while (m_opened)
        {
            SDL_Event ev;

            constexpr float speed = 0.1;
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
            {
                auto vec = omath::source_engine::right_vector(camera.get_view_angles());
                std::println("Right {} {} {}", vec.x, vec.y, vec.z);
                camera.set_origin(camera.get_origin() + vec * speed);
            }

            if (GetAsyncKeyState(VK_LEFT) & 0x8000)
                camera.set_origin(camera.get_origin() + -omath::source_engine::right_vector(camera.get_view_angles()) * speed);

            if (GetAsyncKeyState(VK_UP) & 0x8000)
                camera.set_origin(camera.get_origin() + omath::source_engine::forward_vector(camera.get_view_angles()) * speed);

            if (GetAsyncKeyState(VK_DOWN) & 0x8000)
                camera.set_origin(camera.get_origin() + -omath::source_engine::forward_vector(camera.get_view_angles()) * speed);

            if (GetAsyncKeyState(VK_SPACE) & 0x8000)
                camera.set_origin(camera.get_origin() + omath::source_engine::k_abs_up * speed);

            if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
                camera.set_origin(camera.get_origin() + -omath::source_engine::k_abs_up* speed);

            if (GetAsyncKeyState('W') & 0x8000)
            {
                auto angles = camera.get_view_angles();
                angles.pitch -= omath::source_engine::PitchAngle::from_degrees(1);
                camera.set_view_angles(angles);
            }

            if (GetAsyncKeyState('S') & 0x8000)
            {
                auto angles = camera.get_view_angles();
                angles.pitch += omath::source_engine::PitchAngle::from_degrees(1);
                camera.set_view_angles(angles);
            }

            if (GetAsyncKeyState('A') & 0x8000)
            {
                auto angles = camera.get_view_angles();
                angles.yaw += omath::source_engine::YawAngle::from_degrees(1);
                camera.set_view_angles(angles);
            }

            if (GetAsyncKeyState('D') & 0x8000)
            {
                auto angles = camera.get_view_angles();
                angles.yaw -= omath::source_engine::YawAngle::from_degrees(1);
                camera.set_view_angles(angles);
            }
            if (GetAsyncKeyState('R') & 0x8000)
            {
                auto angles = camera.get_view_angles();
                angles.roll += omath::source_engine::RollAngle::from_degrees(1);
                camera.set_view_angles(angles);
            }
            if (GetAsyncKeyState('Q') & 0x8000)
            {
                auto angles = camera.get_view_angles();
                angles.roll -= omath::opengl_engine::RollAngle::from_degrees(1);
                camera.set_view_angles(angles);
            }
            while (SDL_PollEvent(&ev))
                process_event(ev);


            int w,h;
            SDL_GetWindowSizeInPixels(m_sdl_window,&w, &h);
            camera.set_view_port({static_cast<float>(w), static_cast<float>(h)});
            glViewport(0, 0, w, h);
            glClearColor(0.f, 0.f, 0.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);

            auto x = camera.get_view_projection_matrix().transposed();
            program.pass_mat_to_uniform("uMVP", x);
            program.pass_vec_to_uniform("uColor", {1.f, 1.f, 1.f});
            program.use();
            glBindVertexArray(vao);

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // <-- key line
            glLineWidth(1.5f);
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // restore if you draw other objects


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

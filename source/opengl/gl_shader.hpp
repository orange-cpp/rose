//
// Created by Vlad on 4/25/2025.
//

#pragma once
#include <string>
#include <GL/glew.h>


namespace rose_engine::opengl
{
    class shader
    {
    public:
        explicit shader(const std::string& path, GLenum type);
        shader(shader& other) = delete;
        shader(shader&& other) noexcept;

        [[nodiscard]]
        GLint get_handle() const;
        ~shader();
    private:
        GLint m_shader_handle;
    };
}

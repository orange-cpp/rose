//
// Created by Vlad on 4/25/2025.
//
#include "gl_shader.hpp"
#include <filesystem>
#include <fstream>


namespace rose_engine::opengl
{
    shader::shader(const std::string& path, const GLenum type) : m_shader_handle(0)
    {
        std::ifstream shader_file(path);
        std::string shader_source_code;

        shader_source_code.resize(std::filesystem::file_size(path));
        shader_file.read(shader_source_code.data(), static_cast<std::streamsize>(shader_source_code.size()));

        const GLuint shader_handle = glCreateShader(type);

        const auto ptr = shader_source_code.c_str();
        glShaderSource(shader_handle, 1, &ptr, nullptr);
        glCompileShader(shader_handle);

        GLint status;
        glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &status);

        if (!status)
            throw std::runtime_error("Failed to compile shader");

        m_shader_handle = shader_handle;

    }

    shader::shader(shader&& other) noexcept
    {
        m_shader_handle = std::move(other.m_shader_handle);
    }

    GLint shader::get_handle() const
    {
        return m_shader_handle;
    }

    shader::~shader()
    {
        if (m_shader_handle)
            glDeleteShader(m_shader_handle);
    }
}

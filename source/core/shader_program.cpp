//
// Created by Vlad on 4/25/2025.
//
#include "shader_program.hpp"
#include <fstream>
#include <filesystem>
#include <GL/glew.h>
#include <GL/GL.h>

namespace rose_engine
{
    shader_program::shader_program(const std::string& path) : m_prog_handle(0)
    {
        const auto vertex_shader = compile_shader_from_file(path+".vert", GL_VERTEX_SHADER);
        const auto frag_shader = compile_shader_from_file(path+".frag", GL_FRAGMENT_SHADER);

        if (!frag_shader || !vertex_shader)
            throw std::runtime_error("Failed to compile shaders");

        const GLuint id = glCreateProgram();
        glAttachShader(id, vertex_shader.value());
        glAttachShader(id, frag_shader.value());
        glLinkProgram(id);

        GLint success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);

        if (!success)
            throw std::runtime_error("Failed to create program");



        glDeleteShader(vertex_shader.value());
        glDeleteShader(frag_shader.value());
    }

    void shader_program::use()
    {
        glUseProgram(m_prog_handle);
    }

    std::optional<GLuint> shader_program::compile_shader_from_file(const std::string& path, const GLenum type)
    {
        std::ifstream shader_file(path);
        std::string shader_source_code;

        shader_source_code.resize(std::filesystem::file_size(path));
        shader_file.read(shader_source_code.data(), static_cast<std::streamsize>(shader_source_code.size()));

        GLuint shader = glCreateShader(type);

        const auto ptr = shader_source_code.c_str();
        glShaderSource(shader, 1, &ptr, nullptr);
        glCompileShader(shader);

        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if (!status)
            return std::nullopt;

        return shader;
    }
}

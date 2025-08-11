//
// Created by Vlad on 4/25/2025.
//
#include "gl_program.hpp"

#include <stdexcept>

#include "omath/engines/source_engine/constants.hpp"

namespace rose_engine::opengl
{
    program::program(const std::initializer_list<shader>& shaders)
    {
        m_prog_handle = glCreateProgram();

        for (const auto& shader: shaders)
            glAttachShader(m_prog_handle, shader.get_handle());

        glLinkProgram(m_prog_handle);

        GLint success;
        glGetProgramiv(m_prog_handle, GL_LINK_STATUS, &success);

        if (!success)
            throw std::runtime_error("Failed to create program");
    }

    void program::use() const
    {
        glUseProgram(m_prog_handle);
    }

    void program::pass_mat_to_uniform(const std::string_view& name, const omath::source_engine::Mat4X4& mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_prog_handle, name.data()), 1, GL_FALSE, mat.raw_array().data());
    }

    void program::pass_vec_to_uniform(const std::string_view& name, const omath::Vector3<float>& mat)
    {
        glUniform3f(glGetUniformLocation(m_prog_handle, name.data()), mat.x, mat.y, mat.z);
    }

    program::~program()
    {
        glDeleteProgram(m_prog_handle);
    }
}

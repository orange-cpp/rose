//
// Created by Vlad on 4/25/2025.
//

#pragma once
#include <string>
#include <GL/glew.h>
#include "gl_shader.hpp"
#include <omath/mat.hpp>

#include "omath/engines/opengl_engine/camera.hpp"
#include "omath/engines/source_engine/constants.hpp"


namespace rose_engine::opengl
{
    class program
    {
    public:
        explicit program(const std::initializer_list<shader>& shaders);
        void use() const;
        void pass_mat_to_uniform(const std::string_view& name, const omath::source_engine::Mat4X4& mat);
        void pass_vec_to_uniform(const std::string_view& name, const omath::Vector3<float>& mat);
        ~program();
    private:
        GLuint m_prog_handle;
    };
}

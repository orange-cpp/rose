//
// Created by Vlad on 4/25/2025.
//

#pragma once
#include <string>
#include <optional>
#include <GL/glew.h>


namespace rose_engine
{
    class shader_program
    {
    public:
        explicit shader_program(const std::string& path);
        void use();
        void set_mat_by_uniforml(const std::string_view& name,)
    private:
        [[nodiscard]]
        static std::optional<GLuint> compile_shader_from_file(const std::string& path, GLenum type);
        GLuint m_prog_handle;
    };
}

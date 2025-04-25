//
// Created by Vlad on 4/25/2025.
//

#pragma once
#include "utility/singleton.hpp"

namespace rose_engine
{
    class rose_context : public utility::singleton<rose_context>
    {
    public:
        explicit rose_context();
        static rose_context& get_instance();
        ~rose_context();
    };
}
//
// Created by Vlad on 4/25/2025.
//

#pragma once
#include <stdexcept>
#include <format>
#include <source_location>

namespace rose_engine::utility
{
    template<class type>
    class singleton
    {
    protected:
        singleton() = default;

    public:
        singleton(const singleton&) = delete;

        singleton& operator=(const singleton&) = delete;

        static type& get_instance()
        {
            throw std::runtime_error(std::format("{} not implemented!", std::source_location::current().function_name()));
        };
    };
}

#include <cstdlib>
#include <print>

#include "core/rose_context.hpp"
#include "core/window_manager.hpp"


[[nodiscard]]
int main()
{
    // Initializing engine context
    rose_engine::rose_context::get_instance();
    rose_engine::window_manager windowManager;

    windowManager.run();

    return EXIT_SUCCESS;
}

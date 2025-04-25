cmake_minimum_required(VERSION 3.25)

option(ROSE_ENGINE_USE_VCPKG "Use vcpkg for building project" ON)


if (ROSE_ENGINE_USE_VCPKG)
    include(cmake/vcpkg.cmake)

    vcpkg_install_if_not_found(sdl3 glew)
endif ()

project(rose_engine LANGUAGES CXX)
add_executable(rose_engine source/main.cpp)

set_target_properties(rose_engine PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}"
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON)


target_include_directories(rose_engine PRIVATE source)

add_subdirectory(source)
add_subdirectory(extlibs/omath)

if (ROSE_ENGINE_USE_VCPKG)
    find_package(SDL3 CONFIG REQUIRED)
    find_package(GLEW REQUIRED)

    target_link_libraries(rose_engine PRIVATE SDL3::SDL3 opengl32 GLEW::GLEW omath::omath)
endif ()
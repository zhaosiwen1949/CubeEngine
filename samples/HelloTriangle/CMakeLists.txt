cmake_minimum_required(VERSION 3.15)
project(HelloTriangle CXX C)

add_executable(HelloTriangle "")

set_property(TARGET HelloTriangle PROPERTY CXX_STANDARD 20)
set_property(TARGET HelloTriangle PROPERTY CXX_STANDARD_REQUIRED ON)

target_sources(HelloTriangle
        PRIVATE
            src/main.cpp
        )

target_include_directories(HelloTriangle
        PRIVATE
            ../../deps/src/vulkan/include
            ../../deps/src/imgui
            ../../deps/src/ImGuizmo
        )

target_link_libraries(HelloTriangle
        PRIVATE
            ImGuizmo
            framework
            scene
            utils
        )

cmake_minimum_required(VERSION 3.15)
project(SceneGraph CXX C)

add_executable(SceneGraph "")

set_property(TARGET SceneGraph PROPERTY CXX_STANDARD 20)
set_property(TARGET SceneGraph PROPERTY CXX_STANDARD_REQUIRED ON)

target_sources(SceneGraph
        PRIVATE
            src/main.cpp
        )

target_include_directories(SceneGraph
        PRIVATE
            ../../deps/src/vulkan/include
            ../../deps/src/imgui
            ../../deps/src/ImGuizmo
        )

target_link_libraries(SceneGraph
        PRIVATE
            ImGuizmo
            framework
            scene
            utils
        )

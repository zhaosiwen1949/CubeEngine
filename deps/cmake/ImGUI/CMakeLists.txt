cmake_minimum_required(VERSION 3.0)

project("ImGUI")

file(GLOB SRC
        ../../src/imgui/*.h
        ../../src/imgui/*.cpp
        )

include_directories(../../src/imgui)

add_library(ImGUI ${SRC})

set_property(TARGET ImGUI PROPERTY FOLDER "ThirdPartyLibraries")
cmake_minimum_required(VERSION 3.15)
project(LargeScene CXX)

add_executable(LargeScene "")

set_property(TARGET LargeScene PROPERTY CXX_STANDARD 20)
set_property(TARGET LargeScene PROPERTY CXX_STANDARD_REQUIRED ON)

target_sources(LargeScene
		PRIVATE
			src/main.cpp
		)

target_include_directories(LargeScene
		PRIVATE
			../../deps/src/vulkan/include
			../../deps/src/imgui
		)

target_link_libraries(LargeScene
		PRIVATE
			framework
			scene
			utils
		)

if(BUILD_WITH_EASY_PROFILER)
	target_link_libraries(LargeScene PRIVATE easy_profiler)
endif()

if(BUILD_WITH_OPTICK)
	target_link_libraries(LargeScene PRIVATE OptickCore)
endif()

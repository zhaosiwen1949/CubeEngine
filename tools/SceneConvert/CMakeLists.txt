cmake_minimum_required(VERSION 3.15)
project(SceneCovert CXX C)

add_executable(SceneCovert "")

set_property(TARGET SceneCovert PROPERTY CXX_STANDARD 20)
set_property(TARGET SceneCovert PROPERTY CXX_STANDARD_REQUIRED ON)

target_sources(SceneCovert
		PRIVATE
			src/main.cpp
		)

target_include_directories(SceneCovert
		PRIVATE
			../../deps/src/vulkan/include
			../../deps/src/imgui
		)

target_link_libraries(SceneCovert
		PRIVATE
			meshoptimizer
			framework
			scene
			utils
		)

target_link_libraries(SceneCovert PRIVATE assimp)

if(BUILD_WITH_EASY_PROFILER)
	target_link_libraries(SceneCovert PRIVATE easy_profiler)
endif()

if(BUILD_WITH_OPTICK)
	target_link_libraries(SceneCovert PRIVATE OptickCore)
endif()


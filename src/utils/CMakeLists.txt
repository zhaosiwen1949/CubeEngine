add_library(utils "")

set_property(TARGET utils PROPERTY CXX_STANDARD 20)
set_property(TARGET utils PROPERTY CXX_STANDARD_REQUIRED ON)

set(SOURCES

        Utils.cpp
        UtilsCubemap.cpp
        UtilsVulkan.cpp
        )

set(HEADERS

        Bitmap.h
        Camera.h
        debug.h
        EasyProfilerWrapper.h
        Trackball.h
        Utils.h
        UtilsCubemap.h
        UtilsFPS.h
        UtilsMath.h
        UtilsVulkan.h
        )

target_sources(utils
        PRIVATE
            ${SOURCES}
        PUBLIC
            ${HEADERS}
        )

target_include_directories(utils
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/../
        )

target_link_libraries(utils PUBLIC glad glfw volk glslang SPIRV glslang-default-resource-limits assimp )

if(BUILD_WITH_EASY_PROFILER)
    target_link_libraries(utils PUBLIC easy_profiler)
endif()

if(BUILD_WITH_OPTICK)
    target_link_libraries(utils PUBLIC OptickCore)
endif()
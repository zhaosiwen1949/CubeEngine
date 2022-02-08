add_library(scene "")

set_property(TARGET scene PROPERTY CXX_STANDARD 20)
set_property(TARGET scene PROPERTY CXX_STANDARD_REQUIRED ON)

set(SOURCES

        Material.cpp
        MergeUtil.cpp
        Scene.cpp
        VtxData.cpp
        )

set(HEADERS

        Cameras.h
        Material.h
        MergeUtil.h
        Scene.h
        vec4.h
        VtxData.h
        )

target_sources(scene
        PRIVATE
            ${SOURCES}
        PUBLIC
            ${HEADERS}
        )

target_include_directories(scene
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/../
        )

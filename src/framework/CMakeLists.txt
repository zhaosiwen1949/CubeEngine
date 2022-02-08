add_library(framework "")

set_property(TARGET framework PROPERTY CXX_STANDARD 20)
set_property(TARGET framework PROPERTY CXX_STANDARD_REQUIRED ON)

set(SOURCES

        # Renderer
        CubeRenderer.cpp
        GuiRenderer.cpp
        InfinitePlaneRenderer.cpp
        LineCanvas.cpp
        MultiRenderer.cpp
        QuadRenderer.cpp
        TriangleRenderer.cpp

        # App
        VulkanApp.cpp
        VulkanResources.cpp
        VulkanShaderProcessor.cpp
        )

set(HEADERS

        # Effects
        effects/HDRProcessor.h
        effects/LuminanceCalculator.h
        effects/SSAOProcessor.h

        # Renderer
        Renderer.h
        CompositeRenderer.h
        CubeRenderer.h
        GuiRenderer.h
        InfinitePlaneRenderer.h
        LineCanvas.h
        MultiRenderer.h
        QuadRenderer.h
        TriangleRenderer.h

        # App
        Barriers.h
        VulkanApp.h
        VulkanResources.h
        VulkanShaderProcessor.h
        )

target_sources(framework
        PRIVATE
            ${SOURCES}
        PUBLIC
            ${HEADERS}
        )

target_include_directories(framework
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/../
        )


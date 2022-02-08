cmake_minimum_required(VERSION 3.15)
project(CubeEngine CXX C)

option(BUILD_WITH_EASY_PROFILER "Enable EasyProfiler usage" ON)
option(BUILD_WITH_OPTICK "Enable Optick usage" OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 1、配置 python 环境，并运行 bootstrap.py，下载 bootstrap.json 中的三方依赖库到 deps 文件夹下
if(WIN32)
    set(PYTHON_EXECUTABLE "python")
else()
    set(PYTHON_EXECUTABLE "python3")
endif()

if((NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/.bootstrap.json") OR ("${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" IS_NEWER_THAN "${CMAKE_CURRENT_SOURCE_DIR}/deps/.bootstrap.json"))
    execute_process(
            COMMAND ${PYTHON_EXECUTABLE} "bootstrap.py"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE bootstrap_result
    )
    if (NOT (${bootstrap_result} EQUAL 0))
        message(FATAL_ERROR "Cannot run bootstrap.py")
    endif()
endif()

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

set(EASY_PROFILER_NO_GUI ON CACHE BOOL "")
set(EASY_PROFILER_NO_SAMPLES ON CACHE BOOL "")

set(ASSIMP_NO_EXPORT ON CACHE BOOL "")
set(ASSIMP_BUILD_DRACO OFF CACHE BOOL "")
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "")
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "")
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "")
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "")
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "")

set(MESHOPT_BUILD_DEMO OFF CACHE BOOL "")
set(MESHOPT_BUILD_TOOLS OFF CACHE BOOL "")
set(MESHOPT_BUILD_SHARED_LIBS OFF CACHE BOOL "")

# 2、开始编译第三方依赖库
add_subdirectory(deps/src/etc2comp)

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(deps/src/vulkan/include)

add_subdirectory(deps/src/glfw)
if(BUILD_WITH_OPTICK)
    add_subdirectory(deps/src/optick)
endif()
add_subdirectory(deps/src/easy_sources)
add_subdirectory(deps/src/assimp)
add_subdirectory(deps/src/meshoptimizer)
add_subdirectory(deps/src/volk)

set(ENABLE_GLSLANG_BINARIES  ON  CACHE BOOL "")
set(ENABLE_HLSL              OFF  CACHE BOOL "")
set(ENABLE_CTEST             OFF  CACHE BOOL "")
set(ENABLE_OPT               OFF  CACHE BOOL "")
set(SKIP_GLSLANG_INSTALL     ON   CACHE BOOL "")
add_subdirectory(deps/src/glslang)

include_directories(.)
include_directories(deps/src)
include_directories(deps/src/glfw/include)
include_directories(deps/src/glm)
include_directories(deps/src/gli)
include_directories(deps/glad/include)
include_directories(deps/src/assimp/include)
include_directories(deps/src/etc2comp/EtcLib/Etc)
include_directories(deps/src/etc2comp/EtcLib/EtcCodec)
include_directories(deps/src/glslang/glslang/Include)
include_directories(deps/src/taskflow)
include_directories(deps/src/rapidjson/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/deps/src/assimp/include)
include_directories(deps/src/stb)
include_directories(deps/src/glslang)
include_directories(deps/src/glslang/StandAlone)
include_directories(deps/src/glslang/src)
include_directories(deps/src/bullet/src)
include_directories(deps/src/ImGuizmo/src)

add_subdirectory(deps/cmake/bullet)
add_subdirectory(deps/cmake/ImGUI)
add_subdirectory(deps/cmake/ImGuizmo)

set(GLAD_SOURCES deps/glad/src/gl.c deps/glad/src/vulkan.c)
if(WIN32)
    set(GLAD_SOURCES ${GLAD_SOURCES} deps/glad/src/wgl.c)
endif()

add_library(glad ${GLAD_SOURCES})

if(BUILD_WITH_EASY_PROFILER)
    message("Enabled EasyProfiler")
    add_definitions(-DBUILD_WITH_EASY_PROFILER=1)
    include_directories(deps/src/easy_profiler/include)
    set_property(TARGET easy_profiler PROPERTY FOLDER "ThirdPartyLibraries")
    set_property(TARGET profiler_converter PROPERTY FOLDER "ThirdPartyLibraries")
endif()
if(BUILD_WITH_OPTICK)
    message("Enabled Optick")
    add_definitions(-DBUILD_WITH_OPTICK=1)
    set_property(TARGET OptickCore PROPERTY FOLDER "ThirdPartyLibraries")
endif()

# 3、采用 FOLDER 组织第三方库
set_property(TARGET glfw          PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET assimp        PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET EtcLib        PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET EtcTool       PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET glad          PROPERTY FOLDER "ThirdPartyLibraries")
#set_property(TARGET IrrXML        PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET meshoptimizer PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET volk          PROPERTY FOLDER "ThirdPartyLibraries")
if(WIN32)
    #set_property(TARGET zlib          PROPERTY FOLDER "ThirdPartyLibraries")
    set_property(TARGET zlibstatic    PROPERTY FOLDER "ThirdPartyLibraries")
    set_property(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTY FOLDER "ThirdPartyLibraries")
endif()
set_property(TARGET uninstall     PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET glslang       PROPERTY FOLDER "ThirdPartyLibraries/glslang")
set_property(TARGET OGLCompiler   PROPERTY FOLDER "ThirdPartyLibraries/glslang")
set_property(TARGET OSDependent   PROPERTY FOLDER "ThirdPartyLibraries/glslang")
set_property(TARGET SPIRV         PROPERTY FOLDER "ThirdPartyLibraries/glslang")
set_property(TARGET SPVRemapper   PROPERTY FOLDER "ThirdPartyLibraries/glslang")

# 4、编译引擎核心库
add_subdirectory(src/framework)

# 5、编译场景数据
add_subdirectory(src/scene)

# 6、编译 utils
add_subdirectory(src/utils)

# 7、编译工具
add_subdirectory(tools)

# 8、编译 samples
add_subdirectory(samples)
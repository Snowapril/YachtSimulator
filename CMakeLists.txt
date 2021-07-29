# CMake version
cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Builds/CMake")

# Declare project
project(YachtSimulator)

# Set output directories
set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Includes
include_directories(Includes)
include_directories(Libraries)
include_directories(Libraries/glfw/include)
include_directories(Libraries/glm)
include_directories(Libraries/imgui)
include_directories(Libraries/tinygltf)
include_directories(Libraries/tinyobjloader)
include_directories(Libraries/vkbootstrap)
include_directories(Libraries/vma)
include_directories(Libraries/Vulkan-Headers/include)

# Set enable output of compile commands during generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build type - Release by default
message("CMake build type: " ${CMAKE_BUILD_TYPE})
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-DDEBUG)
endif()

option(BUILD_COVERAGE "Build code coverage" OFF)
if (CMAKE_BUILD_TYPE MATCHES Debug AND CMAKE_COMPILER_IS_GNUCXX AND BUILD_COVERAGE)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage UnitTests coverage)
endif()

# Compile options
include(Builds/CMake/CompileOptions.cmake)

# Overrides
set(CMAKE_MACOSX_RPATH ON)

# Set resources
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/glfw)
add_subdirectory(Libraries/imgui)
add_subdirectory(Libraries/tinyobjloader)
add_subdirectory(Libraries/vkbootstrap)
add_subdirectory(Libraries/Vulkan-Headers)

# find glslangValidator program
find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/bin/ $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)

# find all the shader files under the shaders folder.
file(GLOB_RECURSE GLSL_SOURCE_FILES
	"${RESOURCES_DIR}/shaders/*.frag",
	"${RESOURCES_DIR}/shaders/*.vert",
	"${RESOURCES_DIR}/shaders/*.comp"
)

# iterate each shader and compile them
foreach(GLSL ${GLSL_SOURCE_FILES})
	message(STATUS "Building Shader")
	get_filename_component(FILE_NAME ${GLSL} NAME)
	set(SPIRV "${RESOURCES_DIR}/shaders/${FILE_NAME}.spv")
	message(STATUS ${GLSL})
	add_custom_command(
		OUTPUT ${SPIRV}
		COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
		DEPENDS ${GLSL}
	)
	list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
	run ALL
	DEPENDS ${SPIRV_BINARY_FILES}
)

add_subdirectory(Sources/Components/Common)
add_subdirectory(Sources/Components/Renderer)
add_subdirectory(Sources/Components/Network)
add_subdirectory(Sources/Components/Model)
add_subdirectory(Sources/Yacht)
add_subdirectory(Tests/UnitTests)
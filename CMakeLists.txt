# CMake version
cmake_minimum_required(VERSION 3.18.6 FATAL_ERROR)
cmake_policy(SET CMP0063 NEW) # visibility
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

# Declare project
project(YachtSimulator)

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Builds/CMake")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

# Set output directories
set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Set enable output of compile commands during generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build type - Release by default
message("CMake build type: " ${CMAKE_BUILD_TYPE})
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-DDEBUG)
endif()

# Option for enable code coverage check
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

# Imports packages
# Get conan build script
find_file(CONAN_SCRIPT
	NAMES conanbuildinfo.txt
	PATHS ${CMAKE_BINARY_DIR}
		  ${PROJECT_SOURCE_DIR}/build
)

# Find conan build script directory
if (CONAN_SCRIPT)
	message(STATUS "Find Conan script directory")
	get_fileNAME_component(CONAN_SCRIPT_DIR ${CONAN_SCRIPT} DIRECTORY)
	list(APPEND CMAKE_MODULE_PATH ${CONAN_SCRIPT_DIR})
endif()

find_package(glslang MODULE REQUIRED)

# find glslangValidator program
find_program(GLSL_VALIDATOR glslangValidator 
	PATHS /usr/bin 
		  /usr/local/bin 
		  $ENV{VULKAN_SDK}/bin/ 
		  $ENV{VULKAN_SDK}/Bin/ 
		  $ENV{VULKAN_SDK}/Bin32/ 
		  ${glslang_INCLUDE_DIR}/../bin
)

# find all the shader files under the shaders folder.
file(GLOB_RECURSE GLSL_SOURCE_FILES
	"${RESOURCES_DIR}/shaders/*.frag"
	"${RESOURCES_DIR}/shaders/*.vert"
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

# Convert all shader files to Spir-V
add_custom_target(
	run ALL
	DEPENDS ${SPIRV_BINARY_FILES}
)

# Build Sub-component modules
add_subdirectory(Sources/Components/Common)
add_subdirectory(Sources/Components/Game)
add_subdirectory(Sources/Components/Network)
add_subdirectory(Sources/Components/Renderer)
# Build main Yacht simulator application
add_subdirectory(Sources/Yacht)
# Build unit testing
add_subdirectory(Tests/UnitTests)
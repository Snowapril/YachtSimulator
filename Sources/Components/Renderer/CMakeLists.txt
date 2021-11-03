# Target name
set(target YachtRenderer)
set(ROOT_DIR ${PROJECT_SOURCE_DIR})
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/Libraries)
set(PUBLIC_HDR_DIR ${PROJECT_SOURCE_DIR}/Includes/Components/Renderer)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Find essential packages
find_package(VulkanHeaders MODULE REQUIRED)
find_package(vk-bootstrap MODULE REQUIRED)
find_package(vulkan-memory-allocator MODULE REQUIRED)
find_package(glfw3 MODULE REQUIRED)
find_package(glm MODULE REQUIRED)
find_package(imgui MODULE REQUIRED)
find_package(TinyGLTF MODULE REQUIRED)

# Find vulkan sdk.
message(STATUS "Attempting auto locate Vulkan using CMake......")

# Find Vulkan Path using CMake's Vulkan Module
# This will return Boolean 'Vulkan_FOUND' indicating the status of find as success(ON) or fail(OFF).
# Include directory path - 'Vulkan_INCLUDE_DIRS' and 'Vulkan_LIBRARY' with required libraries.
find_package(Vulkan REQUIRED)

if (UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

if (NOT Vulkan_FOUND)
	if (WIN32)
		find_library(Vulkan_LIBRARY NAMES vulkan-1 vulkan PATHS $ENV{VULKAN_SDK}/Lib ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/vulkan REQUIRED)
	elseif(LINUX)
		find_library(Vulkan_LIBRARY NAMES vulkan PATHS $ENV{VULKAN_SDK}/lib ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/vulkan REQUIRED)
	elseif(APPLE)
		find_library(Vulkan_LIBRARY NAMES vulkan PATHS $ENV{VULKAN_SDK}/lib ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/vulkan REQUIRED)
	endif()
	if (Vulkan_LIBRARY)
		set(Vulkan_FOUND ON)
		message(STATUS "Using Bundled version of Vulkan")
	endif()
endif()


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

#
add_custom_target(
	run ALL
	DEPENDS ${SPIRV_BINARY_FILES}
)

# Includes
set(PUBLIC_HDRS
    ${PUBLIC_HDR_DIR}/Camera.hpp
    ${PUBLIC_HDR_DIR}/Device.hpp
    ${PUBLIC_HDR_DIR}/Initializer.hpp
    ${PUBLIC_HDR_DIR}/Pipeline.hpp
    ${PUBLIC_HDR_DIR}/Renderer.hpp
    ${PUBLIC_HDR_DIR}/RenderSystem.hpp
    ${PUBLIC_HDR_DIR}/Resource.hpp
    ${PUBLIC_HDR_DIR}/SwapChain.hpp
    ${PUBLIC_HDR_DIR}/Utils.hpp
    ${PUBLIC_HDR_DIR}/Window.hpp)

# Set sources list
set(SRCS
    ${SRC_DIR}/Device.cpp
    ${SRC_DIR}/Initializer.cpp
    ${SRC_DIR}/Pipeline.cpp
    ${SRC_DIR}/Renderer.cpp
    ${SRC_DIR}/RenderSystem.cpp
    ${SRC_DIR}/Resource.cpp
    ${SRC_DIR}/SwapChain.cpp
    ${SRC_DIR}/Utils.cpp
    ${SRC_DIR}/Window.cpp)

# Build static library with given sources
add_library(${target} STATIC ${SRCS})

# Project options
set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    PUBLIC_HEADER [${PUBLIC_HDRS}]
)

#Include directories
target_include_directories(${target}
    PUBLIC
    $<BUILD_INTERFACE:${PUBLIC_HDR_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
    ${Vulkan_Headers_INCLUDE_DIR}
    PRIVATE
    ${glfw_INCLUDE_DIR}
    ${glm_INCLUDE_DIR}
    ${vulkan-memory-allocator_INCLUDE_DIR}
    ${imgui_INCLUDE_DIR}
    ${TinyGLTF_INCLUDE_DIR}
    ${vk-bootstrap_INCLUDE_DIR}
    PRIVATE
    ${ROOT_DIR}/Includes
)

# Compile options
target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)

# Link libraries
target_link_libraries(${target}
    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}
	${DEFAULT_LIBRARIES}   
    ${Vulkan_LIBRARY} 
    glfw::glfw
    glm::glm
    vulkan-memory-allocator::vulkan-memory-allocator
    imgui::imgui
    TinyGLTF::TinyGLTF
    vk-bootstrap::vk-bootstrap
)

# Compile definitions
target_compile_definitions(${target}
    PRIVATE
    RESOURCES_DIR="${RESOURCES_DIR}"
    ${DEFAULT_COMPILE_DEFINITIONS}
)

# Install
install(TARGETS  ${target}
        EXPORT   ${target}-config
        RUNTIME  DESTINATION bin
        LIBRARY  DESTINATION lib
        ARCHIVE  DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)
install(EXPORT   ${target}-config
        DESTINATION share/${target}
)
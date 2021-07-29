# Target name
set(target YachtRenderer)
set(ROOT_DIR ${PROJECT_SOURCE_DIR})
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/Libraries)
set(PUBLIC_HDR_DIR ${PROJECT_SOURCE_DIR}/Includes/Components/Renderer)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Find essential packages
find_package(Vulkan MODULE REQUIRED)
find_package(vk-bootstrap MODULE REQUIRED)
find_package(vulkan-memory-allocator MODULE REQUIRED)
find_package(glfw3 MODULE REQUIRED)
find_package(glm MODULE REQUIRED)
find_package(imgui MODULE REQUIRED)
find_package(TinyGLTF MODULE REQUIRED)

# Includes
set(PUBLIC_HDRS
    ${PUBLIC_HDR_DIR}/Camera.hpp
    ${PUBLIC_HDR_DIR}/Device.hpp
    ${PUBLIC_HDR_DIR}/Initializer.hpp
    ${PUBLIC_HDR_DIR}/Pipeline.hpp
    ${PUBLIC_HDR_DIR}/Renderer.hpp
    ${PUBLIC_HDR_DIR}/Resource.hpp
    ${PUBLIC_HDR_DIR}/SwapChain.hpp
    ${PUBLIC_HDR_DIR}/Utils.hpp
    ${PUBLIC_HDR_DIR}/Window.hpp)

#
set(SRCS
    ${SRC_DIR}/Device.cpp
    ${SRC_DIR}/Initializer.cpp
    ${SRC_DIR}/Renderer.cpp
    ${SRC_DIR}/Resource.cpp
    ${SRC_DIR}/SwapChain.cpp
    ${SRC_DIR}/Utils.cpp
    ${SRC_DIR}/Window.cpp)

# 
add_library(${target} ${SRCS})

# Project options
set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    PUBLIC_HEADER ${PUBLIC_HDRS}
)

#Include directories
target_include_directories(${target}
    PUBLIC
    $<BUILD_INTERFACE:${PUBLIC_HDR_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
    ${Vulkan_INCLUDE_DIR}
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

#
target_link_libraries(${target}
    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}
	${DEFAULT_LIBRARIES}    
    ${Vulkan_LIBRARY}
    ${glfw_LIBRARIES}
    ${glm_LIBRARIES}
    ${vulkan-memory-allocator_LIBRARIES}
    ${imgui_LIBRARIES}
    ${TinyGLTF_LIBRARIES}
    ${vk-bootstrap_LIBRARIES}
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
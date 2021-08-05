# Target name
set(target YachtGame)
set(ROOT_DIR ${PROJECT_SOURCE_DIR})
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/Libraries)
set(PUBLIC_HDR_DIR ${PROJECT_SOURCE_DIR}/Includes/Components/Game)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Includes
set(PUBLIC_HDRS
    ${PUBLIC_HDR_DIR}/Dice.hpp
    ${PUBLIC_HDR_DIR}/Player.hpp
    ${PUBLIC_HDR_DIR}/ScoreBoard.hpp)

# Set sources list
set(SRCS
    ${SRC_DIR}/Dice.cpp
    ${SRC_DIR}/Player.cpp
    ${SRC_DIR}/ScoreBoard.cpp)

# Build static library with given sources
add_library(${target} STATIC ${SRCS})

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
)

# Compile definitions
target_compile_definitions(${target}
    PRIVATE
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
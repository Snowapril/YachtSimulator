# Target name
set(target UnitTests)
set(ROOT_DIR ${PROJECT_SOURCE_DIR})
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/Libraries)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#
find_package(doctest REQUIRED)

#
set(SRCS
    ${SRC_DIR}/UnitTests.cpp
    ${SRC_DIR}/ConstantsTest.cpp)

# Build executable
add_executable(${target} ${SRCS})

# Project options
set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
)

# Compile options
# GCC and Clang compiler options
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
        # /wd4996       # -> disable warning: non-Standard std::tr1 namespace and TR1-only machinery (because of gtest)		
        -Wno-unused-variable
        )
endif()

#Include directories
target_include_directories(${target}
    PUBLIC
    $<BUILD_INTERFACE:${PUBLIC_HDR_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
    PRIVATE
    ${doctest_INCLUDE_DIR}
    ${ROOT_DIR}/Includes
)

#
target_compile_options(${target}
    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

#
target_compile_definitions(${target}
    PRIVATE
    RESOURCE_DIR="${PROJECT_SOURCE_DIR}/Resources/"
    ${DEFAULT_COMPILE_DEFINITIONS}
)

# Link libraries
target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
	${DEFAULT_LIBRARIES}
    ${doctest_LIBRARIES}
    YachtCommon
    YachtGame
    YachtNetwork
    YachtRenderer)
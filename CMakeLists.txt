cmake_minimum_required(VERSION 3.20)
project(EchoWaves LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically find all .cpp files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

# Create executable target
add_executable(index ${SOURCES})

# Include SDL3 headers
target_include_directories(index PRIVATE "C:/SDL/include")

# Check if we are using Emscripten
if(EMSCRIPTEN)
    # Set output directory for web files
    set(DIST_DIR "${CMAKE_SOURCE_DIR}/dist")
    file(MAKE_DIRECTORY ${DIST_DIR})

    # Tell Emscripten to build HTML/JS/WASM directly in dist/
    set_target_properties(index PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${DIST_DIR}           # Output folder
        LINK_FLAGS "-s USE_SDL=3 -s WASM=1 -O0"        # Emscripten flags
        SUFFIX ".html"                                  # Produce HTML wrapper
    )
endif()

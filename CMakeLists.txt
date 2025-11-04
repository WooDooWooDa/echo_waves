cmake_minimum_required(VERSION 3.20)
project(EchoWaves LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically include all source files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")
add_executable(index ${SOURCES})

# Include SDL3 headers
target_include_directories(index PRIVATE "C:/SDL/include")

# Web build configuration
if(EMSCRIPTEN)
    # Set output folder
    set(DIST_DIR "${CMAKE_SOURCE_DIR}/dist")
    file(MAKE_DIRECTORY ${DIST_DIR})

    # Folder containing text or data files you want to access in the browser
    set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

    # Preload the assets directory into the Emscripten virtual FS so we can use files in ./assets
    set(PRELOAD_FLAG "--preload-file ${ASSETS_DIR}@/assets")

    # Configure Emscripten build output
    set_target_properties(index PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${DIST_DIR}
        LINK_FLAGS "-s USE_SDL=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -O2 ${PRELOAD_FLAG} -s EXIT_RUNTIME=1 -s FORCE_FILESYSTEM=1"
        SUFFIX ".html"
    )
endif()

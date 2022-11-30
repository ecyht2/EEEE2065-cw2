cmake_minimum_required(VERSION 3.21.1)

project(number-guessing-game VERSION 1.0.0 LANGUAGES CXX)

# Configure project paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR})

# Exporting compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configure CXX standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES number-guessing-game)

foreach(SOURCE ${SOURCES})
  add_subdirectory(src/${SOURCE})
endforeach()

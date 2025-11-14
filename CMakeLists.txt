# Copyright (c) 2025 Wenchao Huang <physhuangwenchao@gmail.com>
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.10)

# Target name
set(TARGET_NAME easywin32)

# Project name
project(${TARGET_NAME} LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Organize targets into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Library options
option(EZWIN32_BUILD_TESTS "Build tests for ${TARGET_NAME} library" OFF)
option(EZWIN32_BUILD_EXAMPLES "Build examples for ${TARGET_NAME} library" OFF)

# Source files
file(GLOB EZWIN32_SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/easywin32.cpp"
    "${PROJECT_SOURCE_DIR}/easywin32.h"
)

# Create the static library
add_library(${TARGET_NAME} STATIC ${EZWIN32_SOURCES})

# Include directories
target_include_directories(${TARGET_NAME} INTERFACE ${PROJECT_SOURCE_DIR})

# MSVC settings
if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:/MP /W4 /WX>)
endif()

# Optional: Add tests if enabled
if(EZWIN32_BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Optional: Add examples if enabled
if(EZWIN32_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
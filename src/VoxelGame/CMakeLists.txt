﻿# CMakeList.txt : CMake project for MortarCore, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.29)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (VoxelGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE VoxelGame_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.inl")

# Add source to this project's executable.
add_executable(VoxelGame ${VoxelGame_SOURCES})

target_sources(VoxelGame PRIVATE ${VoxelGame_SOURCES})

target_include_directories(VoxelGame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
# Add directories with lose .dlls or .libs here
target_link_directories(MortarCore PRIVATE
  
)

# Set configuration properties for MortarCore
if(MSVC)
    target_compile_options(MortarCore PRIVATE
        /W3
        /MP # multithreaded build
        /WX # warnings as errors
        /ZI # program database for edit and continue
    )
else()
    target_compile_options(MortarCore PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()

# Set Playground as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MortarCore)

# Filters
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${MortarCore_SOURCES})

# Enable solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
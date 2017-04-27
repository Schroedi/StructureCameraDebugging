cmake_minimum_required(VERSION 3.7)
project(StructureCameraDebugging)

set(CMAKE_CXX_STANDARD 11)

# OpenNI2
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(OpenNI2)
include_directories(SYSTEM ${OPENNI2_INCLUDE_DIR})
link_directories(${OPENNI2_LIBRARY_DIR})

set(SOURCE_FILES OpenNICam.cpp main.cpp)
add_executable(StructureCameraDebugging ${SOURCE_FILES})
target_link_libraries(StructureCameraDebugging
        OpenNI2)
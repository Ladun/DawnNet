cmake_minimum_required(VERSION 3.13)
 
set(PROJECT_NAME DawnNet)

project(${PROJECT_NAME})

# find boost packages
find_package(Boost 1.82.0 REQUIRED COMPONENTS thread)

# source
file(GLOB_RECURSE SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/*.cpp)

add_library(${PROJECT_NAME} STATIC 
            ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${Boost_INCLUDE_DIRS})

# Linking
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


if(COMMAND target_precompile_headers)
    target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/DawnNet/pch.hpp)
    message("Use precompiled headers")
endif()

# compile option for c17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
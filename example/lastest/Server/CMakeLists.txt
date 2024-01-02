cmake_minimum_required(VERSION 3.13)
 
set(PROJECT_NAME server)

project(${PROJECT_NAME})

# find boost packages
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../DawnNet DawnNet)

# source
file(GLOB_RECURSE SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/../Packets)

# Linking
target_link_libraries(${PROJECT_NAME} DawnNet)

# compile option for c17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
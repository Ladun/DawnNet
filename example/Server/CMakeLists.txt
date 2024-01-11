cmake_minimum_required(VERSION 3.15)
 
set(PROJECT_NAME server)

project(${PROJECT_NAME})

if(UNIX)
     set(Protobuf_INCLUDE_DIR /usr/local/include)
     set(Protobuf_DEBUG ON)
     set(Protobuf_USE_STATIC_LIBS ON)
     find_package(Protobuf REQUIRED) 
     set(CUSTOM_Protobuf_LIBRARY /usr/local/lib/libprotobuf.a)       
else()
     set(Protobuf_INCLUDE_DIRS E:/Dev/tools/protobuf/protobuf/src)
     set(CUSTOM_Protobuf_LIBRARY E:/Dev/tools/protobuf/build/Debug/libprotobufd.lib)    
     set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")     
endif()

# find boost packages
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../DawnNet DawnNet)

# source
file(GLOB_RECURSE SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

add_compile_definitions(DN_DEBUG)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/src
                           ${Protobuf_INCLUDE_DIRS})

# Linking
target_link_libraries(${PROJECT_NAME} PRIVATE
                      DawnNet ${CUSTOM_Protobuf_LIBRARY})

# compile option for c17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
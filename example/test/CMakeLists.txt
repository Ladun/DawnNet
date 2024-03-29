cmake_minimum_required(VERSION 3.15)
 
set(PROJECT_NAME test)

project(${PROJECT_NAME})


# Protobuf
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

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../DawnNet DawnNet)

message("ProtoBuf found:" ${Protobuf_FOUND})
message("ProtoBuf version:" ${Protobuf_VERSION})
message("ProtoBuf libraries:" ${Protobuf_LIBRARIES})
message("ProtoBuf library:" ${Protobuf_LIBRARY})
message("Protoc library:" ${Protobuf_PROTOC_LIBRARIES})
message("ProtoBuf include directory:" ${Protobuf_INCLUDE_DIRS})

# source
file(GLOB_RECURSE SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

add_compile_definitions(DN_DEBUG)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/src
                           ${Protobuf_INCLUDE_DIRS}
                           ${Boost_INCLUDE_DIRS})
# Linking
target_link_libraries(${PROJECT_NAME} PRIVATE
                       ${CUSTOM_Protobuf_LIBRARY} DawnNet)

# compile option for c17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

cmake_minimum_required(VERSION 3.13)
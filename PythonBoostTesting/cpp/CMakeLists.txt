cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I../testproj_bit")
project(testproj VERSION 0.1.0)
include_directories(/usr/local/include)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../testproj_bits
)
AUX_SOURCE_DIRECTORY(src SRC_FILES)
set(PROJECT_SOURCE_DIR "src")
set(PROJECT_INCLUDE_DIR "include/testproj_bit")
set(SOURCE_FILES ${SRC_FILES} 
    ${PROJECT_INCLUDE_DIR}/testproj.hpp
    ${PROJECT_SOURCE_DIR}/testproj.cpp
    )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})
add_library(testproj SHARED ${SOURCE_FILES})
target_include_directories(testproj PRIVATE include/testproj)
install(TARGETS testproj DESTINATION lib)
install(FILES include/testproj DESTINATION include)
install(DIRECTORY include/testproj_bit DESTINATION include)

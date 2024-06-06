cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(PYBIND11_FINDPYTHON ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)

endif()

set(CHANGE_CXX_FLAGS "-03")
set(CMAKE_CXX_FLAGS_REALEASE "-03")
set(pybind11_DIR "/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/pybind11/share/cmake/pybind11")

project(testproj)

include_directories("${CMAKE_SOURCE_DIR}/cpp/include/testproj_bit")
include_directories("{CMAKE_SOURCE_DIR}/python")
include_directories("/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/pybind11/include")

file (GLOB SOURCE_FILES "cpp/src/*.cpp")
file (GLOB HEADER_FILES "cpp/include,testproj_bit/*.hpp")
file (GLOB PYTHON_FILES "python/*.cpp" "python/*.hpp")

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SOURCE_FILES} ${HEADER_FILES} ${PYTHON_FILES})

find_package(pybind11 REQUIRED)
pybind11_add_module(testproj 
        ${SOURCE_FILES} 
        ${HEADER_FILES} 
        ${PYTHON_FILES})
target_link_libraries(testproj PUBLIC)
install(TARGETS testproj
  COMPONENT python
  LIBRARY DESTINATION "${PYTHON_LIBRARY_DIR}"
  )
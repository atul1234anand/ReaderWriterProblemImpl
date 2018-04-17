cmake_minimum_required (VERSION 3.8)
project (ReaderWriterProblemImpl)

# global include local project source dir
include_directories ("${PROJECT_SOURCE_DIR}/vendor/include")
include_directories ("${PROJECT_SOURCE_DIR}/src")

# global link lib
link_directories ("${PROJECT_SOURCE_DIR}/vendor/lib")

# set compile parameter
set (CMAKE_C_FLAGS "-std=c99")
set (CMAKE_CXX_FLAGS "-std=c++11")

# make libquickimage
add_subdirectory (src)

link_directories ("${PROJECT_BINARY_DIR}/src")

add_executable (rw.out demo/demo.cpp)
target_link_libraries (rw.out readwrite)

install (TARGETS rw.out DESTINATION /bin)

# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

project ("square_solver")

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(SOLVER_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOLVER_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(SOLVER_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(COMMONLIBS_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/commonlibs)

include_directories(${SOLVER_INSTALL_INCLUDE_DIR})
include_directories(${COMMONLIBS_HEADERS_DIR})

# Include sub-projects.
add_subdirectory ("src")
# Disable tests
#add_subdirectory ("test")

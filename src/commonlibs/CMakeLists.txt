# CMakeList.txt : CMake project for square_solver, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(commonlibs C CXX)

set(SOURCE_FILES
    solver.hpp
    solver.cpp
    monitor.hpp
)

add_library(commonlibs SHARED STATIC ${SOURCE_FILES})

install(TARGETS commonlibs DESTINATION ${SOLVER_INSTALL_LIB_DIR})
install(FILES solver.hpp DESTINATION ${SOLVER_INSTALL_INCLUDE_DIR})
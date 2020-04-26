# CMakeList.txt : CMake project for square_solver, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

project(commonlibs C CXX)

set(SOURCE_FILES
    quadricequation.hpp
    quadricequation.cpp
    blockingqueue.cpp
    blockingqueue.hpp
    workerbase.cpp
    workerbase.hpp
    solver.hpp
    solver.cpp
    producercin.hpp
    producercin.cpp
    consumer.hpp 
    consumer.cpp 
    producer.hpp 
    producer.cpp)

add_library(commonlibs STATIC ${SOURCE_FILES})

install(TARGETS commonlibs DESTINATION ${SOLVER_INSTALL_LIB_DIR} )
#install(FILES monitor.hpp solver.hpp DESTINATION ${SOLVER_INSTALL_INCLUDE_DIR})
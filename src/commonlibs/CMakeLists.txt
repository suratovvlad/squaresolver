# CMakeList.txt : CMake project for square_solver, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

project(commonlibs C CXX)

set(SOURCE_FILES
    quadraticequation.hpp
    solver.hpp
    solver.cpp
    blockingqueue.hpp
    quadraticequationworker.hpp
    workerbase.hpp
    producercin.hpp
    producercin.cpp
    consumer.hpp 
    consumer.cpp 
    producer.hpp 
    producer.cpp)

add_library(commonlibs STATIC ${SOURCE_FILES})

install(TARGETS commonlibs DESTINATION ${SOLVER_INSTALL_LIB_DIR} )
install(FILES  quadraticequation.hpp quadraticequationworker.hpp solver.hpp blockingqueue.hpp workerbase.hpp consumer.hpp producer.hpp  DESTINATION ${SOLVER_INSTALL_INCLUDE_DIR})
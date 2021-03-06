# CMakeList.txt : CMake project for square_solver, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.10)

project(solver_tests)

find_package(Catch2 CONFIG REQUIRED)
find_package(Threads REQUIRED)

include_directories(${COMMONLIBS_HEADERS_DIR})


set(SOURCE_FILES
    simpletaskworker.hpp
    simpletaskgenerator.hpp
    simpletaskgenerator.cpp
    simpletaskconsumer.hpp
    simpletaskconsumer.cpp
    testmain.cpp
    )

add_executable(solver_tests ${SOURCE_FILES})
target_link_libraries(solver_tests commonlibs Catch2::Catch2)
target_link_libraries(solver_tests Threads::Threads)
install(TARGETS solver_tests DESTINATION bin)

include(CTest)
include(Catch)
catch_discover_tests(solver_tests)

#add_test(NAME Test1 COMMAND solver_tests)

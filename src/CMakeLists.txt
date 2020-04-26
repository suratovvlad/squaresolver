# CMakeList.txt : CMake project for square_solver, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)
project(solver)

add_subdirectory(commonlibs)

# Add source to this project's executable.
set(SOURCE_FILES main.cpp)

add_executable(square_solver ${SOURCE_FILES})

# TODO: Add tests and install targets if needed.
target_link_libraries(square_solver commonlibs)
install(TARGETS square_solver DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})


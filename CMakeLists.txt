cmake_minimum_required(VERSION 3.10) 

set(CMAKE_BUILD_TYPE "Debug")
project(MDSolver VERSION 0.0)

add_executable(MDSolver main.cpp 

./spline/Spline.cpp
./spline/SplBase.cpp
./spline/SplAkima.cpp
./spline/SplLagrange3.cpp

./math/Quaternion.cpp
./math/Coord7.cpp

./geo/Mesh.cpp
./geo/GP_Circle.cpp
)

target_include_directories(MDSolver PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")



                           
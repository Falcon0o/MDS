cmake_minimum_required(VERSION 3.10) 


find_package(Eigen3 REQUIRED)
set(CMAKE_BUILD_TYPE "Debug")
project(MDSolver VERSION 0.0)

add_executable(MDSolver main.cpp 

./spline/Spline.cpp
./spline/SplBase.cpp
./spline/SplAkima.cpp
./spline/SplLagrange3.cpp

./math/Quaternion.cpp
./math/CoordSys.cpp

# ./geo/Mesh.cpp
# ./geo/GP_Circle.cpp
)

target_include_directories(MDSolver PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")



                           
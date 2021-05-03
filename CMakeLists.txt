 cmake_minimum_required(VERSION 3.19)
 project(NumericalComputationExperiment VERSION 1.0)

 # specify the C++ standard
 set(CMAKE_CXX_STANDARD 17)
 set(CMAKE_CXX_STANDARD_REQUIRED True)

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()
 include_directories(${CMAKE_BINARY_DIR})

 add_executable(main main.cpp)
 find_package(LAPACK REQUIRED)
 find_package(OpenMP REQUIRED)
 include_directories(${CMAKE_BINARY_DIR})
 target_link_libraries(main ${CONAN_LIBS} LAPACK::LAPACK OpenMP::OpenMP_CXX)
 
cmake_minimum_required(VERSION 3.8)

project(DynamicProgramming VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("-Wall" "-Wextra")
#------------mdp
aux_source_directory("../src/mdp" MDP)
add_library(mdp STATIC ${MDP})
target_include_directories(mdp PUBLIC "../src/mdp")
target_compile_features(mdp PUBLIC cxx_std_20)

#------------executable
add_executable(DynamicProgramming ../src/main.cpp)

#------------link libraries
target_link_libraries(DynamicProgramming PUBLIC mdp)

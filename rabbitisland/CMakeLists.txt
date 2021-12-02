# Author: Jeroen de Haas <jah.dehaas@avans.nl>
cmake_minimum_required(VERSION 3.1.3)
project(rabbitisland)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wpedantic)#  -Werror)
    add_compile_options("$<$<CONFIG:DEBUG>:-g>")
endif()

  
add_executable(rabbitisland
  src/kmint/rabbitisland/main.cpp
  src/kmint/rabbitisland/node_algorithm.cpp
  src/kmint/rabbitisland/resources.cpp
  src/kmint/rabbitisland/dog.cpp
  src/kmint/rabbitisland/misses.cpp
  src/kmint/rabbitisland/mister.cpp
  src/kmint/rabbitisland/rabbit.cpp)

target_compile_features(rabbitisland PUBLIC cxx_std_17)
target_link_libraries(rabbitisland PRIVATE kmint)
target_include_directories(rabbitisland PRIVATE 
  src
  include)

add_custom_target(rabbitisland-resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")

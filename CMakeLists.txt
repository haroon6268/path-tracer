cmake_minimum_required(VERSION 3.3)
project(path_tracer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  glm_fetch
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  SYSTEM
)

FetchContent_MakeAvailable(glm_fetch)

add_executable(pathtracer
  main.cpp
)

target_link_libraries(pathtracer PUBLIC glm)



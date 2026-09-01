cmake_minimum_required(VERSION 3.15)
project(Function_renderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(sfml)
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/modelo/Vector3.cpp
    src/modelo/Vector4.cpp
    src/modelo/Matriz4x4.cpp
    src/modelo/Camara.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
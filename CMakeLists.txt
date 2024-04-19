cmake_minimum_required(VERSION 3.16)

project(TronGame)

file(GLOB SOURCES "src/*.cpp" "src/*.c" "include/*.hpp" "include/*.h" "libs/*.cpp" "libs/*.h") 

add_executable(TronGame ${SOURCES})

# configure_file("include/Graphical/Shaders/ShaderFiles/4.2.texture.vs" "4.2.texture.vs" COPYONLY)
# configure_file("include/Graphical/Shaders/ShaderFiles/4.2.texture.fs" "4.2.texture.fs" COPYONLY)


file(COPY "assets/" DESTINATION "assets/")

include(FetchContent)

FetchContent_Declare(
    glfw  
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3-stable
)
FetchContent_GetProperties(glfw)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG c
)
FetchContent_MakeAvailable(glad)

add_library(glad "${glad_SOURCE_DIR}/src/glad.c" "${glad_SOURCE_DIR}/include/glad/glad.h")
target_include_directories(glad PUBLIC "${glad_SOURCE_DIR}/include")

find_package(OpenGL REQUIRED)

target_include_directories(TronGame 
    PUBLIC
        include
        ${glfw_SOURCE_DIR}/include
        ${glm_SOURCE_DIR}
        ${glad_SOURCE_DIR}/include

    PRIVATE
        src
        src/internal
)
message(${glad_SOURCE_DIR})
target_link_libraries(TronGame PRIVATE glfw glad glm::glm ${OPENGL_LIBRARIES})

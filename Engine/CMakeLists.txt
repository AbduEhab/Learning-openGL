project(Engine VERSION 0.1.0)

add_library(${PROJECT_NAME} 
    src/core/Input.cpp 
    src/core/Window.cpp
    src/renderer/Shader.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC include/
)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/include
    PUBLIC build/external/glad/include
    PUBLIC external/glm
    PUBLIC include/
)

# Add target link directory here: (Where the Libs are)
target_link_directories(${PROJECT_NAME}
    PRIVATE external/glfw/src
    PRIVATE external/glad
    PRIVATE external/glm
)

target_link_libraries(${PROJECT_NAME} glfw glad)

cmake_minimum_required(VERSION 3.9)
project(Exam)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR})

add_executable(Exam main.cpp src/InputManager.cpp include/InputManager.h include/Drawable2D.h include/Updatable.h src/GameObject.cpp include/GameObject.h include/Component.h src/Game.cpp include/Game.h)

target_link_libraries(Exam ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})
# -lmingw32 -lSDL2main -lSDL2 #[[-mwindows]]
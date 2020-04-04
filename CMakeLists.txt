cmake_minimum_required(VERSION 3.9)
project(Exam)
INCLUDE(FindPkgConfig)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL_ttf REQUIRED)

#include_directories(${SDL2_INCLUDE_DIR}
#        ${SDL2_IMAGE_INCLUDE_DIR})

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL_TTF)


add_executable(Exam main.cpp src/InputManager.cpp src/TextureManager.cpp include/VoidWarp.h src/Hallway.cpp include/Hallway.h src/VoidWarp.cpp include/TextureManager.h include/InputManager.h src/Game.cpp include/Game.h src/GameObject.cpp include/GameObject.h src/Player.cpp include/Player.h src/WallEntity.cpp include/Map.h src/Map.cpp include/WallEntity.h src/Pellet.cpp include/Pellet.h src/Ghost.cpp include/Ghost.h)
target_link_libraries(Exam ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL_TTF_LIBRARIES})
# -lmingw32 -lSDL2main -lSDL2 #[[-mwindows]]
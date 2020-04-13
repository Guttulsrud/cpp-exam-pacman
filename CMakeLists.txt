cmake_minimum_required(VERSION 3.9)
project(Exam)
INCLUDE(FindPkgConfig)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

add_executable(Exam main.cpp src/InputManager.cpp utils/SDL_FontCache.c utils/SDL_FontCache.h src/TextureManager.cpp include/TextureManager.h include/InputManager.h src/Game.cpp include/Game.h src/GameObject.cpp include/GameObject.h src/Player.cpp include/Player.h include/Map.h src/Map.cpp src/Pellet.cpp include/Pellet.h src/Ghost.cpp include/Ghost.h src/MovableObject.cpp include/MovableObject.h src/StationaryObject.cpp include/StationaryObject.h src/EntityAnimator.cpp include/EntityAnimator.h)
target_link_libraries(Exam ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})

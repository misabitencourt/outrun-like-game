include(FindPkgConfig)

# sudo apt install libsdl2-dev libsdl-ttf2.0-dev libsdl2-mixer-dev libsdl2-image-dev
cmake_minimum_required(VERSION 3.7)
project(Outrun)

find_package(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_image REQUIRED IMPORTED_TARGET SDL2_image)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)

include_directories(
  ${SDL2_INCLUDE_DIRS}
  ${SDL2mixer_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIR}
)

add_executable(Outrun src/main.cpp)

target_link_libraries(Outrun 
    ${SDL2_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
    ${SDL2MIXER_LIBRARIES}
    PkgConfig::SDL2_image
    PkgConfig::SDL2_Mixer
)

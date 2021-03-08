#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>

const unsigned int SCENE_MAIN_MENU = 0;
const unsigned int SCENE_INSTRUCTIONS = 1;
const unsigned int SCENE_IN_GAME = 3;

const static int SCENE_GAME_CAR_SPEED = 4;
const static int SCENE_GAME_CAR_TURNING = 5;
const static int SCENE_GAME_CAR_MTS_TRAVELED = 6;
const static int SCENE_GAME_CAR_TOPSPEED = 7;


#include "./ResPath.h"
#include "./factory/SceneConstants.h"
#include "./factory/Entities.h"
#include "./view/Sound.h"
#include "./view/Sprite.h"
#include "./view/Tileset.h"
#include "./view/Text.h"
#include "./view/Scene.h"
#include "./factory/SceneBuilder.h"
#include "./view/MainWindow.h"

int main(int, char**)
{
    MainWindow mainWindow;
    mainWindow.title = "Outrun";
    mainWindow.width = 640;
    mainWindow.height = 480;
    mainWindow.x = 100;
    mainWindow.y = 100;
    mainWindow.init();
    return 0;
}


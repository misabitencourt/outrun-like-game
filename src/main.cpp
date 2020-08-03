#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>

#include "./ResPath.h"
#include "./factory/Entities.h"
#include "./view/Sound.h"
#include "./view/Sprite.h"
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


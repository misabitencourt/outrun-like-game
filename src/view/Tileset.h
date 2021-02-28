#include <list>
#include <string>
#include <map>

class Tileset {
    public:
        int id;
        SDL_Texture *sheet;
        int width;
        int height;
        int x;
        int y;
        std::map<int, int> state;

    void render(SDL_Renderer *renderer, std::list<std::list<int>> coords) {
        int w, h;
        SDL_QueryTexture(sheet, NULL, NULL, &w, &h);

        std::list<std::list<int>>::iterator coordsIt;
        for (coordsIt = coords.begin(); coordsIt != coords.end(); ++coordsIt){
            // Sprite cut
            SDL_Rect clip;
            clip.x = x;
            clip.y = y;
            clip.w = width;
            clip.h = height;   

            // Screen destiny
            SDL_Rect dst;

            std::list<int>::iterator coordPosIt = coordsIt->begin();
            std::advance(coordPosIt, 0);
            dst.x = coordPosIt;

            std::advance(coordPosIt, 1);
            dst.y = y;
            
            dst.w = width;
            dst.h = height; 

            SDL_RenderCopy(renderer, sheet, &clip, &dst);
        }
    }
};
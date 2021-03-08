#include <list>
#include <string>
#include <map>

class TilesetPaint {
    public:
        int tilesetX;
        int tilesetY;
        int tilesetW;
        int tilesetH;
        int x;
        int y;
};

class Tileset {
    public:
        int id;
        std::string image;
        SDL_Texture *sheet;
        int width;
        int height;
        int x;
        int y;
        std::map<int, int> state;
        std::list<TilesetPaint> coords;

    void load(SDL_Renderer *renderer) {
        std::string file = "resources/tilesets/" + image;
        sheet = IMG_LoadTexture(renderer, file.c_str());
    }

    void render(SDL_Renderer *renderer) {
        int w, h;
        SDL_QueryTexture(sheet, NULL, NULL, &w, &h);

        std::list<TilesetPaint>::iterator coordsIt;
        for (coordsIt = coords.begin(); coordsIt != coords.end(); ++coordsIt){
            // Sprite cut
            SDL_Rect clip;
            clip.x = coordsIt->tilesetX;
            clip.y = coordsIt->tilesetY;
            clip.w = coordsIt->tilesetW;
            clip.h = coordsIt->tilesetH;

            // Screen destiny
            SDL_Rect dst;
            dst.x = coordsIt->x;
            dst.y = coordsIt->y;            
            dst.w = coordsIt->tilesetW;
            dst.h = coordsIt->tilesetH;

            SDL_RenderCopy(renderer, sheet, &clip, &dst);
        }
    }
};
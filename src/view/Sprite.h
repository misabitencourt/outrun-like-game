#include <string>
#include <map>

class Sprite {
    public:
        int id;
        std::string image;
        SDL_Texture *sheet;
        int width;
        int height;
        int x;
        int y;
        int frame;
        int frameSpeed;
        std::map<int, int> state;

    void load(SDL_Renderer *renderer) {        
        std::string file = "resources/sprites/" + image;
        sheet = IMG_LoadTexture(renderer, file.c_str());
    }

    void render(SDL_Renderer *renderer) {
        int w, h;
        SDL_QueryTexture(sheet, NULL, NULL, &w, &h);

        // Sprite cut
        SDL_Rect clip;
        clip.x = frame * width;
        clip.y = 0;
        clip.w = width;
        clip.h = height;

        // Screen destiny
        SDL_Rect dst;
        dst.x = x;
        dst.y = y;
        dst.w = width;
        dst.h = height;

        SDL_RenderCopy(renderer, sheet, &clip, &dst);
    }
};
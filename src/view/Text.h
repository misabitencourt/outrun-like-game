#include <string>
#include <map>

class Text {
    public:
        int id;
        int x;
        int y;
        int size;
        int transitionSpeed = 1;
        int transitionToX = -1;
        int transitionToY = -1;
        bool modified = true;
        bool rendered = false;
        TTF_Font* font;
        SDL_Surface* textSurface;
        std::string fontFile;
        std::string content;
        SDL_Color color = { 255, 255, 255 };
        SDL_Color backgroundColor = { 0, 0, 0 };
        SDL_Surface * surface;
        SDL_Texture * texture;

    void load() {
        font = TTF_OpenFont("resources/fonts/arial.ttf", 25);
        if (font == nullptr) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
        }
    }

    void render(SDL_Renderer *renderer) {
        surface = TTF_RenderText_Solid(font, content.c_str(), color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        int temp_w, temp_h;
        SDL_QueryTexture(texture, NULL, NULL, &temp_w, &temp_h);
        SDL_Rect textLocation = { x, y, temp_w, temp_h };
        SDL_RenderCopy(renderer, texture, NULL, &textLocation);

        if (transitionToX > -1) {
            if (x == transitionToX) {
                transitionToX = -1;
            }
            x = transitionToX > x ? (transitionSpeed * -1) : transitionSpeed;
        }

        if (transitionToY > -1) {
            if (x == transitionToY) {
                transitionToY = -1;
            }
            x = transitionToY > x ? (transitionSpeed * -1) : transitionSpeed;
        }

        rendered = true;
    }

    void clear() {
        if (!rendered) {
            return;
        }
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
};
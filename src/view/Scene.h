#include <list>

class Scene {
    public:
        std::list<Sprite> sprites;
        std::list<Text> texts;
        static const int STATE_MAIN_MENU = 1;
        bool upPressed;
        bool downPressed;
        bool leftPressed;
        bool rightPressed;
        bool actionPressed;

    private:
        int menuState;

    void load(SDL_Renderer *renderer) {
        std::list<Sprite>::iterator it;
        for (it = sprites.begin(); it != sprites.end(); ++it){
            it->load(renderer);
        }
        
        std::list<Text>::iterator it2;
        for (it2 = texts.begin(); it2 != texts.end(); ++it2){
            it2->load();
        }
    }

    void render(SDL_Renderer *renderer) {
        std::list<Sprite>::iterator it;
        for (it = sprites.begin(); it != sprites.end(); ++it){
            it->render(renderer);
        }
        
        std::list<Text>::iterator it2;
        for (it2 = texts.begin(); it2 != texts.end(); ++it2){
            it2->render(renderer);
        }
    }

    int calc(int gameState) {
        switch (gameState) {
            case (Scene::STATE_MAIN_MENU):
                return calcMainMenu();
                break;
        }

        return gameState;
    }

    private:

    int calcMainMenu() {
        std::list<Sprite>::iterator it;
        for (it = sprites.begin(); it != sprites.end(); ++it){
            if (it->id == Entities::MAIN_MENU_CAR) {
                it->y += 1;
                if (it->y == 303) {
                    it->y = 300;
                }
                continue;
            }
        }

        return Scene::STATE_MAIN_MENU;
    }
};
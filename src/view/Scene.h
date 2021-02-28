#include <list>

const int OUTRUN_MAIN_MENU_OPT_1 = 0;
const int OUTRUN_MAIN_MENU_OPT_2 = 1;
const int OUTRUN_MAIN_MENU_OPT_3 = 2;

const int OUTRUN_IN_GAME = 3;

class Scene {
    public:
        std::list<Sprite> sprites;
        std::list<Text> texts;
        static const int STATE_MAIN_MENU = OUTRUN_MAIN_MENU_OPT_1;
        static const int STATE_INSTRUCTIONS = OUTRUN_MAIN_MENU_OPT_2;
        static const int STATE_EXIT = OUTRUN_MAIN_MENU_OPT_3;
        static const int IN_GAME_SCENE = OUTRUN_IN_GAME;
        bool upPressed;
        bool downPressed;
        bool leftPressed;
        bool rightPressed;
        bool actionPressed;
        bool enterPressed;
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

            case (Scene::STATE_INSTRUCTIONS):
                return calcInstructions();
                break;

            case (Scene::IN_GAME_SCENE):
                return calcInGame();
                break;
        }

        return gameState;
    }

    private:

    int calcInGame() {
        return Scene::IN_GAME_SCENE;
    }

    int calcMainMenu() {
        std::list<Sprite>::iterator it;
        std::list<Text>::iterator itTxt;
        for (it = sprites.begin(); it != sprites.end(); ++it) {
            if (it->id == Entities::MAIN_MENU_CAR) {
                it->y += 1;
                if (it->y == 303) {
                    it->y = 300;
                }
                continue;
            }            
        }

        for (itTxt = texts.begin(); itTxt != texts.end(); ++itTxt) {
            if (itTxt->id == Entities::MAIN_MENU_ARROW) {
                // Menu arrow target
                int target;
                switch (menuState) {
                    case OUTRUN_MAIN_MENU_OPT_1:
                        if (itTxt->y != SceneConstants::SCENE_MAIN_MENU_MENU_START) {
                            itTxt->y += itTxt->y < SceneConstants::SCENE_MAIN_MENU_MENU_START ? 1 : -1;
                        }
                        if (enterPressed) {
                            return IN_GAME_SCENE;
                        }
                        break;
                    case OUTRUN_MAIN_MENU_OPT_2:
                        target = SceneConstants::SCENE_MAIN_MENU_MENU_START + SceneConstants::SCENE_MAIN_MENU_MENU_SPACING;
                        if (itTxt->y != target) {
                            itTxt->y += itTxt->y < target ? 1 : -1;
                        }
                        if (enterPressed) {
                            return STATE_INSTRUCTIONS;
                        }
                        break;
                    case OUTRUN_MAIN_MENU_OPT_3:
                        target = SceneConstants::SCENE_MAIN_MENU_MENU_START + (SceneConstants::SCENE_MAIN_MENU_MENU_SPACING * 2);
                        if (itTxt->y != target) {
                            itTxt->y += itTxt->y < target ? 1 : -1;
                        }
                        if (enterPressed) {
                            return IN_GAME_SCENE;
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        // Menu arrows
        if (upPressed) {
            menuState -= 1;
        } else if (downPressed) {
            menuState += 1;
        }

        // Circular menu
        if (menuState < OUTRUN_MAIN_MENU_OPT_1) {
            menuState = OUTRUN_MAIN_MENU_OPT_3;
        } else if (menuState > OUTRUN_MAIN_MENU_OPT_3) {
            menuState = OUTRUN_MAIN_MENU_OPT_1;
        }

        return Scene::STATE_MAIN_MENU;
    }


    int calcInstructions() {
        if (enterPressed) {
            return STATE_MAIN_MENU;
        }

        return Scene::STATE_INSTRUCTIONS;
    }
};
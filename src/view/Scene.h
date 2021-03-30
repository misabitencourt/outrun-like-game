#include <list>

const int OUTRUN_MAIN_MENU_OPT_1 = 0;
const int OUTRUN_MAIN_MENU_OPT_2 = 1;
const int OUTRUN_MAIN_MENU_OPT_3 = 2;

const int OUTRUN_IN_GAME = 3;

const unsigned int SPEED_DELAY = 50;

class Scene {
    public:
        TrackBuilder trackBuilder;
        std::list<Sprite> sprites;
        std::list<Text> texts;
        std::list<Tileset> tilesets;
        std::list<Line> lines;
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

        std::list<Tileset>::iterator it3;
        for (it3 = tilesets.begin(); it3 != tilesets.end(); ++it3){
            it3->load(renderer);
        }
    }

    void render(SDL_Renderer *renderer) {
        std::list<Line>::iterator it4;
        for (it4 = lines.begin(); it4 != lines.end(); ++it4) {
            SDL_SetRenderDrawColor(renderer, it4->colorR, it4->colorG, it4->colorB, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(renderer, it4->x, it4->y, it4->x2, it4->y2);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        }

        std::list<Tileset>::iterator it3;
        for (it3 = tilesets.begin(); it3 != tilesets.end(); ++it3) {
            it3->render(renderer);
        }
        
        std::list<Sprite>::iterator it;
        for (it = sprites.begin(); it != sprites.end(); ++it) {
            it->render(renderer);
        }
        
        std::list<Text>::iterator it2;
        for (it2 = texts.begin(); it2 != texts.end(); ++it2) {
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
        int speed;
        int realSpeed;
        int topSpeed;
        int trackTraveled;
        std::list<Sprite>::iterator itSprites;
        for (itSprites = sprites.begin(); itSprites != sprites.end(); ++itSprites) {

            /**
             * Car calc 
             */
            if (itSprites->id == Entities::MAIN_MENU_CAR) {
                // Var extracting
                speed = itSprites->state[SCENE_GAME_CAR_SPEED];
                topSpeed = itSprites->state[SCENE_GAME_CAR_TOPSPEED];
                if (!topSpeed) {
                    topSpeed = itSprites->state[SCENE_GAME_CAR_TOPSPEED] = 90;
                }

                // Speed force
                if (upPressed) {
                    speed += 200;
                } else {
                    speed -= 3;
                    speed = speed < 0 ? 0 : speed;
                }

                // Lowspeed and stop bouncing animation
                if (speed > 10) {
                    itSprites->y = 370;
                } else {
                    itSprites->y += 1;
                    if (itSprites->y == 373) {
                        itSprites->y = 370;
                    }
                }

                // Real speed displayed
                realSpeed = speed/500;

                // Top speed limit
                if (realSpeed > topSpeed) {
                    speed -= 450;
                    realSpeed = speed/500;               
                }

                itSprites->state[SCENE_GAME_CAR_SPEED] = speed;
                continue;
            }            
        }

        std::list<Text>::iterator itTxt;
        for (itTxt = texts.begin(); itTxt != texts.end(); ++itTxt) {
            if (itTxt->id == Entities::IN_GAME_VELOCIMETER) {
                itTxt->content = std::to_string(realSpeed);
            }
        }


        std::list<Tileset>::iterator itTilesets;
        for (itTilesets = tilesets.begin(); itTilesets != tilesets.end(); ++itTilesets) {
            // Track
            if (itTilesets->id == Entities::HORIZON) {
                unsigned short int trackState = trackBuilder.getTrackState(TRACKS_DEFAULT_TRACK, 0);
                trackTraveled = itTilesets->state[SCENE_GAME_TRACK_TRAVELED];
                switch (trackState)
                {
                    case 1:                        
                        break;
                    
                    default:
                        unsigned short int zebra = 0;
                        unsigned short int zebraApply = 0;
                        if (lines.empty()) {
                            for (int y=160; y<480; y++) {
                                // Stripe height=5, horizonHeight=160, screenHeight=480, screenWidth=640
                                Line offroadLine;
                                Line roadLine;
                                
                                offroadLine.x = 0;
                                offroadLine.y = y;
                                offroadLine.x2 = 640;
                                offroadLine.y2 = y;

                                roadLine.x = 320 - (y/2);
                                roadLine.y = y;
                                roadLine.x2 = 320 + (y/2);
                                roadLine.y2 = y;

                                zebraApply++;
                                if (zebraApply == 34) {
                                    zebraApply = 0;
                                    zebra = zebra ? 0 : 1;
                                }
                                int offroadR=80, offroadG=zebra ? 150 : 120, offroadB=80;
                                int roadColor=zebra ? 20 : 50;

                                offroadLine.colorR = offroadR;
                                offroadLine.colorG = offroadG;
                                offroadLine.colorB = offroadB;

                                roadLine.colorR = roadColor;
                                roadLine.colorG = roadColor;
                                roadLine.colorB = roadColor;

                                lines.push_back(offroadLine);
                                lines.push_back(roadLine);
                            }
                        } else {
                            std::list<Line>::iterator itLines;
                            int y;
                            for (itLines = lines.begin(); itLines != lines.end(); ++itLines) {
                                // TODO running animation
                            }
                        }
                        
                        break;
                }
            }
        }

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
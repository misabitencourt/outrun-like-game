#include <string>
const unsigned int SCENE_MAIN_MENU = 0;


class SceneBuilder {
    public:
        static Scene create(int type) {
            Scene scene;
            switch (type) {
                case 0:
                    Text title = SceneBuilder::createDefaultText("CAR RACE GAME", 235, 100);
                    scene.texts.push_back(title);
                    
                    Text arrow = SceneBuilder::createDefaultText(">>", SceneConstants::SCENE_MAIN_MENU_MENU_ALIGN-33, SceneConstants::SCENE_MAIN_MENU_MENU_START);
                    arrow.id = Entities::MAIN_MENU_ARROW;
                    scene.texts.push_back(arrow);

                    Text menuOpt1 = SceneBuilder::createDefaultText("Start game", SceneConstants::SCENE_MAIN_MENU_MENU_ALIGN, SceneConstants::SCENE_MAIN_MENU_MENU_START);
                    scene.texts.push_back(menuOpt1);

                    Text menuOpt2 = SceneBuilder::createDefaultText("Instructions", SceneConstants::SCENE_MAIN_MENU_MENU_ALIGN, SceneConstants::SCENE_MAIN_MENU_MENU_START + SceneConstants::SCENE_MAIN_MENU_MENU_SPACING);
                    scene.texts.push_back(menuOpt2);

                    Text menuOpt3 = SceneBuilder::createDefaultText("Quit", SceneConstants::SCENE_MAIN_MENU_MENU_ALIGN, SceneConstants::SCENE_MAIN_MENU_MENU_START + (SceneConstants::SCENE_MAIN_MENU_MENU_SPACING * 2));
                    scene.texts.push_back(menuOpt3);

                    Sprite car;
                    car.id = Entities::MAIN_MENU_CAR;
                    car.frame = 4;
                    car.frameSpeed = 1;
                    car.height = 100;
                    car.width = 95;
                    car.x = 235;
                    car.y = 300;
                    car.image = "kart.png";
                    scene.sprites.push_front(car);

                    return scene;
            }
            return scene;
        }

        static Text createDefaultText(std::string content, int x, int y) {
            Text text;
            text.fontFile = "arial.ttf";
            text.size = 12;
            text.x = x;
            text.y = y;
            text.content = content;
            return text;
        }
};

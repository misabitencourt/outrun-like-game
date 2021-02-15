#include <string>
#include <sys/time.h>

class MainWindow {
    public:
        int width;
        int height;
        int x;
        int y;
        std::string title;
        SDL_Window *win;
        SDL_Renderer *ren;
        Scene scene;


    void init() {
        SDL_Init(SDL_INIT_EVERYTHING);
        Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
        Mix_AllocateChannels(4);
        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
            std::cout << "Image Error";
            SDL_Quit();
            return;
        }
        TTF_Init();

        // Window instance
        SDL_Window *win = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
        if (win == nullptr){
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        // Renderer
        SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (ren == nullptr){
            SDL_DestroyWindow(win);
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        int gameState = Scene::STATE_MAIN_MENU;
        win = win;
        ren = ren;
        bool keepGoing = true;
        scene = SceneBuilder::create(SCENE_MAIN_MENU);
        scene.load(ren);
        SDL_Event e;
        Sound sound;
        sound.musicPath = "resources/sound/music.ogg";
        sound.load();
        sound.play();
        while(keepGoing) {
            scene.enterPressed = scene.upPressed = scene.downPressed = 
                scene.leftPressed = scene.rightPressed = false;

            while (SDL_PollEvent(&e)) {
                switch (e.type) {
                    case SDL_KEYDOWN:
                        printf( "Key release detected\n" );
                        switch (e.key.keysym.sym) {
                            case SDLK_LEFT:
                                scene.leftPressed = true;
                                break;
                            case SDLK_RIGHT:
                                scene.rightPressed = true;
                                break;
                            case SDLK_UP:
                                scene.upPressed = true;
                                break;
                            case SDLK_DOWN:
                                scene.downPressed = true;
                                break;
                            case SDLK_SPACE:
                                scene.enterPressed = true;
                                break;
                            case SDLK_KP_ENTER:
                                scene.enterPressed = true;
                                break;
                            case SDLK_RETURN:
                                scene.enterPressed = true;
                                break;
                            case SDLK_ESCAPE:
                                keepGoing = false;
                                break;
                            default:
                                break;
                        }
                        break;

                    default:
                        break;
                }

                // Quit
                if (e.type == SDL_QUIT){
                    keepGoing = false;
                }

                
                break;
            }
            SDL_RenderClear(ren);
            struct timeval tp;
            gettimeofday(&tp, NULL);
            long int start = tp.tv_usec;
            scene.render(ren);
            int newGameState = scene.calc(gameState);
            if (newGameState != gameState) {
                SDL_DestroyRenderer(ren);
                ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                scene = SceneBuilder::create(newGameState);
                scene.load(ren);
            }
            if (gameState == Scene::STATE_EXIT) {
                keepGoing = false;
            }
            gameState = newGameState;
            SDL_RenderPresent(ren);
            gettimeofday(&tp, NULL);
            long int processTime = tp.tv_usec - start;
            // Log process time
        }
    }
};


#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameMap.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 500

class Game {
public:
    static Game* getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Game();
    }

    bool init();

    void update();
    void handleEvents();
    void render();
    void quit();
    void clean();

    inline bool isRunning() const { return m_isRunning; }
    inline SDL_Renderer* getRenderer() { return renderer; }

private:
    Game() = default;
    static Game* s_Instance;
    bool m_isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
};

#endif //GAME_H
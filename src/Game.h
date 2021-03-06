#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameMap.h"
#include "StateManager.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "VoidState.h"
#include "GameOverState.h"

class PlayState;

class MenuState;

class PauseState;

class VoidState;

class GameOverState;

class Game {
public:
    static Game *getInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Game();
    }

    bool init();

    void update();

    void handleEvents();

    void render();

    void quit();

    void clean();

    inline bool isRunning() const { return m_isRunning; }

    inline SDL_Renderer *getRenderer() { return renderer; }

    inline PlayState *getPlayState() { return playState; }

    inline StateManager *getManager() { return &manager; }

    inline PauseState *getPauseState() { return pauseState; }

    inline VoidState *getVoidState() { return voidState; }

    void unsetPlayState();

    void unsetMenu();

    void unsetPause();

    void unsetVoidState();

    void startGame();

    void restartGame(int life, int coins, int score);

    void newMenu();

    void newVoidState(int life);

    void newGameOverState(int life, int coins, int sc);

    void unsetGameOverState();

private:
    Game() = default;

    static Game *s_Instance;
    bool m_isRunning{};
    SDL_Window *window{};
    SDL_Renderer *renderer{};

    StateManager manager;
    MenuState *menu{};
    PlayState *playState{};
    PauseState *pauseState{};
    VoidState *voidState{};
    GameOverState *gameOverState{};
};

#endif //GAME_H
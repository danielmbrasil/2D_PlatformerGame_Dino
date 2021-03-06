//
// Created by daniel on 17/07/2020.
//

#include "MenuState.h"
#include "Game.h"
#include "KeyboardController.h"
#include "TextureManager.h"

MenuState::MenuState() {
    // get context
    m_Context = Game::getInstance()->getRenderer();

    // set labels position
    position[0].x = 50;
    position[0].y = 260;
    position[1].x = 50;
    position[1].y = 310;

    // create new labels
    for (int i = 0; i < 2; i++)
        labels[i] = new UILabel(position[i].x, position[i].y, options[i], "minecraftBigger", white);

    TextureManager::getInstance()->loadTexture("background", "../assets/images/background.png");
}

MenuState::~MenuState() = default;

void MenuState::events() {
    int x = KeyboardController::getInstance()->getX();
    int y = KeyboardController::getInstance()->getY();

    for (int i = 0; i < 2; ++i) {
        if (x >= labels[i]->getPosition().x &&
            x <= labels[i]->getPosition().x + labels[i]->getPosition().w &&
            y >= labels[i]->getPosition().y &&
            y <= labels[i]->getPosition().y + labels[i]->getPosition().h) {
            labels[i]->clean();
            delete labels[i];
            labels[i] = new UILabel(position[i].x, position[i].y, options[i], "minecraftBigger", green);

            if (KeyboardController::getInstance()->getMouseButtonDown() && i == 0) {
                for (auto &label : labels)
                    label->clean();
                Game::getInstance()->getManager()->popState();
                Game::getInstance()->startGame();
                Game::getInstance()->unsetMenu();
                SDL_Delay(300);
            } else if (KeyboardController::getInstance()->getMouseButtonDown() && i == 1) {
                for (auto &label : labels)
                    label->clean();
                Game::getInstance()->quit();
            }
        } else {
            labels[i]->clean();
            delete labels[i];
            labels[i] = new UILabel(position[i].x, position[i].y, options[i], "minecraftBigger", white);
        }
    }
}

void MenuState::update(float dt) {
    //GameState::update(dt);
}

void MenuState::render() {
    SDL_SetRenderDrawColor(m_Context, 0, 0, 0, 0);
    SDL_RenderClear(m_Context);

    TextureManager::getInstance()->draw("background", (int)(Camera::getInstance()->getPosition().x), 0, 900, 480);

    for (auto &label : labels)
        label->draw();

    SDL_RenderPresent(m_Context);
}

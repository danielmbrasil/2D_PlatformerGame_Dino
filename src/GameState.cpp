//
// Created by daniel on 17/07/2020.
//

#include "GameState.h"

GameState::GameState() {
    manager = nullptr;
}

GameState::~GameState() {}

void GameState::setManager(StateManager *m) {
    manager = m;
}

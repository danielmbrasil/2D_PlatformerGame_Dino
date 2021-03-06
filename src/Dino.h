//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef Dino_H
#define Dino_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"

#define JUMP_TIME 16.6f
#define JUMP_FORCE 19.f

class Collider;

class Dino : public Character {
public:
    explicit Dino(Properties *properties);

    ~Dino() override;

    void draw() override;

    void clean() override;

    void update(float delta) override;

    inline void setLife(int x) {
        life = x;
    }

    inline void loseLife() {
        if (life != 0)
            life--;
    }

    inline int getLife() {
        return life;
    }

    SDL_Rect getCollider();

    inline bool getDinoHitFirst() { return dinoHitFirst; }

    inline int getCoinsCollected() { return collectedCoins; }

    inline void setCoins(int x) {
        collectedCoins = x;
    }

    inline int getScore() { return score; }

    inline void setScore(int sc) {
        score = sc;
    }

private:
    Animation *animation;
    RigidBody *rigidBody;

    bool isJumping{};
    bool isOnGround{};

    float jumpTime;
    float jumpForce;

    Collider *collider;
    Vector2D lastPosition;

    int life{};
    bool dinoHitFirst;

    int collectedCoins;
    int score;
};


#endif //Dino_H

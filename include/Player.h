#ifndef EXAM_PLAYER_H
#define EXAM_PLAYER_H

#include <SDL_mixer.h>
#include "GameObject.h"
#include "MovableObject.h"
#include "EntityAnimator.h"
#include <thread>
#include <future>


enum Sound {
    EAT_PELLET, EAT_POWER_PELLET, DEATH, EAT_FRUIT, EAT_GHOST, TEST
};

class Player : public MovableObject {
public:
    Player(SDL_Texture *texturePtr, int x, int y, int id, int movementSpeed, EntityAnimator animator) :
            MovableObject(texturePtr, x, y, id, movementSpeed), m_animator(animator) {
        movementChange.x = 0;
        movementChange.y = 0;
        highScore = readHighScore();

        sounds = {{EAT_PELLET,       Mix_LoadWAV("../resources/sounds/pacman/pacman_chomp.wav")},
                  {EAT_POWER_PELLET, Mix_LoadWAV("../resources/sounds/pacman/eat_powerpellet.mp3")},
                  {EAT_FRUIT,        Mix_LoadWAV("../resources/sounds/pacman/pacman_eatfruit.wav")},
                  {EAT_GHOST,        Mix_LoadWAV("../resources/sounds/pacman/pacman_eatghost.wav")},
                  {DEATH,            Mix_LoadWAV("../resources/sounds/pacman/pacman_death.wav")},
                  {TEST,             Mix_LoadWAV("../resources/sounds/game/pacman_beginning.wav")},
        };
    }

    std::map<Sound, Mix_Chunk *> sounds;


    void reset() override;

    void update() override;

    TYPE getType() override;

    Direction direction = UP;
    EntityAnimator m_animator;
    int points = 0;
    int highScore = 0;
    int newHighScore = 0;
    int lives = 3;

    void playSound(Sound sound, int channel = -1);

    void writeHighScore(int score);

    EntityAnimator deathAnimator = EntityAnimator({{UP,
                                                           {
                                                                   "../resources/img/pacman/pacman_death_1.png",
                                                                   "../resources/img/pacman/pacman_death_2.png",
                                                                   "../resources/img/pacman/pacman_death_3.png",
                                                                   "../resources/img/pacman/pacman_death_4.png",
                                                                   "../resources/img/pacman/pacman_death_5.png",
                                                                   "../resources/img/pacman/pacman_death_6.png",
                                                                   "../resources/img/pacman/pacman_death_7.png",
                                                                   "../resources/img/pacman/pacman_death_8.png",
                                                                   "../resources/img/pacman/pacman_death_9.png"
                                                           }
                                                   },
                                                   {DOWN,
                                                           {
                                                                   "../resources/img/pacman/pacman_death_1.png",
                                                                   "../resources/img/pacman/pacman_death_2.png",
                                                                   "../resources/img/pacman/pacman_death_3.png",
                                                                   "../resources/img/pacman/pacman_death_4.png",
                                                                   "../resources/img/pacman/pacman_death_5.png",
                                                                   "../resources/img/pacman/pacman_death_6.png",
                                                                   "../resources/img/pacman/pacman_death_7.png",
                                                                   "../resources/img/pacman/pacman_death_8.png",
                                                                   "../resources/img/pacman/pacman_death_9.png"
                                                           }
                                                   },
                                                   {LEFT,
                                                           {
                                                                   "../resources/img/pacman/pacman_death_1.png",
                                                                   "../resources/img/pacman/pacman_death_2.png",
                                                                   "../resources/img/pacman/pacman_death_3.png",
                                                                   "../resources/img/pacman/pacman_death_4.png",
                                                                   "../resources/img/pacman/pacman_death_5.png",
                                                                   "../resources/img/pacman/pacman_death_6.png",
                                                                   "../resources/img/pacman/pacman_death_7.png",
                                                                   "../resources/img/pacman/pacman_death_8.png",
                                                                   "../resources/img/pacman/pacman_death_9.png"
                                                           }
                                                   },
                                                   {RIGHT,
                                                           {
                                                                   "../resources/img/pacman/pacman_death_1.png",
                                                                   "../resources/img/pacman/pacman_death_2.png",
                                                                   "../resources/img/pacman/pacman_death_3.png",
                                                                   "../resources/img/pacman/pacman_death_4.png",
                                                                   "../resources/img/pacman/pacman_death_5.png",
                                                                   "../resources/img/pacman/pacman_death_6.png",
                                                                   "../resources/img/pacman/pacman_death_7.png",
                                                                   "../resources/img/pacman/pacman_death_8.png",
                                                                   "../resources/img/pacman/pacman_death_9.png"
                                                           }
                                                   },


                                                  });
private:
    SDL_Point movementChange;

    int readHighScore();

    bool positionIsValid(SDL_Rect &possiblePosition);

    void determineDirection(const SDL_Rect &possiblePosition);

};


#endif

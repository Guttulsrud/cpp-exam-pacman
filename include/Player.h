#ifndef EXAM_PLAYER_H
#define EXAM_PLAYER_H

#include <SDL_mixer.h>
#include "GameObject.h"
#include "Movable.h"
#include "EntityAnimator.h"
#include <thread>
#include <future>


enum Sound {
    EAT_PELLET, EAT_POWER_PELLET, DEATH, EAT_FRUIT, EAT_GHOST, INTRO, MAP_COMPLETED, GHOST_RETURN
};

class Player : public Movable {
public:
    Player(SDL_Texture *texturePtr, int x, int y, int movementSpeed) :
            Movable(texturePtr, x, y, movementSpeed){
        movementChange.x = 0;
        movementChange.y = 0;

        sounds = {{EAT_PELLET,       Mix_LoadWAV("../resources/sounds/pacman/pacman_chomp.wav")},
                  {EAT_POWER_PELLET, Mix_LoadWAV("../resources/sounds/pacman/eat_powerpellet.mp3")},
                  {EAT_FRUIT,        Mix_LoadWAV("../resources/sounds/pacman/pacman_eatfruit.wav")},
                  {EAT_GHOST,        Mix_LoadWAV("../resources/sounds/pacman/pacman_eatghost.wav")},
                  {DEATH,            Mix_LoadWAV("../resources/sounds/pacman/pacman_death.wav")},
                  {INTRO,            Mix_LoadWAV("../resources/sounds/game/pacman_beginning.wav")},
                  {MAP_COMPLETED,    Mix_LoadWAV("../resources/sounds/pacman/pacman_extrapac.wav")},
                  {GHOST_RETURN,    Mix_LoadWAV("../resources/sounds/ghosts/ghost_return_to_home.mp3")},
        };
    }

    std::map<Sound, Mix_Chunk *> sounds;


    void reset() override;

    void update() override;
    void die();

    Direction m_direction = UP;

    void playSound(Sound sound, int channel = -1);
    EntityAnimator m_animator = EntityAnimator({{UP,
                                                        {
                                                                "../resources/img/pacman/base.png",
                                                                "../resources/img/pacman/medium-open-up.png",
                                                                "../resources/img/pacman/large-open-up.png",
                                                                "../resources/img/pacman/medium-open-up.png"
                                                        }
                                                },
                                                {DOWN,
                                                        {
                                                                "../resources/img/pacman/base.png",
                                                                "../resources/img/pacman/medium-open-down.png",
                                                                "../resources/img/pacman/large-open-down.png",
                                                                "../resources/img/pacman/medium-open-down.png"
                                                        }
                                                },
                                                {LEFT,
                                                        {
                                                                "../resources/img/pacman/base.png",
                                                                "../resources/img/pacman/medium-open-left.png",
                                                                "../resources/img/pacman/large-open-left.png",
                                                                "../resources/img/pacman/medium-open-left.png"
                                                        }
                                                },
                                                {RIGHT,
                                                        {
                                                                "../resources/img/pacman/base.png",
                                                                "../resources/img/pacman/medium-open-right.png",
                                                                "../resources/img/pacman/large-open-right.png",
                                                                "../resources/img/pacman/medium-open-right.png"
                                                        }
                                                }});

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
                                                   }
                                                  });
private:
    SDL_Point movementChange;


    void updateDirection();

    SDL_Point updateMovementDirection();

    bool willCollideWithWall(SDL_Rect& possiblePosition);

    SDL_Rect moveOneFrame(SDL_Point potentialChange);
};


#endif

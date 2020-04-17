#ifndef EXAM_PLAYER_H
#define EXAM_PLAYER_H

#include <SDL_mixer.h>
#include "GameObject.h"
#include "Movable.h"
#include "EntityAnimator.h"
#include <thread>
#include <future>


class Player : public Movable {
public:
    Player(int x, int y, int movementSpeed) :
            Movable(x, y, movementSpeed) {
        m_movementChange.x = 0;
        m_movementChange.y = 0;
    }

    void reset() override;

    void update() override;

    void die();

    Direction m_direction = UP;

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

    void updateDirection();

    SDL_Point updateMovementDirection();

    SDL_Rect moveOneFrame(SDL_Point potentialChange);

    SDL_Point m_movementChange;

};


#endif

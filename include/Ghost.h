#ifndef EXAM_GHOST_H
#define EXAM_GHOST_H

#include "GameObject.h"
#include "Movable.h"
#include "EntityAnimator.h"
#include <map>
class Ghost : public Movable {
public:
    Ghost(SDL_Texture *texturePtr, int x, int y, int movementSpeed, EntityAnimator animator) :
            Movable(texturePtr, x, y, movementSpeed),
            m_animator(animator) {
        spawn.x = x;
        spawn.y = y;
    }

    int difficulty = 4;
    Direction direction = RIGHT;
    std::vector<Direction> prevDirections;
    bool eatable = false;
    bool eatableStateEnd = false;
    bool dead = false;
    bool switchedToEatable = false;
    EntityAnimator m_animator;
    SDL_Point spawn;


    SDL_TimerID eatableStateEndTimer;
    SDL_TimerID ghostReviveTimer;
    static Uint32 eatableStateEndCallback(Uint32 interval, void* param);
    static Uint32 reviveGhostCallback(Uint32 interval, void* param);

    void update() override;
    void reset() override;
    TYPE getType() override;
    Direction getDirectionToPoint(const std::map<Direction, SDL_Rect> &possibleDirections) const;



    EntityAnimator powerPelletStateAnimator = EntityAnimator({{UP,
                                                                      {
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png"
                                                                      }
                                                              },
                                                              {DOWN,
                                                                      {

                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png"
                                                                      }
                                                              },
                                                              {LEFT,
                                                                      {
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png"
                                                                      }
                                                              },
                                                              {RIGHT,
                                                                      {
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png"
                                                                      }
                                                              }});

    EntityAnimator powerPelletStateEndAnimator = EntityAnimator({{UP,
                                                                      {
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_2.png"
                                                                      }
                                                              },
                                                              {DOWN,
                                                                      {
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_2.png"
                                                                      }
                                                              },
                                                              {LEFT,
                                                                      {
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_2.png"
                                                                      }
                                                              },
                                                              {RIGHT,
                                                                      {
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_2.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_flash_2.png"
                                                                      }
                                                              }});
    EntityAnimator deadAnimator = EntityAnimator({{UP,
                                                          {
                                                                  "../resources/img/ghosts/eyes_N.png"
                                                          }
                                                  },
                                                  {DOWN,
                                                          {
                                                                  "../resources/img/ghosts/eyes_S.png"
                                                          }
                                                  },
                                                  {LEFT,
                                                          {
                                                                  "../resources/img/ghosts/eyes_W.png"
                                                          }
                                                  },
                                                  {RIGHT,
                                                          {
                                                                  "../resources/img/ghosts/eyes_E.png"
                                                          }
                                                  }});
};

#endif

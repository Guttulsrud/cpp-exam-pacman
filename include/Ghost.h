#ifndef EXAM_GHOST_H
#define EXAM_GHOST_H

#include "GameObject.h"
#include "MovableObject.h"
#include "EntityAnimator.h"
#include <map>

class Ghost : public MovableObject {
public:
    Ghost(SDL_Texture *texturePtr, int x, int y, int id, int movementSpeed, EntityAnimator animator) :
            MovableObject(texturePtr, x, y, id, movementSpeed),
            m_animator(animator) {}

    int difficulty = 4;
    Direction direction = RIGHT;
    std::vector<Direction> prevDirections;
    bool powerPelletState = false;
    bool dead = false;
    bool switchedToPowerPelletState = false;
    EntityAnimator m_animator;

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

    void update() override;
    void reset() override;

    TYPE getType() override;

    Direction getDirectionToPlayer(const std::map<Direction, SDL_Rect> &possibleDirections) const;

};

#endif //EXAM_GHOST_H

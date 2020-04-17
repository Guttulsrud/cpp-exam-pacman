#ifndef EXAM_GHOST_H
#define EXAM_GHOST_H

#include "GameObject.h"
#include "Movable.h"
#include "EntityAnimator.h"
#include <map>

class Ghost : public Movable {
public:
    Ghost(int x, int y, int movementSpeed, EntityAnimator animator) :
            Movable(x, y, movementSpeed),
            m_animator(animator) {
        spawn.x = x;
        spawn.y = y;

        respawnPoint.x = 30*15;
        respawnPoint.y = 30*14+15;
        respawnPoint.w = 60;
        respawnPoint.h = 60;

    }

    void reset() override;
    void powerPelletState();
    void die();
    void update() override;

    bool eatable = false;
    bool dead = false;
private:
    SDL_Rect respawnPoint;
    int difficulty = 4;
    Direction direction = RIGHT;
    std::vector<Direction> prevDirections;
    bool eatableStateEnd = false;
    bool switchedToEatable = false;
    EntityAnimator m_animator;
    SDL_Point spawn;

    SDL_TimerID eatableStateEndTimer;
    SDL_TimerID ghostReviveTimer;

    static Uint32 eatableStateEndCallback(Uint32 interval, void *param);

    static Uint32 reviveGhostCallback(Uint32 interval, void *param);

    Direction getDirectionToPoint(std::map<Direction, SDL_Rect> &possibleDirections) const;

    static int getRandomNumberInRange(int begin, int end);

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

    std::map<Direction, SDL_Rect> getDirectionsMap();

    void updateValidMoves(std::map<Direction, SDL_Rect> &directions, std::map<Direction, SDL_Rect> &possibleDirections,
                          std::vector<Direction> &possibleDirectionsVector) const;

    void decideMove(std::map<Direction, SDL_Rect> &directions, std::map<Direction, SDL_Rect> &possibleDirections,
                    std::vector<Direction> &possibleDirectionsVector);

    void animateState();

    void maintainPositionRelativeToTiles();
};

#endif

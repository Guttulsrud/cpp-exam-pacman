#ifndef EXAM_GHOST_H
#define EXAM_GHOST_H

#include "GameObject.h"
#include "Movable.h"
#include "EntityAnimator.h"
#include <map>

class Ghost : public Movable {
public:
    Ghost(int x, int y, int movementSpeed, EntityAnimator animator) : Movable(x, y, movementSpeed),
                                                                      m_animator(animator) {
        m_spawn.x = x;
        m_spawn.y = y;
        m_respawnPoint.x = 30 * 15;
        m_respawnPoint.y = 30 * 14 + 15;
        m_respawnPoint.w = 60;
        m_respawnPoint.h = 60;
    }

    void reset() override;

    void powerPelletState();

    void die();

    void update() override;

    bool m_eatable = false;
    bool m_dead = false;
private:
    int m_difficulty = 4;
    bool m_eatableStateEnd = false;
    bool m_switchedToEatable = false;
    EntityAnimator m_animator;
    SDL_Point m_spawn;
    SDL_TimerID m_eatableStateEndTimer;
    SDL_TimerID m_ghostReviveTimer;
    SDL_Rect m_respawnPoint;
    Direction m_direction = Direction::RIGHT;
    std::vector<Direction> m_prevDirections;

    static Uint32 eatableStateEndCallback(Uint32 interval, void *param);

    static Uint32 reviveGhostCallback(Uint32 interval, void *param);

    Direction getDirectionToPoint(std::map<Direction, SDL_Rect> &possibleDirections) const;

    static int getRandomNumberInRange(int begin, int end);

    EntityAnimator powerPelletStateAnimator = EntityAnimator({{Direction::UP,
                                                                      {
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png"
                                                                      }
                                                              },
                                                              {Direction::DOWN,
                                                                      {

                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png"
                                                                      }
                                                              },
                                                              {Direction::LEFT,
                                                                      {
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png"
                                                                      }
                                                              },
                                                              {Direction::RIGHT,
                                                                      {
                                                                              "../resources/img/ghosts/ghost_badTripState_1.png",
                                                                              "../resources/img/ghosts/ghost_badTripState_2.png"
                                                                      }
                                                              }});

    EntityAnimator powerPelletStateEndAnimator = EntityAnimator({{Direction::UP,
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
                                                                 {Direction::DOWN,
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
                                                                 {Direction::LEFT,
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
                                                                 {Direction::RIGHT,
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
    EntityAnimator deadAnimator = EntityAnimator({{Direction::UP,
                                                          {
                                                                  "../resources/img/ghosts/eyes_N.png"
                                                          }
                                                  },
                                                  {Direction::DOWN,
                                                          {
                                                                  "../resources/img/ghosts/eyes_S.png"
                                                          }
                                                  },
                                                  {Direction::LEFT,
                                                          {
                                                                  "../resources/img/ghosts/eyes_W.png"
                                                          }
                                                  },
                                                  {Direction::RIGHT,
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

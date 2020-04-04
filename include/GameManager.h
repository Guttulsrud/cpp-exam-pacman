#ifndef EXAM_GAMEMANAGER_H
#define EXAM_GAMEMANAGER_H


class GameManager {
public:
    ~GameManager();

    static GameManager &getInstance(){
        static GameManager instance;
        return instance;
    }
/*
    void pointScore(int oldPoints, int pelletPoint){
        if()
    }
*/
    //TODO: Adde ting fra Game og over hit, pacman, andre renders, etc.


private:
    GameManager() = default;
};


#endif //EXAM_GAMEMANAGER_H
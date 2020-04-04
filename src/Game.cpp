#include "../include/Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Renderer *Game::renderer = nullptr;


void Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen) {

    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    }
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {


        TTF_Init();

        TTF_Font * font = TTF_OpenFont("../resources/fonts/arial.ttf", 20);
        SDL_Color white = {255, 0, 255};
        if(font == NULL) {

            std::cout << "no font!!" << std::endl;
        }

        SDL_Surface * message = TTF_RenderText_Solid(font, "hellooowoooooooooooo", white);





        std::cout << "Initializing.." << std::endl;
        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

        if (window) {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, flags);

        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;
    }

    addGameObject(std::make_shared<Player>(
            TextureManager::loadTexture("../resources/img/pacman-closed.png"),
            60, 60, 60, 60, 0, 2));

    ///TODO: Draw with map class
    addGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghost_red.png"),
            60, 60, 60, 60, 0, 2));

    addGameObject(
            std::make_shared<VoidWarp>(TextureManager::loadTexture("../resources/img/red.jpg"), 60, 60, -80, 480, 2,
                                       0));
    addGameObject(
            std::make_shared<VoidWarp>(TextureManager::loadTexture("../resources/img/red.jpg"), 60, 60, 1000, 480, 2,
                                       1));

    addMap(std::make_shared<Map>());

}


void removeGameObjects(std::vector<std::shared_ptr<GameObject>> &objects) {

    objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                           [](const std::shared_ptr<GameObject> &pellet) {
                               return pellet->getType() == "Pellet" && dynamic_cast<Pellet *>(pellet.get())->eaten;
                           }),
            objects.end());
}


void Game::update() {
    std::vector<std::shared_ptr<GameObject>> &objects = Game::getGameObjects();

    for (auto &gameObject : objects) {
        gameObject->update();
    }

    removeGameObjects(objects);


}

int test = 0;

void Game::render() {
    SDL_RenderClear(renderer);
    for (auto &gameObject : Game::getGameObjects()) {
        gameObject->render();
    }

    //todo: Player animation below. Needs to be a function
    test++;
    auto *player = dynamic_cast<Player *>(Game::getGameObjects()[0].get());
    SDL_Texture *altTex = player->playerClosed;
    if (test > 19) {
        player->render(altTex);
    }
    if (test > 40) {
        test = 0;
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() {

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned.." << std::endl;
}

void Game::addMap(const std::shared_ptr<Map> &m) {
    getMaps().emplace_back(m);
}

void Game::addGameObject(std::shared_ptr<GameObject> const &object) {
    getGameObjects().emplace_back(object);
}


std::vector<std::shared_ptr<Map>> &Game::getMaps() {
    return getInstance().maps;
}

std::vector<std::shared_ptr<GameObject>> &Game::getGameObjects() {
    return getInstance().gameObjects;
}

Game::~Game() {

}

void Game::removePellet(const std::shared_ptr<GameObject> &object) {
    std::vector<std::shared_ptr<GameObject>> &objects = Game::getGameObjects();


    objects.erase(
            std::remove_if(
                    objects.begin(),
                    objects.end(),
                    [object](const std::shared_ptr<GameObject> &p) { return p->m_id == object->m_id; }
            ),
            objects.end()
    );

}

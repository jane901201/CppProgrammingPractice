#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class Unit;
class UIScreen;

class Game {
public:
    Game();
    ~Game();

    bool Initialize();
    void RunLoop();
    void Shutdown();

private:
    void ProcessInput();
    void UpdateGame(); 
    void GenerateOutput();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    Unit* mPlayer;
    Unit* mDog;
    UIScreen* mUI;

    bool mIsRunning;
};
#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "Shader.h"
#include "SlashAttack.h"

class Unit;
class UIScreen;

enum class Phase
{
    Select,
    Action
};

enum class Action
{
    None,
    Attack,
    Defend
};

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

    bool IsInRect(int x, int y, const SDL_Rect& rect);
    bool mActionProcessed = false;

    SDL_Window* mWindow;
    SDL_GLContext mGLContext;
    SDL_Renderer* mRenderer;

    Unit* mPlayer;
    Unit* mDog;
    UIScreen* mUI;

    bool mIsRunning;

    Uint32 mActionStartTime;

    Phase mPhase;
    Action mPlayerAction;
    Action mDogAction;
};
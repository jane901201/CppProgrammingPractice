#include "Game.h"
#include "PlayerUnit.h"
#include "DogUnit.h"
#include "UIScreen.h"
#include <iostream>
#include <SDL/SDL_image.h>
#include <GL/glew.h>  
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <iostream>

Game::Game()
    : mWindow(nullptr), mRenderer(nullptr),
    mPlayer(nullptr), mDog(nullptr), mUI(nullptr),
    mIsRunning(true)
{
    mPhase = Phase::Select;
    mPlayerAction = Action::None;
    mDogAction = Action::None;
}

Game::~Game()
{
}

bool Game::Initialize()
{
    SDL_Init(SDL_INIT_VIDEO);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    IMG_Init(IMG_INIT_PNG);

    if (TTF_Init() == -1)
    {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return false;
    }

    // Set OpenGL attributes
    // Use the core OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    // Specify version 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Request a color buffer with 8-bits per RGBA channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);


    mWindow = SDL_CreateWindow("Battle Game", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);
    if (!mWindow)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // OpenGLコンテキスト作成
    mGLContext = SDL_GL_CreateContext(mWindow);
    if (!mGLContext)
    {
        std::cout << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
        return false;
    }

    glewExperimental = GL_TRUE;
    glewInit();

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW Init Failed" << std::endl;
        return false;
    }

    glGetError();

    glViewport(0, 0, 1024, 768);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1024, 768, 0, -1, 1); // SDL座標と同じにする
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    mPlayer = new PlayerUnit();
    mDog = new DogUnit();
    mUI = new UIScreen();

    mUI->LoadAssets();

    return true;
}

void Game::RunLoop()
{
    SDL_Event event;
    while (mIsRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                mIsRunning = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && mPhase == Phase::Select)
            {
                int mx = event.button.x;
                int my = event.button.y;

                if (IsInRect(mx, my, mUI->GetAttackButtonRect()))
                    mPlayerAction = Action::Attack;
                else if (IsInRect(mx, my, mUI->GetDefendButtonRect()))
                    mPlayerAction = Action::Defend;

                if (mPlayerAction != Action::None)
                {
                    mDogAction = (rand() % 2 == 0) ? Action::Attack : Action::Defend;

                    // ダメージ計算
                    if (mPlayerAction == Action::Attack && mDogAction != Action::Defend)
                        mDog->SetHP(mDog->GetHP() - 10);

                    if (mDogAction == Action::Attack && mPlayerAction != Action::Defend)
                        mPlayer->SetHP(mPlayer->GetHP() - 10);

                    // 行動開始時間記録
                    mActionStartTime = SDL_GetTicks();
                    mPhase = Phase::Action;
                }
            }
        }

        UpdateGame();
        GenerateOutput();
    }
}

void Game::UpdateGame()
{
    if (mPhase == Phase::Action)
    {
        Uint32 now = SDL_GetTicks();
        
        if (!mActionProcessed)
        {
            if (mPlayerAction == Action::Attack && mDogAction != Action::Defend)
                mDog->SetHP(mDog->GetHP() - 10);

            if (mDogAction == Action::Attack && mPlayerAction != Action::Defend)
                mPlayer->SetHP(mPlayer->GetHP() - 10);

            mActionProcessed = true;
        }

        if (now - mActionStartTime >= 3000) // 3秒経過したら
        {
            mPhase = Phase::Select;
            mPlayerAction = Action::None;
            mDogAction = Action::None;
            mActionProcessed = false; // 次の行動フェーズに備えてリセット
        }
        return;
    }
}

void Game::GenerateOutput()
{
    glClear(GL_COLOR_BUFFER_BIT);

    const char* phaseStr = (mPhase == Phase::Select) ? "Select Phase" : "Action Phase";
    const char* playerActStr = "";
    const char* dogActStr = "";

    if (mPhase == Phase::Action)
    {
        if (mPlayerAction == Action::Attack) playerActStr = "Player Action:Attack";
        else if (mPlayerAction == Action::Defend) playerActStr = "Player Action:Defend";

        if (mDogAction == Action::Attack) dogActStr = "Enemy Action:Attack";
        else if (mDogAction == Action::Defend) dogActStr = "Enemy Action:Defend";
    }

    // テキストやUIのOpenGL描画へ（仮対応）

    mUI->Render(mPlayer, mDog, phaseStr, playerActStr, dogActStr);

    SDL_GL_SwapWindow(mWindow); // 描画の反映
}

bool Game::IsInRect(int x, int y, const SDL_Rect& rect)
{
    return (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h);
}

void Game::Shutdown()
{
    delete mPlayer;
    delete mDog;
    delete mUI;

    SDL_GL_DeleteContext(mGLContext);
    SDL_DestroyWindow(mWindow);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
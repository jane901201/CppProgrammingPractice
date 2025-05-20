#include "Game.h"
#include "PlayerUnit.h"
#include "DogUnit.h"
#include "UIScreen.h"
#include <iostream>
#include <SDL/SDL_image.h>

Game::Game()
    : mWindow(nullptr), mRenderer(nullptr),
    mPlayer(nullptr), mDog(nullptr), mUI(nullptr),
    mIsRunning(true)
{
}

Game::~Game()
{
}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return false;
    }

    mWindow = SDL_CreateWindow("Battle Game", 100, 100, 1024, 768, 0);
    if (!mWindow)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!mRenderer)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    mPlayer = new PlayerUnit();
    mDog = new DogUnit();
    mUI = new UIScreen(mRenderer);

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
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mx = event.button.x;
                int my = event.button.y;
                SDL_Rect rect = mUI->GetAttackButtonRect();
                if (mx >= rect.x && mx <= rect.x + rect.w &&
                    my >= rect.y && my <= rect.y + rect.h)
                {
                    if (mDog->GetHP() > 0)
                        mDog->SetHP(mDog->GetHP() - 10);
                }
            }
        }

        UpdateGame();
        GenerateOutput();
    }
}

void Game::UpdateGame()
{
    // 今後行動フェーズや遅延演出などが必要になったときに拡張
}

void Game::GenerateOutput()
{
    mUI->Render(mPlayer, mDog);
}

void Game::Shutdown()
{
    delete mPlayer;
    delete mDog;
    delete mUI;

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
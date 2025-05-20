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
    mPhase = Phase::Select;
    mPlayerAction = Action::None;
    mDogAction = Action::None;
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

                    // �_���[�W�v�Z
                    if (mPlayerAction == Action::Attack && mDogAction != Action::Defend)
                        mDog->SetHP(mDog->GetHP() - 10);

                    if (mDogAction == Action::Attack && mPlayerAction != Action::Defend)
                        mPlayer->SetHP(mPlayer->GetHP() - 10);

                    // �s���J�n���ԋL�^
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

        if (now - mActionStartTime >= 3000) // 3�b�o�߂�����
        {
            mPhase = Phase::Select;
            mPlayerAction = Action::None;
            mDogAction = Action::None;
            mActionProcessed = false; // ���̍s���t�F�[�Y�ɔ����ă��Z�b�g
        }
        return;
    }
}

void Game::GenerateOutput()
{
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

    mUI->Render(mPlayer, mDog, phaseStr, playerActStr, dogActStr);
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

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
#include "UIScreen.h"
#include <SDL/SDL_image.h>
#include <iostream>

UIScreen::UIScreen(SDL_Renderer* renderer)
    : mRenderer(renderer),
    mBackground(nullptr),
    mDogTexture(nullptr),
    mFarmerTexture(nullptr),
    mButtonTexture(nullptr)
{
    LoadAssets();
}

UIScreen::~UIScreen()
{
    SDL_DestroyTexture(mBackground);
    SDL_DestroyTexture(mDogTexture);
    SDL_DestroyTexture(mFarmerTexture);
    SDL_DestroyTexture(mButtonTexture);
}

void UIScreen::LoadAssets()
{
    SDL_Surface* surface = IMG_Load("Assets/Background.png");
    SDL_Surface* dogSurf = IMG_Load("Assets/Dog.png");
    SDL_Surface* farmerSurf = IMG_Load("Assets/Farmer.png");

    mBackground = SDL_CreateTextureFromSurface(mRenderer, surface);
    mDogTexture = SDL_CreateTextureFromSurface(mRenderer, dogSurf);
    mFarmerTexture = SDL_CreateTextureFromSurface(mRenderer, farmerSurf);
    mButtonTexture = IMG_LoadTexture(mRenderer, "Assets/Button.png");

    SDL_FreeSurface(surface);
    SDL_FreeSurface(dogSurf);
    SDL_FreeSurface(farmerSurf);

    mDogRect = { 1024 - 200 - 50, 200, 200, 200 };
    mFarmerRect = { 50, 768 - 200 - 200, 200, 200 };
    mButtonRect = { 400, 680, 190, 49 };
}

void UIScreen::DrawHPBar(int x, int y, int hp)
{
    SDL_Rect bg = { x, y, 104, 14 };
    SDL_Rect bar = { x + 2, y + 2, hp, 10 };

    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(mRenderer, &bg);
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(mRenderer, &bar);
}

void UIScreen::Render(Unit* player, Unit* dog)
{
    SDL_RenderClear(mRenderer);

    SDL_RenderCopy(mRenderer, mBackground, nullptr, nullptr);
    SDL_RenderCopy(mRenderer, mDogTexture, nullptr, &mDogRect);
    SDL_RenderCopy(mRenderer, mFarmerTexture, nullptr, &mFarmerRect);

    DrawHPBar(mDogRect.x, mDogRect.y - 20, dog->GetHP());
    DrawHPBar(mFarmerRect.x, mFarmerRect.y - 20, player->GetHP());

    SDL_RenderCopy(mRenderer, mButtonTexture, nullptr, &mButtonRect);

    SDL_RenderPresent(mRenderer);
}

SDL_Rect UIScreen::GetButtonRect() const
{
    return mButtonRect;
}

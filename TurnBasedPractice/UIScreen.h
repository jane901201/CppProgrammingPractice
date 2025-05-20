#pragma once
#include <SDL/SDL.h>
#include "Unit.h"
#include <SDL/SDL_ttf.h>

class UIScreen {
public:
    UIScreen(SDL_Renderer* renderer);
    ~UIScreen();

    void LoadAssets();
    void Render(Unit* player, Unit* dog);
    SDL_Rect GetAttackButtonRect() const;

private:
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;

    SDL_Texture* mBackground;
    SDL_Texture* mDogTexture;
    SDL_Texture* mFarmerTexture;
    SDL_Texture* mButtonTexture;

    SDL_Texture* mAttackButtonTexture;
    SDL_Texture* mDefendButtonTexture;
    SDL_Texture* mSpecialButtonTexture;

    SDL_Rect mDogRect;
    SDL_Rect mFarmerRect;
    SDL_Rect mButtonRect;

    SDL_Rect mAttackRect;
    SDL_Rect mDefendRect;
    SDL_Rect mSpecialRect;


    void DrawHPBar(int x, int y, int hp);
    void DrawTextCentered(const char* text, const SDL_Rect& targetRect);
};
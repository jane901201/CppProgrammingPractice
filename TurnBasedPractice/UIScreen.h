#pragma once
#include <SDL/SDL.h>
#include "Unit.h"

class UIScreen {
public:
    UIScreen(SDL_Renderer* renderer);
    ~UIScreen();

    void LoadAssets();
    void Render(Unit* player, Unit* dog);
    SDL_Rect GetButtonRect() const;

private:
    SDL_Renderer* mRenderer;

    SDL_Texture* mBackground;
    SDL_Texture* mDogTexture;
    SDL_Texture* mFarmerTexture;
    SDL_Texture* mButtonTexture;

    SDL_Rect mDogRect;
    SDL_Rect mFarmerRect;
    SDL_Rect mButtonRect;

    void DrawHPBar(int x, int y, int hp);
};
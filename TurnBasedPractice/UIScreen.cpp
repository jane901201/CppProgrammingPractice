#include "UIScreen.h"
#include <SDL/SDL_image.h>
#include <iostream>
#include <SDL/SDL_ttf.h>

UIScreen::UIScreen(SDL_Renderer* renderer)
    : mRenderer(renderer),
    mBackground(nullptr),
    mDogTexture(nullptr),
    mFarmerTexture(nullptr),
    mButtonTexture(nullptr),
    mAttackButtonTexture(nullptr),
    mDefendButtonTexture(nullptr),
    mSpecialButtonTexture(nullptr)
{
    LoadAssets();
}

UIScreen::~UIScreen()
{
    SDL_DestroyTexture(mBackground);
    SDL_DestroyTexture(mDogTexture);
    SDL_DestroyTexture(mFarmerTexture);
    SDL_DestroyTexture(mButtonTexture);
    SDL_DestroyTexture(mAttackButtonTexture);
    SDL_DestroyTexture(mDefendButtonTexture);
    SDL_DestroyTexture(mSpecialButtonTexture);
}

void UIScreen::LoadAssets()
{
    SDL_Surface* backgroundSurf = IMG_Load("Assets/Background.png");
    SDL_Surface* dogSurf = IMG_Load("Assets/Dog.png");
    SDL_Surface* farmerSurf = IMG_Load("Assets/Farmer.png");

    mBackground = SDL_CreateTextureFromSurface(mRenderer, backgroundSurf);
    mDogTexture = SDL_CreateTextureFromSurface(mRenderer, dogSurf);
    mFarmerTexture = SDL_CreateTextureFromSurface(mRenderer, farmerSurf);

    mButtonTexture = IMG_LoadTexture(mRenderer, "Assets/Button.png");

    SDL_FreeSurface(backgroundSurf);
    SDL_FreeSurface(dogSurf);
    SDL_FreeSurface(farmerSurf);

    mDogRect = { 1024 - 200 - 50, 200, 200, 200 };
    mPlayerRect = { 50, 768 - 200 - 200, 200, 200 };

    mAttackRect = { 200, 680, 190, 49 };
    mDefendRect = { 400, 680, 190, 49 };
    mSpecialRect = { 600, 680, 190, 49 };

    auto adjustButtonRect = [](SDL_Rect& rect, int newHeight) {
        int centerY = rect.y + rect.h / 2;
        rect.h = newHeight;
        rect.y = centerY - rect.h / 2;
    };

    // ボタンの高さを全部80に
    adjustButtonRect(mAttackRect, 100);
    adjustButtonRect(mDefendRect, 100);
    adjustButtonRect(mSpecialRect, 100);

    // フォント読み込み
    mFont = TTF_OpenFont("Assets/NotoSans-Regular.ttf", 24);
    if (!mFont) {
        std::cout << "Font Load Error: " << TTF_GetError() << std::endl;
    }

}

void UIScreen::DrawHPBar(int x, int y, int hp)
{
    const int maxHP = 100;     // HPの最大値（固定）
    const int barWidth = 100;  // HPバーの表示幅

    SDL_Rect bg = { x, y, barWidth + 4, 14 }; // +4 は枠分（左右2pxずつ）
    int hpWidth = (hp * barWidth) / maxHP;    // 現在HPの割合で横幅を決定
    SDL_Rect bar = { x + 2, y + 2, hpWidth, 10 };

    // 背景（黒い枠）
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(mRenderer, &bg);

    // HPバー（赤）
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(mRenderer, &bar);
}

void UIScreen::DrawTextCentered(const char* text, const SDL_Rect& targetRect)
{
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderUTF8_Blended(mFont, text, color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }

    // テキストサイズ
    int textW = surface->w;
    int textH = surface->h;

    // ボタンの中央に合わせる
    SDL_Rect dstRect;
    dstRect.x = targetRect.x + (targetRect.w - textW) / 2;
    dstRect.y = targetRect.y + (targetRect.h - textH) / 2;
    dstRect.w = textW;
    dstRect.h = textH;

    SDL_FreeSurface(surface);
    SDL_RenderCopy(mRenderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
}

void UIScreen::Render(Unit* player, Unit* dog, const char* phaseText, const char* playerActionText, const char* dogActionText)
{
    SDL_RenderClear(mRenderer);

    SDL_RenderCopy(mRenderer, mBackground, nullptr, nullptr);
    SDL_RenderCopy(mRenderer, mDogTexture, nullptr, &mDogRect);
    SDL_RenderCopy(mRenderer, mFarmerTexture, nullptr, &mPlayerRect);

    DrawHPBar(mDogRect.x, mDogRect.y - 20, dog->GetHP());
    DrawHPBar(mPlayerRect.x, mPlayerRect.y - 20, player->GetHP());

    SDL_RenderCopy(mRenderer, mButtonTexture, nullptr, &mAttackRect);
    SDL_RenderCopy(mRenderer, mButtonTexture, nullptr, &mDefendRect);
    SDL_RenderCopy(mRenderer, mButtonTexture, nullptr, &mSpecialRect);

    // ボタンのテキスト
    DrawTextCentered("Attack", mAttackRect);
    DrawTextCentered("Defend", mDefendRect);
    DrawTextCentered("Special Attack", mSpecialRect);

    // 上部中央にフェーズ名を表示
    DrawTextCentered(phaseText, { 0, 20, 1024, 40 }); // 画面上部中央

    DrawTextCentered(playerActionText, { 100, 50, 300, 30 });
    DrawTextCentered(dogActionText, { 600, 50, 300, 30 });

    SDL_RenderPresent(mRenderer);
}

SDL_Rect UIScreen::GetAttackButtonRect() const
{
    return mAttackRect;
}

SDL_Rect UIScreen::GetDefendButtonRect() const
{
    return mDefendRect;
}

SDL_Rect UIScreen::GetSpecialButtonRect() const
{
    return mSpecialRect;
}
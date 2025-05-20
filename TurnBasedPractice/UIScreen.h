#pragma once
#include <GL/glew.h>
#include <string>
#include "Unit.h"
#include <SDL/SDL.h>

class UIScreen {
public:
    UIScreen();
    ~UIScreen();

    bool LoadAssets();
    void Render(Unit* player, Unit* dog, const char* phaseText, const char* playerActionText, const char* dogActionText);

    SDL_Rect GetAttackButtonRect() const;
    SDL_Rect GetDefendButtonRect() const;
    SDL_Rect GetSpecialButtonRect() const;

private:
    GLuint mBackgroundTex;
    GLuint mDogTex;
    GLuint mFarmerTex;
    GLuint mButtonTex;

    SDL_Rect mDogRect;
    SDL_Rect mPlayerRect;

    SDL_Rect mAttackRect;
    SDL_Rect mDefendRect;
    SDL_Rect mSpecialRect;

    GLuint LoadGLTextureFromFile(const char* path);
    void DrawQuad(GLuint texture, int x, int y, int w, int h);
    void DrawHPBar(int x, int y, int hp);
};
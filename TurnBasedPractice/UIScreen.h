#pragma once
#include <GL/glew.h>
#include <string>
#include "Unit.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "TextRenderer.h"

class UIScreen {
public:
    UIScreen();
    ~UIScreen();

    bool LoadAssets();
    void Render(Unit* player, Unit* enemy, const char* phaseText, const char* playerActionText, const char* enemyActionText);

    SDL_Rect GetAttackButtonRect() const;
    SDL_Rect GetDefendButtonRect() const;
    SDL_Rect GetSpecialButtonRect() const;

    
    SDL_Rect GetEnemyRect() const;
    SDL_Rect GetPlayerRect() const;

private:
    GLuint mBackgroundTex;
    GLuint mEnemyTex;
    GLuint mPlayerTex;
    GLuint mButtonTex;

    SDL_Rect mEnemyRect;
    SDL_Rect mPlayerRect;

    SDL_Rect mAttackRect;
    SDL_Rect mDefendRect;
    SDL_Rect mSpecialRect;

    TextRenderer mTextRenderer;

    GLuint LoadGLTextureFromFile(const char* path);
    void DrawQuad(GLuint texture, int x, int y, int w, int h);
    void DrawHPBar(int x, int y, int hp);
};
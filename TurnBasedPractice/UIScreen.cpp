#include "UIScreen.h"
#include <SDL/SDL_image.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>

UIScreen::UIScreen() : mBackgroundTex(0), mEnemyTex(0), mPlayerTex(0), mButtonTex(0) {}

UIScreen::~UIScreen() {
    glDeleteTextures(1, &mBackgroundTex);
    glDeleteTextures(1, &mEnemyTex);
    glDeleteTextures(1, &mPlayerTex);
    glDeleteTextures(1, &mButtonTex);
}

bool UIScreen::LoadAssets() {
    mBackgroundTex = LoadGLTextureFromFile("Assets/Background.png");
    mEnemyTex = LoadGLTextureFromFile("Assets/Dog.png");
    mPlayerTex = LoadGLTextureFromFile("Assets/Farmer.png");
    mButtonTex = LoadGLTextureFromFile("Assets/Button.png");

    if (!mBackgroundTex || !mEnemyTex || !mPlayerTex || !mButtonTex)
        return false;

    if (!mTextRenderer.Initialize("Assets/NotoSans-Regular.ttf", 32)) {
        return false;
    }

    mEnemyRect = { 774, 200, 200, 200 };
    mPlayerRect = { 50, 368, 200, 200 };
    mAttackRect = { 200, 600, 190, 120 };
    mDefendRect = { 400, 600, 190, 120 };
    mSpecialRect = { 600, 600, 190, 120 };

    return true;
}

GLuint UIScreen::LoadGLTextureFromFile(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        std::cout << "IMG_Load failed: " << IMG_GetError() << std::endl;
        return 0;
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);
    return texID;
}

void UIScreen::DrawQuad(GLuint texture, int x, int y, int w, int h) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(x, y);
    glTexCoord2f(1, 0); glVertex2f(x + w, y);
    glTexCoord2f(1, 1); glVertex2f(x + w, y + h);
    glTexCoord2f(0, 1); glVertex2f(x, y + h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void UIScreen::DrawHPBar(int x, int y, int hp) {
    const int maxHP = 100;
    int barWidth = 100;
    int barHeight = 10;

    int hpWidth = (hp * barWidth) / maxHP;

    glColor3f(0.0f, 0.0f, 0.0f); // 枠（背景）
    glBegin(GL_QUADS);
    glVertex2f(x - 2, y - 2);
    glVertex2f(x + barWidth + 2, y - 2);
    glVertex2f(x + barWidth + 2, y + barHeight + 2);
    glVertex2f(x - 2, y + barHeight + 2);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); // HPバー本体
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + hpWidth, y);
    glVertex2f(x + hpWidth, y + barHeight);
    glVertex2f(x, y + barHeight);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // 色を戻す
}

void UIScreen::Render(Unit* player, Unit* enemy, const char* phaseText, const char* playerActionText, const char* enemyActionText) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClear(GL_COLOR_BUFFER_BIT);

    DrawQuad(mBackgroundTex, 0, 0, 1024, 768);
    DrawQuad(mEnemyTex, mEnemyRect.x, mEnemyRect.y, mEnemyRect.w, mEnemyRect.h);
    DrawQuad(mPlayerTex, mPlayerRect.x, mPlayerRect.y, mPlayerRect.w, mPlayerRect.h);

    DrawHPBar(mEnemyRect.x, mEnemyRect.y - 20, enemy->GetHP());
    DrawHPBar(mPlayerRect.x, mPlayerRect.y - 20, player->GetHP());

    DrawQuad(mButtonTex, mAttackRect.x, mAttackRect.y, mAttackRect.w, mAttackRect.h);
    DrawQuad(mButtonTex, mDefendRect.x, mDefendRect.y, mDefendRect.w, mDefendRect.h);
    DrawQuad(mButtonTex, mSpecialRect.x, mSpecialRect.y, mSpecialRect.w, mSpecialRect.h);

    // 描画時：
    SDL_Color white = { 255, 255, 255 };
    int w, h;
    GLuint attackTex = mTextRenderer.RenderText("Attack", white, w, h);
    mTextRenderer.DrawTextTexture(
        attackTex,
        mAttackRect.x + (mAttackRect.w - w) / 2,
        mAttackRect.y + (mAttackRect.h - h) / 2,
        w, h);
    GLuint defendTex = mTextRenderer.RenderText("Defend", white, w, h);
    mTextRenderer.DrawTextTexture(
        defendTex,
        mDefendRect.x + (mDefendRect.w - w) / 2,
        mDefendRect.y + (mDefendRect.h - h) / 2,
        w, h);
    GLuint specialTex = mTextRenderer.RenderText("Special", white, w, h);
    mTextRenderer.DrawTextTexture(
        specialTex,
        mSpecialRect.x + (mSpecialRect.w - w) / 2,
        mSpecialRect.y + (mSpecialRect.h - h) / 2,
        w, h);

    int phaseW, phaseH;
    GLuint phaseTex = mTextRenderer.RenderText(phaseText, white, phaseW, phaseH);
    mTextRenderer.DrawTextTexture(
        phaseTex,
        (1024 - phaseW) / 2, 
        30,                   
        phaseW, phaseH);
    glDeleteTextures(1, &phaseTex);

    // プレイヤー行動内容
    if (playerActionText && playerActionText[0] != '\0') {
        int w, h;
        GLuint tex = mTextRenderer.RenderText(playerActionText, white, w, h);
        mTextRenderer.DrawTextTexture(tex, 100, 80, w, h);
        glDeleteTextures(1, &tex);
    }

    // 敵の行動内容
    if (enemyActionText && enemyActionText[0] != '\0') {
        int w, h;
        GLuint tex = mTextRenderer.RenderText(enemyActionText, white, w, h);
        mTextRenderer.DrawTextTexture(tex, 600, 80, w, h);
        glDeleteTextures(1, &tex);
    }


    glDeleteTextures(1, &attackTex);
    glDeleteTextures(1, &defendTex);
    glDeleteTextures(1, &specialTex);

    glFlush();
}

SDL_Rect UIScreen::GetAttackButtonRect() const { return mAttackRect; }
SDL_Rect UIScreen::GetDefendButtonRect() const { return mDefendRect; }
SDL_Rect UIScreen::GetSpecialButtonRect() const { return mSpecialRect; }
SDL_Rect UIScreen::GetEnemyRect() const { return mEnemyRect; }
SDL_Rect UIScreen::GetPlayerRect() const { return mPlayerRect; }
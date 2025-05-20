#include "UIScreen.h"
#include <SDL/SDL_image.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>

UIScreen::UIScreen() : mBackgroundTex(0), mDogTex(0), mFarmerTex(0), mButtonTex(0) {}

UIScreen::~UIScreen() {
    glDeleteTextures(1, &mBackgroundTex);
    glDeleteTextures(1, &mDogTex);
    glDeleteTextures(1, &mFarmerTex);
    glDeleteTextures(1, &mButtonTex);
}

bool UIScreen::LoadAssets() {
    mBackgroundTex = LoadGLTextureFromFile("Assets/Background.png");
    mDogTex = LoadGLTextureFromFile("Assets/Dog.png");
    mFarmerTex = LoadGLTextureFromFile("Assets/Farmer.png");
    mButtonTex = LoadGLTextureFromFile("Assets/Button.png");

    if (!mBackgroundTex || !mDogTex || !mFarmerTex || !mButtonTex)
        return false;

    mDogRect = { 774, 200, 200, 200 };
    mPlayerRect = { 50, 368, 200, 200 };
    mAttackRect = { 200, 680, 190, 80 };
    mDefendRect = { 400, 680, 190, 80 };
    mSpecialRect = { 600, 680, 190, 80 };

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
    int hpWidth = (hp * 100) / maxHP;

    float fx = x / 512.0f - 1.0f;
    float fy = 1.0f - y / 384.0f;
    float fw = hpWidth / 512.0f;
    float fh = 10 / 384.0f;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(fx, fy);
    glVertex2f(fx + fw, fy);
    glVertex2f(fx + fw, fy - fh);
    glVertex2f(fx, fy - fh);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
}

void UIScreen::Render(Unit* player, Unit* dog, const char* phaseText, const char* playerActionText, const char* dogActionText) {
    glClear(GL_COLOR_BUFFER_BIT);

    DrawQuad(mBackgroundTex, 0, 0, 1024, 768);
    DrawQuad(mDogTex, mDogRect.x, mDogRect.y, mDogRect.w, mDogRect.h);
    DrawQuad(mFarmerTex, mPlayerRect.x, mPlayerRect.y, mPlayerRect.w, mPlayerRect.h);

    DrawHPBar(mDogRect.x, mDogRect.y - 20, dog->GetHP());
    DrawHPBar(mPlayerRect.x, mPlayerRect.y - 20, player->GetHP());

    DrawQuad(mButtonTex, mAttackRect.x, mAttackRect.y, mAttackRect.w, mAttackRect.h);
    DrawQuad(mButtonTex, mDefendRect.x, mDefendRect.y, mDefendRect.w, mDefendRect.h);
    DrawQuad(mButtonTex, mSpecialRect.x, mSpecialRect.y, mSpecialRect.w, mSpecialRect.h);

    // テキストは未対応。必要ならSDL_ttf→OpenGLテクスチャに変換で対応可能。

    glFlush();
}

SDL_Rect UIScreen::GetAttackButtonRect() const { return mAttackRect; }
SDL_Rect UIScreen::GetDefendButtonRect() const { return mDefendRect; }
SDL_Rect UIScreen::GetSpecialButtonRect() const { return mSpecialRect; }
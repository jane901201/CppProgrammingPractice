#include "TextRenderer.h"
#include <iostream>

TextRenderer::TextRenderer()
    : mFont(nullptr) {}

TextRenderer::~TextRenderer() {
    Shutdown();
}

bool TextRenderer::Initialize(const std::string& fontPath, int fontSize) {
    mFont = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!mFont) {
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void TextRenderer::Shutdown() {
    if (mFont) {
        TTF_CloseFont(mFont);
        mFont = nullptr;
    }
}

GLuint TextRenderer::RenderText(const std::string& text, SDL_Color color, int& outW, int& outH) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(mFont, text.c_str(), color);
    if (!surface) {
        std::cout << "Text render failed: " << TTF_GetError() << std::endl;
        return 0;
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format,
        surface->w, surface->h, 0,
        format, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    outW = surface->w;
    outH = surface->h;

    SDL_FreeSurface(surface);
    return texID;
}

void TextRenderer::DrawTextTexture(GLuint texID, int x, int y, int w, int h) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(x, y);
    glTexCoord2f(1, 0); glVertex2f(x + w, y);
    glTexCoord2f(1, 1); glVertex2f(x + w, y + h);
    glTexCoord2f(0, 1); glVertex2f(x, y + h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
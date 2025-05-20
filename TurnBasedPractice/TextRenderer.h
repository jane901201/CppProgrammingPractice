#pragma once
#include <string>
#include <SDL/SDL_ttf.h>
#include <GL/glew.h>
#include <GL/gl.h>

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();

    bool Initialize(const std::string& fontPath, int fontSize);
    void Shutdown();

    // テキストを OpenGL テクスチャに変換（出力：テクスチャID、サイズ）
    GLuint RenderText(const std::string& text, SDL_Color color, int& outW, int& outH);

    // テクスチャを指定位置に描画（左上座標）
    void DrawTextTexture(GLuint texID, int x, int y, int w, int h);

private:
    TTF_Font* mFont;
};
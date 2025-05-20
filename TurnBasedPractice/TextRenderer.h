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

    // �e�L�X�g�� OpenGL �e�N�X�`���ɕϊ��i�o�́F�e�N�X�`��ID�A�T�C�Y�j
    GLuint RenderText(const std::string& text, SDL_Color color, int& outW, int& outH);

    // �e�N�X�`�����w��ʒu�ɕ`��i������W�j
    void DrawTextTexture(GLuint texID, int x, int y, int w, int h);

private:
    TTF_Font* mFont;
};
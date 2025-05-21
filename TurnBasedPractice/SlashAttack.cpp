#include "SlashAttack.h"

SlashAttack::SlashAttack()
    : mStartTime(0.0f), mDuration(0.3f), mActive(false) {}

void SlashAttack::Start(const SDL_Rect& targetRect, float durationSec) {
    mRect = targetRect;
    mStartTime = SDL_GetTicks() / 1000.0f;
    mDuration = durationSec;
    mActive = true;
}

void SlashAttack::Update(float currentTime) {
    if (mActive && (currentTime - mStartTime >= mDuration)) {
        mActive = false;
    }
}

void SlashAttack::Draw(Shader& shader) {
    if (!mActive) return;

    shader.Use();
    float time = SDL_GetTicks() / 1000.0f;
    glUniform1f(glGetUniformLocation(shader.GetProgram(), "uTime"), time);
    glUniform1f(glGetUniformLocation(shader.GetProgram(), "uIntensity"), 1.0f);

    glDisable(GL_TEXTURE_2D);
    glColor4f(1.0, 1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
    glVertex2f(mRect.x, mRect.y);
    glVertex2f(mRect.x + mRect.w, mRect.y);
    glVertex2f(mRect.x + mRect.w, mRect.y + mRect.h);
    glVertex2f(mRect.x, mRect.y + mRect.h);
    glEnd();

    glUseProgram(0);
}

bool SlashAttack::IsActive() const {
    return mActive;
}
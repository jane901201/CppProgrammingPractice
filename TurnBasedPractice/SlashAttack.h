#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Shader.h"

class SlashAttack {
public:
    SlashAttack();

    void Start(const SDL_Rect& targetRect, float durationSec = 0.3f);
    void Update(float currentTime); // ïbíPà ÅiSDL_GetTicks()/1000.0fÅj
    void Draw(Shader& shader);

    bool IsActive() const;

private:
    SDL_Rect mRect;
    float mStartTime;
    float mDuration;
    bool mActive;
};
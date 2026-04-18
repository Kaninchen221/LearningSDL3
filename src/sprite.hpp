#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_image/SDL_image.h>

struct Sprite
{
    SDL_FRect sourceRect;
    SDL_FRect destRect;
};

void DrawSprites(auto* renderer, auto* texture, const auto& sprites)
{
    for (const auto& sprite : sprites)
    {
        SDL_RenderTexture(renderer, texture, &sprite.sourceRect, &sprite.destRect);
    }
}
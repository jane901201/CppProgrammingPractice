#include "SDL/SDL_image.h"
#include <iostream>

void DrawHPBar(SDL_Renderer* renderer, int x, int y, int hp)
{
    SDL_Rect bg = { x, y, 104, 14 }; // 背景（枠）
    SDL_Rect bar = { x + 2, y + 2, hp, 10 }; // 中身（HP）

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 黒い枠
    SDL_RenderFillRect(renderer, &bg);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 赤色HPバー
    SDL_RenderFillRect(renderer, &bar);
}

int main(int argc, char* argv[])
{
    int dogHP = 100;
    int farmerHP = 100;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Background Example", 100, 100, 1024, 768, 0);
    if (!window)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // SDL_image 初期化
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 背景画像を読み込む
    SDL_Surface* surface = IMG_Load("Assets/Background.png");
    SDL_Surface* dogSurf = IMG_Load("Assets/Dog.png");
    SDL_Surface* farmerSurf = IMG_Load("Assets/Farmer.png");
    SDL_Texture* buttonTex = IMG_LoadTexture(renderer, "Assets/Button.png");


    if (!surface)
    {
        std::cout << "IMG_Load Error: " << IMG_GetError() << std::endl;
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect buttonRect = { 400, 680, 190, 49 }; // 画面下部中央付近
    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture* dogTex = SDL_CreateTextureFromSurface(renderer, dogSurf);
    SDL_Texture* farmerTex = SDL_CreateTextureFromSurface(renderer, farmerSurf);


    SDL_FreeSurface(surface);
    SDL_FreeSurface(dogSurf);
    SDL_FreeSurface(farmerSurf);

    SDL_Rect dogRect;
    dogRect.w = 200; // 幅（画像に応じて調整）
    dogRect.h = 200; // 高さ
    dogRect.x = 1024 - 200 - 50;  // 右端から50px内側
    dogRect.y = 200;               // 上端から50px下

    SDL_Rect farmerRect;
    farmerRect.w = 200;
    farmerRect.h = 200;
    farmerRect.x = 50;            // 左端から50px内側
    farmerRect.y = 768 - 200 - 200; // 下端から50px上

    if (!background)
    {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // メインループ
    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mx = event.button.x;
                int my = event.button.y;
                if (mx >= buttonRect.x && mx <= buttonRect.x + buttonRect.w &&
                    my >= buttonRect.y && my <= buttonRect.y + buttonRect.h)
                {
                    if (dogHP > 0) dogHP -= 10;
                }
            }

        }

        // 背景を描画
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, nullptr, nullptr);
        // キャラ
        SDL_RenderCopy(renderer, dogTex, nullptr, &dogRect);
        SDL_RenderCopy(renderer, farmerTex, nullptr, &farmerRect);

        // HPバー
        DrawHPBar(renderer, dogRect.x, dogRect.y - 20, dogHP);
        DrawHPBar(renderer, farmerRect.x, farmerRect.y - 20, farmerHP);

        // 攻撃ボタン
        SDL_RenderCopy(renderer, buttonTex, nullptr, &buttonRect);

        SDL_RenderPresent(renderer);


    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(dogTex);
    SDL_DestroyTexture(farmerTex);

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//#include "Game.h"
//
//int main(int argc, char** argv)
//{
//	Game game;
//	bool success = game.Initialize();
//	if (success)
//	{
//		game.RunLoop();
//	}
//	game.Shutdown();
//	return 0;
//}

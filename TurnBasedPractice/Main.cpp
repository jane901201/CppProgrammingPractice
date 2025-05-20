#include "SDL/SDL_image.h"
#include <iostream>
#include "Unit.h"
#include "PlayerUnit.h"
#include "DogUnit.h"
#include "UIScreen.h"
#include <SDL/SDL_ttf.h>

int main(int argc, char* argv[])
{
    Unit* player = new PlayerUnit();
    Unit* dog = new DogUnit();

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
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

    bool running = true;
    SDL_Event event;


    UIScreen* ui = new UIScreen(renderer);

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
                SDL_Rect buttonRect = ui->GetAttackButtonRect();
                if (mx >= buttonRect.x && mx <= buttonRect.x + buttonRect.w &&
                    my >= buttonRect.y && my <= buttonRect.y + buttonRect.h)
                {
                    if (dog->GetHP() > 0) dog->SetHP(dog->GetHP() - 10);
                }
            }
        }

        ui->Render(player, dog);
    }

    delete player;
    delete dog;
    delete ui;

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

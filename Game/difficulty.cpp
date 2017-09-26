#include "difficulty.hpp"
#include<SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "items.hpp"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define SCREENW 640
#define SCREENH 480
#define BUTTONW 180
#define BUTTONH 60
#define SCREENW 640
#define SCREENH 480
#define BUTTONW 180
#define BUTTONH 60

int getDifficuty(SDL_Renderer* gRenderer) {

	SDL_Texture* mainTexture;
	SDL_Surface *tmp = SDL_LoadBMP("img/background.bmp");
	mainTexture = SDL_CreateTextureFromSurface(gRenderer, tmp);
	SDL_FreeSurface(tmp);

	Button easyBtnMain(SCREENW / 2 - BUTTONW / 2, 90, BUTTONW, BUTTONH, "img/button/easy.bmp", gRenderer);
	Button normalBtnMain(SCREENW / 2 - BUTTONW / 2, 180, BUTTONW, BUTTONH, "img/button/normal.bmp", gRenderer);
	Button hardBtnMain(SCREENW / 2 - BUTTONW / 2,270, BUTTONW, BUTTONH, "img/button/difficult.bmp", gRenderer);
	Button backBtnMain(SCREENW / 2 - BUTTONW / 2, 360, BUTTONW, BUTTONH, "img/button/back.bmp", gRenderer);
	Button selected_easyBtnMain(SCREENW / 2 - BUTTONW / 2, 90, BUTTONW, BUTTONH, "img/button/easy-selected.bmp", gRenderer);
	Button selected_normalBtnMain(SCREENW / 2 - BUTTONW / 2, 180, BUTTONW, BUTTONH, "img/button/normal-selected.bmp", gRenderer);
	Button selected_hardBtnMain(SCREENW / 2 - BUTTONW / 2, 270, BUTTONW, BUTTONH, "img/button/difficult-selected.bmp", gRenderer);
	Button selected_backBtnMain(SCREENW / 2 - BUTTONW / 2, 360, BUTTONW, BUTTONH, "img/button/back-selected.bmp", gRenderer);
	//0 easy 1 normal 2hard 3back
	int difficultyopt = 0;
	int isRunning = 1;
	SDL_Event e;

	SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
	selected_easyBtnMain.redraw();
	normalBtnMain.redraw();
	hardBtnMain.redraw();
	backBtnMain.redraw();

	SDL_RenderPresent(gRenderer);

	while (isRunning)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				return -1;
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_UP)
				{
					// if user press up so we need decrease curOp

					if (difficultyopt > 0)
					{
						difficultyopt--;
						// then redraw
						SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
						if (difficultyopt == 0)             
						{
							selected_easyBtnMain.redraw();
							normalBtnMain.redraw();
							hardBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (difficultyopt == 1)
						{
							selected_normalBtnMain.redraw();
							easyBtnMain.redraw();
							hardBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (difficultyopt == 2)
						{
							selected_hardBtnMain.redraw();
							easyBtnMain.redraw();
							normalBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (difficultyopt == 3)
						{
							selected_backBtnMain.redraw();
							hardBtnMain.redraw();
							easyBtnMain.redraw();
							normalBtnMain.redraw();
						}

						SDL_RenderPresent(gRenderer);
					}
					continue;
				}

				if (e.key.keysym.sym == SDLK_DOWN)
				{

					if (difficultyopt <3)
					{

						difficultyopt++;//


						SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
						if (difficultyopt == 0)
						{
							selected_easyBtnMain.redraw();
							normalBtnMain.redraw();
							hardBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (difficultyopt == 1)
						{
							selected_normalBtnMain.redraw();
							easyBtnMain.redraw();
							hardBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (difficultyopt == 2)
						{
							selected_hardBtnMain.redraw();
							easyBtnMain.redraw();
							normalBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (difficultyopt == 3)
						{
							selected_backBtnMain.redraw();
							hardBtnMain.redraw();
							easyBtnMain.redraw();
							normalBtnMain.redraw();
						}

						SDL_RenderPresent(gRenderer);
					}
					continue;
				}
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					return -2;
				}
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					// check here if current option is 0,1,2
					if (difficultyopt == 2)
					{
						return 2;
					}
					if (difficultyopt == 0)
					{
						return 0;
					}
					if (difficultyopt == 1)
					{
						return 1;
					}
					if (difficultyopt == 3)
					{
						return -2;
					}
				}
			}
		}
	}
}

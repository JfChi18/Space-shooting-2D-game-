#include "soundcontrol.hpp"
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
#define BUTTONW 150
#define BUTTONH 50

int getVolumn(SDL_Renderer* gRenderer) {

	SDL_Texture* mainTexture;
	SDL_Surface *tmp = SDL_LoadBMP("img/background.bmp");
	mainTexture = SDL_CreateTextureFromSurface(gRenderer, tmp);
	SDL_FreeSurface(tmp);

	Button oneBtnMain(SCREENW / 2 - BUTTONW / 2, 80, BUTTONW, BUTTONH, "img/button/1.bmp", gRenderer);
	Button twoBtnMain(SCREENW / 2 - BUTTONW / 2, 160, BUTTONW, BUTTONH, "img/button/2.bmp", gRenderer);
	Button threeBtnMain(SCREENW / 2 - BUTTONW / 2, 240, BUTTONW, BUTTONH, "img/button/3.bmp", gRenderer);
	Button fourBtnMain(SCREENW / 2 - BUTTONW / 2, 320, BUTTONW, BUTTONH, "img/button/4.bmp", gRenderer);
	Button backBtnMain(SCREENW / 2 - BUTTONW / 2, 400, BUTTONW, BUTTONH, "img/button/back.bmp", gRenderer);
	Button selected_oneBtnMain(SCREENW / 2 - BUTTONW / 2, 80, BUTTONW, BUTTONH, "img/button/1-selected.bmp", gRenderer);
	Button selected_twoBtnMain(SCREENW / 2 - BUTTONW / 2, 160, BUTTONW, BUTTONH, "img/button/2-selected.bmp", gRenderer);
	Button selected_threeBtnMain(SCREENW / 2 - BUTTONW / 2, 240, BUTTONW, BUTTONH, "img/button/3-selected.bmp", gRenderer);
	Button selected_fourBtnMain(SCREENW / 2 - BUTTONW / 2, 320, BUTTONW, BUTTONH, "img/button/4-selected.bmp", gRenderer);
	Button selected_backBtnMain(SCREENW / 2 - BUTTONW / 2, 400, BUTTONW, BUTTONH, "img/button/back-selected.bmp", gRenderer);
	//0-1,1-2,2-3,3-4,4-back
	int soundopt = 0;
	int isRunning = 1;
	SDL_Event e;

	SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);

	selected_oneBtnMain.redraw();
	twoBtnMain.redraw();
	threeBtnMain.redraw();
	fourBtnMain.redraw();
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

					if (soundopt > 0)
					{
						soundopt--;
						// then redraw
						SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
						if (soundopt == 0)
						{
							selected_oneBtnMain.redraw();
							twoBtnMain.redraw();
							threeBtnMain.redraw();
							fourBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (soundopt == 1)
						{
							oneBtnMain.redraw();
							selected_twoBtnMain.redraw();
							threeBtnMain.redraw();
							fourBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (soundopt == 2)
						{
							oneBtnMain.redraw();
							twoBtnMain.redraw();
							selected_threeBtnMain.redraw();
							fourBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (soundopt == 3)
						{
							oneBtnMain.redraw();
							twoBtnMain.redraw();
							threeBtnMain.redraw();
							selected_fourBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (soundopt == 4) {
							oneBtnMain.redraw();
							twoBtnMain.redraw();
							threeBtnMain.redraw();
							fourBtnMain.redraw();
							selected_backBtnMain.redraw();
						}

						SDL_RenderPresent(gRenderer);
					}
					continue;
				}

				if (e.key.keysym.sym == SDLK_DOWN)
				{

					if (soundopt <4)
					{

						soundopt++;//


						SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
						if (soundopt == 0)
						{
							selected_oneBtnMain.redraw();
							twoBtnMain.redraw();
							threeBtnMain.redraw();
							fourBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (soundopt == 1)
						{
							oneBtnMain.redraw();
							selected_twoBtnMain.redraw();
							threeBtnMain.redraw();
							fourBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (soundopt == 2)
						{
							oneBtnMain.redraw();
							twoBtnMain.redraw();
							selected_threeBtnMain.redraw();
							fourBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (soundopt == 3)
						{
							oneBtnMain.redraw();
							twoBtnMain.redraw();
							threeBtnMain.redraw();
							selected_fourBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (soundopt == 4) {
							oneBtnMain.redraw();
							twoBtnMain.redraw();
							threeBtnMain.redraw();
							fourBtnMain.redraw();
							selected_backBtnMain.redraw();
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
					if (soundopt == 2)
					{
						return 2;
					}
					if (soundopt == 0)
					{
						return 0;
					}
					if (soundopt == 1)
					{
						return 1;
					}
					if (soundopt == 3)
					{
						return 3;
					}
					if (soundopt == 4)
					{
						return -2;
					}
				}
			}
		}
	}
}

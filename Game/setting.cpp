#include "setting.hpp"
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

int getSettingoption(SDL_Renderer* gRenderer) {

	SDL_Texture* mainTexture;
	SDL_Surface *tmp = SDL_LoadBMP("img/background.bmp");
	mainTexture = SDL_CreateTextureFromSurface(gRenderer, tmp);
	SDL_FreeSurface(tmp);

	Button difficultyBtnMain(SCREENW / 2 - BUTTONW / 2, 150, BUTTONW, BUTTONH, "img/button/difficulty.bmp", gRenderer);
	Button soundBtnMain(SCREENW / 2 - BUTTONW / 2, 250, BUTTONW, BUTTONH, "img/button/sound.bmp", gRenderer);
	Button backBtnMain(SCREENW / 2 - BUTTONW / 2, 350, BUTTONW, BUTTONH, "img/button/back.bmp", gRenderer);
	Button selected_difficultyBtnMain(SCREENW / 2 - BUTTONW / 2, 150, BUTTONW, BUTTONH, "img/button/difficulty-selected.bmp", gRenderer);
	Button selected_soundBtnMain(SCREENW / 2 - BUTTONW / 2, 250, BUTTONW, BUTTONH, "img/button/sound-selected.bmp", gRenderer);
	Button selected_backBtnMain(SCREENW / 2 - BUTTONW / 2, 350, BUTTONW, BUTTONH, "img/button/back-selected.bmp", gRenderer);
	//0 difficulty 1 sound 2 back
	int settingopt = 0;
	int isRunning = 1;
	SDL_Event e;

	SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
	selected_difficultyBtnMain.redraw();
	soundBtnMain.redraw();
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

					if (settingopt > 0)
					{
						settingopt--;
						// then redraw
						SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
						if (settingopt == 0)  //0 start              
						{
							selected_difficultyBtnMain.redraw();
							soundBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (settingopt == 1)
						{
							selected_soundBtnMain.redraw();
							difficultyBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (settingopt == 2)
						{
							soundBtnMain.redraw();
							difficultyBtnMain.redraw();
							selected_backBtnMain.redraw();
						}
					
						SDL_RenderPresent(gRenderer);
					}
					continue;
				}

				if (e.key.keysym.sym == SDLK_DOWN)
				{
			
					if (settingopt <2)
					{

						settingopt++;//


						SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
						if (settingopt == 0)
						{
							selected_difficultyBtnMain.redraw();
							soundBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (settingopt == 1)
						{
							selected_soundBtnMain.redraw();
							difficultyBtnMain.redraw();
							backBtnMain.redraw();
						}
						if (settingopt == 2)
						{
							soundBtnMain.redraw();
							difficultyBtnMain.redraw();
							selected_backBtnMain.redraw();
						}
						
						SDL_RenderPresent(gRenderer);
					}
					continue;
				}
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					return 2;
				}
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					// 0:difficuty 1:sound 2:back
					if (settingopt == 2)
					{
						return 2;
					}
					if (settingopt == 0)
					{
						return 0;
					}
					if (settingopt == 1)
					{
						return 1;
					}
				} 
			}
		}
	}
}
#include "ui.hpp"
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

SDL_Texture *LoadTextTexture1(std::string content, SDL_Renderer *renderTarget, int size)
{
	SDL_Texture *texture = nullptr;
	TTF_Font *Sans;
	Sans = TTF_OpenFont("text/Sans.ttf", size);
	SDL_Surface *surface = TTF_RenderText_Solid(Sans, content.c_str(), { 255, 0, 0 });
	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_FreeSurface(surface);
	return texture;

}

int highestScore1[3] = { 0 , 0 , 0 };
void readHighestScore1()
{
	FILE *f = fopen("text/highestscore.txt", "r");
	if (f == NULL)
	{
		return;
	}
	for (int i = 0; i < 3; i++)
	{
		fscanf(f, "%d", &highestScore1[i]);
	}
	fclose(f);
	return;
}

void showBestscores(SDL_Renderer* renderTarget)
{
	SDL_Rect r;
	SDL_Texture *line[4];
	line[0] = LoadTextTexture1("Best Scores: ", renderTarget, 20);
	line[1] = LoadTextTexture1("Easy: " + std::to_string(highestScore1[0]), renderTarget, 20);
	line[2] = LoadTextTexture1("Normal: " + std::to_string(highestScore1[1]), renderTarget, 20);
	line[3] = LoadTextTexture1("Hard: " + std::to_string(highestScore1[2]), renderTarget, 20);
	r.x = 0;
	r.y = 0;
	for (int k = 0; k < 4; k++)
	{
		SDL_QueryTexture(line[k], NULL, NULL, &r.w, &r.h);
		SDL_RenderCopy(renderTarget, line[k], NULL, &r);
		r.y += 20;
	}
	//SDL_RenderPresent(renderTarget);
}

int getOption(SDL_Renderer* gRenderer)
{
	SDL_Texture* mainTexture;
	SDL_Surface *tmp = SDL_LoadBMP("img/background.bmp");
	mainTexture = SDL_CreateTextureFromSurface(gRenderer, tmp);
	SDL_FreeSurface(tmp);

	SDL_Texture* insTexture;
	tmp = SDL_LoadBMP("img/Ins.bmp");
	insTexture = SDL_CreateTextureFromSurface(gRenderer, tmp);
	SDL_FreeSurface(tmp);


	Button startBtnMain(SCREENW / 2 - BUTTONW / 2, 90, BUTTONW, BUTTONH, "img/button/start.bmp", gRenderer);
	Button exitBtnMain(SCREENW / 2 - BUTTONW / 2, 360, BUTTONW, BUTTONH, "img/button/exit.bmp", gRenderer);
	Button instructionBtnMain(SCREENW / 2 - BUTTONW / 2, 270, BUTTONW, BUTTONH, "img/button/instructions.bmp", gRenderer);
	Button settingBtnMain(SCREENW / 2 - BUTTONW / 2, 180, BUTTONW, BUTTONH, "img/button/settings.bmp", gRenderer);
	Button selected_startBtnMain(SCREENW / 2 - BUTTONW / 2, 90, BUTTONW, BUTTONH, "img/button/start-selected.bmp", gRenderer);
	Button selected_exitBtnMain(SCREENW / 2 - BUTTONW / 2, 360, BUTTONW, BUTTONH, "img/button/exit-selected.bmp", gRenderer);
	Button selected_instructionBtnMain(SCREENW / 2 - BUTTONW / 2, 270, BUTTONW, BUTTONH, "img/button/instructions-selected.bmp", gRenderer);
	Button selected_settingBtnMain(SCREENW / 2 - BUTTONW / 2, 180, BUTTONW, BUTTONH, "img/button/setting-selected.bmp", gRenderer);
	// now we assume 0 is start, 1 is exit, 2 is instruct
	int curOp = 0;
	int isRunning = 1;
	SDL_Event e,f;

	readHighestScore1();
	// here is code draw screen
	SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
	selected_startBtnMain.redraw();
	exitBtnMain.redraw();
	instructionBtnMain.redraw();
	settingBtnMain.redraw();
	showBestscores(gRenderer);
	SDL_RenderPresent(gRenderer);
	while (isRunning)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				return 3;
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_UP)
				{
					// if user press up so we need decrease curOp

					if (curOp > 0)
					{
						curOp--;
						// then redraw
						SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
						showBestscores(gRenderer);
						if (curOp == 0)  //0 start              
						{
							selected_startBtnMain.redraw();
							exitBtnMain.redraw();
							instructionBtnMain.redraw();
							settingBtnMain.redraw();
						}
						if (curOp == 1)
						{
							selected_settingBtnMain.redraw();
							startBtnMain.redraw();
							exitBtnMain.redraw();
							instructionBtnMain.redraw();
						}
						if (curOp == 2)
						{
							selected_instructionBtnMain.redraw();
							startBtnMain.redraw();
							exitBtnMain.redraw();
							settingBtnMain.redraw();
						}
						if(curOp == 3) {
							selected_exitBtnMain.redraw(); //1 end.
							startBtnMain.redraw();
							instructionBtnMain.redraw();
							settingBtnMain.redraw();
						}
						SDL_RenderPresent(gRenderer);
					}
					continue;
				}

				if (e.key.keysym.sym == SDLK_DOWN)
				{
					// if user press down we must increase curOp
					// but if curOp==2 then current button is bttom 
					// so we dont decrease
					if (curOp <3)
					{

						curOp++;//
								// change mainTexture with another textture from image you want draw

						SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
						showBestscores(gRenderer);
						if (curOp == 0)  //0 start              
						{
							selected_startBtnMain.redraw();
							exitBtnMain.redraw();
							instructionBtnMain.redraw();
							settingBtnMain.redraw();
						}
						if (curOp == 1)
						{
							selected_settingBtnMain.redraw();
							startBtnMain.redraw();
							exitBtnMain.redraw();
							instructionBtnMain.redraw();
						}
						if (curOp == 2)
						{
							selected_instructionBtnMain.redraw();
							startBtnMain.redraw();
							exitBtnMain.redraw();
							settingBtnMain.redraw();
						}
						if (curOp == 3) {
							selected_exitBtnMain.redraw(); //1 end.
							startBtnMain.redraw();
							instructionBtnMain.redraw();
							settingBtnMain.redraw();
						}
						SDL_RenderPresent(gRenderer);
					}
					continue;
				}
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					return 3;
				}
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					// check here if current option is 0,1,2
					if (curOp == 2)
					{
						SDL_RenderCopy(gRenderer, insTexture, NULL, NULL);
						SDL_RenderPresent(gRenderer);
						while (true) {
							while (SDL_PollEvent(&f) != 0)
							{
								if (f.type == SDL_QUIT)
									return 3;
								if (f.type == SDL_KEYDOWN)
									if (f.key.keysym.sym == SDLK_ESCAPE|| f.key.keysym.sym == SDLK_SPACE)
										return -1;
							}
						}
					}
					else return curOp;
				}
			}
		}
	}
}
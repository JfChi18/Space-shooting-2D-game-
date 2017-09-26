#include<SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "ui.hpp"
#include "setting.hpp"
#include "soundcontrol.hpp"
#include "difficulty.hpp"
#include "items.hpp"

SDL_Window *window = nullptr;
SDL_Renderer *renderTarget = nullptr;
SDL_Texture *ship = nullptr;
SDL_Texture *backGround = nullptr;
SDL_Texture *gameoverimg = nullptr;
SDL_Texture* scoreMessage = nullptr;
SDL_Texture* highscoreMessage = nullptr;
SDL_Rect playerRect;
SDL_Rect scoreRect;
SDL_Rect highestscoreRect;
SDL_Rect gameoverRect;
bool isRunning = true;
bool gameover = false;
SDL_Event ev;
const Uint8 *keyState;

Mix_Music *bgm;
Mix_Chunk *chunk;

std::vector<enemy*> enemys;
enemy* temp;
std::vector<bullet*> bullets;
bullet* temp1;
std::vector<bullet*> enemybullets;
int highestScore[3] = { 0 , 0 , 0 };
int score = 0;

int movespeed = 3;
int enemyspeed = 3;
int windowWidth = 640;
int windowHeight = 480;
int shipWidth = 50;
int bulletWidth = 10;
int bulletHeight = 10;
int bulletspeed = -7;
int enemyTimer = 0;
int bulletTimer = 0;
int enemyFrequency = 20;
int bulletFrequency = 7;
int enemybulletFrequency = 50;
int enemybulletspeed = 4;
int difficuty = 0;
int volumn = 1;

//-1:main menu; 0:game board; 1:setting 2:instruction 3:exit;
int gamestate = -1;
int settingState;

SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = SDL_LoadBMP(filePath.c_str());
	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_FreeSurface(surface);
	return texture;
	
}

SDL_Texture *LoadTextTexture(std::string content, SDL_Renderer *renderTarget, int size)
{
	SDL_Texture *texture = nullptr;
	TTF_Font *Sans;
	Sans = TTF_OpenFont("text/Sans.ttf", size);
	SDL_Surface *surface = TTF_RenderText_Solid(Sans, content.c_str(), { 255, 0, 0 });
	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_FreeSurface(surface);
	return texture;

}

void storeHighestScore()
{
	FILE *f = fopen("text/highestscore.txt", "w");
	if (f == NULL)
	{
		
		return;
	}
	fprintf(f, "%d %d %d\n", highestScore[0],highestScore[1],highestScore[2]);
	fclose(f);
}

void readHighestScore()
{
	FILE *f = fopen("text/highestscore.txt", "r");
	if (f == NULL)
	{
		storeHighestScore();
		return;
	}
	for (int i = 0; i < 3; i++)
	{
		fscanf(f, "%d", &highestScore[i]);
	}
	fclose(f);
	return;
}

void restart()
{
	for (std::vector<enemy*>::iterator i = enemys.begin(); i != enemys.end();)
	{
		(*i)->destroy();
		i = enemys.erase(i);
	}
	for (std::vector<bullet*>::iterator j = bullets.begin(); j != bullets.end();)
	{
		(*j)->destroy();
		j = bullets.erase(j);
	}
	for (std::vector<bullet*>::iterator j = enemybullets.begin(); j != enemybullets.end();)
	{
		(*j)->destroy();
		j = enemybullets.erase(j);
	}
	ship = LoadTexture("img/ship.bmp", renderTarget);
	playerRect.x = (windowWidth - shipWidth) / 2;
	playerRect.y = windowHeight - 2 * shipWidth;
	playerRect.w = shipWidth;
	playerRect.h = shipWidth;
	SDL_RenderClear(renderTarget);
	SDL_DestroyTexture(gameoverimg);
	gameoverimg = nullptr;
	SDL_DestroyTexture(highscoreMessage);
	highscoreMessage = nullptr;
	SDL_RenderCopy(renderTarget, ship, NULL, &playerRect);
	SDL_RenderCopy(renderTarget, gameoverimg, NULL, NULL);
	SDL_RenderCopy(renderTarget, highscoreMessage, NULL, NULL);
	score = 0;
	scoreMessage = LoadTextTexture("Score: " + std::to_string(score), renderTarget, 20);
	SDL_RenderCopy(renderTarget, scoreMessage, NULL, &scoreRect);
	SDL_RenderPresent(renderTarget);
	Mix_PlayMusic(bgm, -1);
	gameover = false;
}

void initialization()
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();
	readHighestScore();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	bgm = Mix_LoadMUS("music/bgm.wav");
	chunk = Mix_LoadWAV("music/biubiubiu.wav");
	window = SDL_CreateWindow("Space Shooting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	backGround = LoadTexture("img/spaceshoot.bmp", renderTarget);

	gameoverRect.w = 480;
	gameoverRect.h = 320;
	gameoverRect.x = 80;
	gameoverRect.y = 80;

	scoreMessage = LoadTextTexture("Score: " + std::to_string(score), renderTarget, 20);
	highscoreMessage = LoadTextTexture("Highest Score: " + std::to_string(highestScore[difficuty]),renderTarget,40);

	scoreRect.y = 10;
	scoreRect.x = 520;
	SDL_QueryTexture(scoreMessage, NULL, NULL, &scoreRect.w, &scoreRect.h);
	highestscoreRect.y = 50;
	highestscoreRect.x = 140;
	SDL_QueryTexture(highscoreMessage, NULL, NULL, &highestscoreRect.w, &highestscoreRect.h);

	highscoreMessage = nullptr;

	restart();
	Mix_HaltMusic();
}

void createBullet()
{
	temp1 = new bullet();
	temp1->bulletRect.w = bulletWidth;
	temp1->bulletRect.h = bulletHeight;
	temp1->bulletRect.x = playerRect.x + (playerRect.w / 2) - (temp1->bulletRect.w / 2);
	temp1->bulletRect.y = playerRect.y - temp1->bulletRect.h;
	temp1->vy = bulletspeed;
	temp1->vx = 0;
	temp1->bulletTexture = LoadTexture("img/bullet.bmp", renderTarget);
	bullets.push_back(temp1);
}

void createEnemy()
{
	temp = new enemy();
	temp->type = (rand() % 3 == 0) ? 1 : 0;
	temp->enemyRect.y = 0;
	temp->enemyRect.x = rand() % (windowWidth - shipWidth);
	temp->enemyRect.w = shipWidth;
	temp->enemyRect.h = shipWidth;
	temp->vx = rand() % 7 - 3;
	temp->vy = rand() % 2 + 1;
	temp->timer = 0;
	temp->enemyTexture = (temp->type==0 )?LoadTexture("img/enemy.bmp", renderTarget): LoadTexture("img/enemy2.bmp", renderTarget);
	enemys.push_back(temp);
}

void createEnemybullet(int d, SDL_Rect r)
{
	temp1 = new bullet();
	temp1->bulletRect.w = bulletWidth;
	temp1->bulletRect.h = bulletHeight;
	temp1->bulletRect.x = r.x + (r.w / 2) - (temp1->bulletRect.w / 2);
	temp1->bulletRect.y = r.y + r.h;
	temp1->vy = enemybulletspeed;
	temp1->vx = d*enemybulletspeed;
	temp1->bulletTexture = LoadTexture("img/enemybullet.bmp", renderTarget);
	enemybullets.push_back(temp1);
}

void render()
{
	SDL_RenderClear(renderTarget);
	SDL_RenderCopy(renderTarget, backGround, NULL, NULL);
	SDL_RenderCopy(renderTarget, ship, NULL, &playerRect);
	for (std::vector<enemy*>::iterator i = enemys.begin(); i != enemys.end(); i++)
		SDL_RenderCopy(renderTarget, (*i)->enemyTexture, NULL, &(*i)->enemyRect);
	for (std::vector<bullet*>::iterator j = bullets.begin(); j != bullets.end(); j++)
		SDL_RenderCopy(renderTarget, (*j)->bulletTexture, NULL, &(*j)->bulletRect);
	for (std::vector<bullet*>::iterator j = enemybullets.begin(); j != enemybullets.end(); j++)
		SDL_RenderCopy(renderTarget, (*j)->bulletTexture, NULL, &(*j)->bulletRect);
	SDL_RenderCopy(renderTarget, highscoreMessage, NULL, &highestscoreRect);
	SDL_RenderCopy(renderTarget, gameoverimg, NULL, &gameoverRect);
	SDL_RenderCopy(renderTarget, scoreMessage, NULL, &scoreRect);
	SDL_RenderPresent(renderTarget);
}

void gameisover()
{
	gameover = true;
	SDL_DestroyTexture(ship);
	ship = nullptr;
	highestScore[difficuty] = (score > highestScore[difficuty]) ? score : highestScore[difficuty];
	storeHighestScore();
	gameoverimg = LoadTexture("img/gameover.bmp", renderTarget);
	SDL_RenderCopy(renderTarget, gameoverimg, NULL, &gameoverRect);
	Mix_HaltMusic();
	highscoreMessage = LoadTextTexture("Highest Score: " + std::to_string(highestScore[difficuty]), renderTarget, 40);
}


void quit() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(ship);
	SDL_DestroyRenderer(renderTarget);
	Mix_FreeMusic(bgm);
	Mix_FreeChunk(chunk);
	bgm = nullptr;
	chunk = nullptr;
	window = nullptr;
	ship = nullptr;
	renderTarget = nullptr;
	SDL_Quit();
	Mix_Quit();
}
int main(int argc, char* argv[])
{
	initialization();
	gamestate = getOption(renderTarget);
	if (gamestate == 3)
		isRunning = false;
	while (isRunning)
	{
		if (gamestate == 3)
			isRunning = false;
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				isRunning = false;
		}
		if (gamestate == 0) {
			if (!gameover)
			{
				if (Mix_PlayingMusic() == 0) {
					Mix_PlayMusic(bgm, -1);
				}
				Mix_VolumeMusic(20*volumn);
				Mix_VolumeChunk(chunk, 3*volumn);
				enemyTimer++;
				if (enemyTimer == enemyFrequency)
				{
					enemyTimer = 0;
					createEnemy();
				}
				for (std::vector<enemy*>::iterator i = enemys.begin(); i != enemys.end();)
				{
					(*i)->move();
					(*i)->timer++;
					if ((*i)->collision(playerRect))
					{
						gameisover();
					}
					if ((*i)->timer == enemybulletFrequency)
					{
						(*i)->timer = 0;
						if ((*i)->type == 1)
						{
							if (difficuty > 0)
							{
								createEnemybullet(0, (*i)->enemyRect);
								if (difficuty > 1)
								{
									createEnemybullet(-1, (*i)->enemyRect);
									createEnemybullet(1, (*i)->enemyRect);
								}
							}
						}
						else
							if (difficuty == 2)
								createEnemybullet(0, (*i)->enemyRect);
					}
					if ((*i)->enemyRect.y > windowHeight || (*i)->enemyRect.x > windowWidth || (*i)->enemyRect.x < 0 - shipWidth)
					{
						(*i)->destroy();
						i = enemys.erase(i);
					}
					else
					{
						i++;
					}

				}
				keyState = SDL_GetKeyboardState(NULL);
				if (keyState[SDL_SCANCODE_RIGHT])
					if (playerRect.x < windowWidth - shipWidth)
						playerRect.x += movespeed;
				if (keyState[SDL_SCANCODE_LEFT])
					if (playerRect.x>0)
						playerRect.x -= movespeed;
				if (keyState[SDL_SCANCODE_UP])
					if (playerRect.y > 0)
						playerRect.y -= movespeed;
				if (keyState[SDL_SCANCODE_DOWN])
					if (playerRect.y < windowHeight - shipWidth)
						playerRect.y += movespeed;
				if (keyState[SDL_SCANCODE_SPACE]) 
				{
					bulletTimer++;
					if (bulletTimer == bulletFrequency) {
						bulletTimer = 0;
						createBullet();
						Mix_PlayChannel(-1, chunk, 0);
					}

				}
				if (keyState[SDL_SCANCODE_ESCAPE]) {
					gamestate = -1;
					gameover = true;
					SDL_DestroyTexture(ship);
					ship = nullptr;
					Mix_HaltMusic();
				}
				for (std::vector<bullet*>::iterator j = bullets.begin(); j != bullets.end(); j++)
				{
					(*j)->move();
					bool boom = false;
					if ((*j)->bulletRect.y > windowHeight || (*j)->bulletRect.x > windowWidth || (*j)->bulletRect.x < 0 - bulletWidth)
					{
						(*j)->destroy();
						j = bullets.erase(j);
					}
					else
					{
						for (std::vector<enemy*>::iterator i = enemys.begin(); i != enemys.end(); i++)
						{
							if ((*i)->collision((*j)->bulletRect))
							{
								score = score + (*i)->type + 1;
								scoreMessage = LoadTextTexture("Score: " + std::to_string(score), renderTarget, 20);
								(*i)->destroy();
								(*j)->destroy();
								enemys.erase(i);
								bullets.erase(j);
								boom = true;
								break;
							}
						}

					}
					if (boom)
						break;
				}

				for (std::vector<bullet*>::iterator j = enemybullets.begin(); j != enemybullets.end();)
				{
					(*j)->move();
					bool boom = false;
					if ((*j)->bulletRect.y > windowHeight || (*j)->bulletRect.x > windowWidth || (*j)->bulletRect.x < 0 - bulletWidth)
					{
						(*j)->destroy();
						j = enemybullets.erase(j);
					}
					else
					{
						if ((*j)->collision(playerRect))
						{
							gameisover();
						}
						j++;
					}
				}
				render();
			}
			else
			{
				keyState = SDL_GetKeyboardState(NULL);
				if (keyState[SDL_SCANCODE_R])
				{
					restart();
				}
				if (keyState[SDL_SCANCODE_ESCAPE])
				{
					gamestate = -1;
				}
			}
		}
		else if (gamestate == -1)
		{
			gamestate = getOption(renderTarget);
			if (gamestate == 0)
				restart();
		}
		else if (gamestate == 1)
		{
			settingState = getSettingoption(renderTarget);
			if (settingState == 0)
			{
				int temp1 = getDifficuty(renderTarget);
				if (temp1!=-2) 
					difficuty = temp1;
				gamestate = -1;
				if (difficuty == -1)
				{
					gamestate = 3;
				}
			}
			else if (settingState == 1)
			{
				int temp1 = getVolumn(renderTarget);
				if (temp1 != -2)
					volumn = temp1;
				gamestate = -1;
				if (volumn == -1)
				{
					gamestate = 3;
				}
			}
			else if (settingState == 2)
			{
				gamestate = -1;
			}
			else if (settingState == -1)
			{
				gamestate = 3;
			}
		}
	}
	quit();
	return 0;
}
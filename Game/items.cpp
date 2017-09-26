#include<SDL2/SDL.h>
#include "items.hpp"

void enemy::move()
{
	enemyRect.x += vx;
	enemyRect.y += vy;
}

void enemy::destroy()
{
	SDL_DestroyTexture(this->enemyTexture);
	this->enemyTexture = nullptr;
}

bool enemy::collision(SDL_Rect another)
{
	int r1, r2, x1, x2, y1, y2;
	r1 = this->enemyRect.w / 2;
	x1 = this->enemyRect.x + r1;
	y1 = this->enemyRect.y + r1;
	r2 = another.w / 2;
	x2 = another.x + r2;
	y2 = another.y + r2;
	if ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) < (r1 + r2)*(r1 + r2))
		return true;
	else
		return false;
}

void bullet::move()
{
	bulletRect.y += vy;
	bulletRect.x += vx;
}

void bullet::destroy()
{
	SDL_DestroyTexture(this->bulletTexture);
	this->bulletTexture = nullptr;
}

bool bullet::collision(SDL_Rect another)
{
	int r1, r2, x1, x2, y1, y2;
	r1 = this->bulletRect.w / 2;
	x1 = this->bulletRect.x + r1;
	y1 = this->bulletRect.y + r1;
	r2 = another.w / 2;
	x2 = another.x + r2;
	y2 = another.y + r2;
	if ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) < (r1 + r2)*(r1 + r2))
		return true;
	else
		return false;
}

Button::Button(int _x, int _y, int _w, int _h, char *file, SDL_Renderer *_render)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	render = _render;
	SDL_Surface *surface = SDL_LoadBMP(file);
	texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
}

void Button::redraw()
{
	SDL_Rect SrcR;
	SDL_Rect DestR;
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.h = h;
	SrcR.w = w;
	DestR.x = x;
	DestR.y = y;
	DestR.h = h;
	DestR.w = w;
	SDL_RenderCopy(render, texture, NULL, &DestR);
}
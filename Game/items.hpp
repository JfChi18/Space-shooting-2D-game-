#ifndef ITEM_H
#define ITEM_H

#include<SDL2/SDL.h>
class enemy {
public:
	SDL_Rect enemyRect;
	SDL_Texture *enemyTexture = nullptr;
	int vx, vy, timer, type;

	void move();
	void destroy();
	bool collision(SDL_Rect another);

};

class bullet {
public:
	SDL_Rect bulletRect;
	SDL_Texture *bulletTexture = nullptr;
	int vx, vy;

	void move();
	void destroy();
	bool collision(SDL_Rect another);

};

class Button
{
public:
	int w;
	int h;
	int x;
	int y;
	SDL_Texture* texture;
	SDL_Renderer *render;
	Button(int _x, int _y, int _w, int _h, char *file, SDL_Renderer *_render);
	void redraw();
};
#endif
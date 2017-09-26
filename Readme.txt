Game: Space Shooter

Language: C++
Library used: SDL, SDL_ttf, SDL_mixer

Project Description: 
Our game, Space Shooter, is an imitation of Space Invaders and various other space shooting games. In this game, we have a spaceship, which is controlled by you, and two enemies, 
the Skull and the Ghost. The goal of this game is to kill as many enemies before the enemies kill you. That is easier said than done, especially depending on the level you play at. 
Easy mode is for beginners--the enemies don't fire at anything at you, you just shoot them. In normal mode, Skull is shooting at you with rapid firing power, while Ghost is just 
roaming around. In difficult mode, it's almost impossible to stay alive when both Skull and Ghost are overwhelming you with their bullets. Try to stay alive soldier! You're our last hope.


Project Timeline:
Week 1-
	Made some basic decisions about the game.
	Created the window and background
	Spaceship with left, right, up, down movement and  with weapon, which can be fired by using the spacebar
	Developed one enemy called Skull. 
		- worth one point
		- fires one bullet, depending on difficulty

Week 2-
	Sound effects for background music and when the weapon is fired. 
	Collision for when:
		- the bullet of the spaceship collides with the enemy
		- the spaceship and enemy collide
		- the bullet of the enemy collides with the spaceship
	Main interface
		- GUI with start, exit, instruction and setting options
	Game Over and restart screen

Week 3-
	Made UI and game more user friendly
	Addition of second enemy with weapons: Ghost
		- worth two points 
		- fires three bullets, depending on difficulty
	Change volume (options of 1, 2, 3, 4)
	Change difficulty
		- easy: enemies don't fire any weapons
		- normal: Skull fires a weapon, and Ghost does not 
		- difficult: Skull and Ghost fire both their weapons
	Recording of highest score


#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Player.h"

class Ball{
	SDL_Texture* ballTexture;
	SDL_Rect rectBall;
	int speedBallX;
	int speedBallY;

	public:
		Ball();
		
		void close();

		void eventMovimentBall();

		SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer);

		bool loadImage(SDL_Renderer *renderer);

		void render(SDL_Renderer *renderer);

		bool collisionBallWithScreen();

		void collisionBallWithPlayer(Player player);

		void setInvertion();

		SDL_Rect getRectBall();

		int getWidthBall();

		int getHeightBall();
};

#endif
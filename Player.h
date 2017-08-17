#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Player{
	SDL_Texture* playerTexture;
	SDL_Rect rectPlayer;
	int speedPlayer;

	public:
		Player();

		void close();

		void eventMovimentPlayer();

		SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer);

		bool loadImage(SDL_Renderer *renderer);

		void render(SDL_Renderer *renderer);

		void collisionPlayerWithScreen();

		SDL_Rect getRectPlayer();

		int getWidthPlayer();

		int getHeightPlayer();

};

#endif
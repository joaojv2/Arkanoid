#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Ball.h"

class Bricks{
	SDL_Texture* brickTexture;
	SDL_Rect rectBrick;
	int** matrixBricks;

	public:
		int getPosBlockX(int j);

		int getPosBlockY(int i);

		void draw_bricks(SDL_Renderer *renderer);

		void createBricks();

		void close();

		SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer);

		bool loadImage(SDL_Renderer *renderer);

		void collisionBallWithBricks(Ball *ball, int *point);
};
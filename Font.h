#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;


class Font{
	TTF_Font *font;

	SDL_Texture* texture;

	int mWidth;
	int mHeight;

	public:
		void renderFont( int x, int y, SDL_Renderer *renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		void setTextToLoad(string text, SDL_Renderer *renderer);

		bool loadFont(string nameFont, int sizeFont);

		bool loadFromRenderedText(string textureText, SDL_Color textColor, SDL_Renderer *renderer);

		void close();

		int getWidth();
		
		int getHeight();
};

#endif
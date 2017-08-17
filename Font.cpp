#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>

#include "Font.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

bool Font::loadFromRenderedText(string textureText, SDL_Color textColor, SDL_Renderer *renderer){
	SDL_Surface* textSurface = TTF_RenderText_Solid(Font::font, textureText.c_str(), textColor);

	if( textSurface == NULL ){
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else{
        Font::texture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( Font::texture == NULL ){
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else{
			Font::mWidth = textSurface->w;
			Font::mHeight = textSurface->h;
		}

		SDL_FreeSurface( textSurface );
	}

	return Font::texture != NULL;
}

bool Font::loadFont(string nameFont, int sizeFont){
	bool success = true;

	Font::font = TTF_OpenFont(nameFont.c_str(), sizeFont);
	
	if( Font::font == NULL ){
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	return success;
}

void Font::setTextToLoad(string text, SDL_Renderer *renderer){
	SDL_Color textColor = { 0, 0, 0 };
	if(!loadFromRenderedText(text , textColor, renderer)){
		printf( "Failed to render text texture!\n" );
	}
}

void Font::renderFont( int x, int y, SDL_Renderer *renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
	SDL_Rect renderQuad = { x, y, Font::mWidth, Font::mHeight };

	if( clip != NULL ){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx( renderer, Font::texture, clip, &renderQuad, angle, center, flip );
}

void Font::close(){
	TTF_CloseFont( Font::font );
		Font::font = NULL;

	SDL_DestroyTexture(Font::texture);
		Font::texture = NULL;
}

int Font::getWidth(){
	return Font::mWidth;
}

int Font::getHeight(){
	return Font::mHeight;
}
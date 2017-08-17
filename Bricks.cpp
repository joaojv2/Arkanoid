#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Bricks.h"
#include "Ball.h"

using namespace std;

const int ROW = 4;
const int COLUMN = 15;
const int WIDTH = 40;
const int HEIGHT = 15;

int Bricks::getPosBlockX(int j){
	return j * (WIDTH + 2) + 5;
}

int Bricks::getPosBlockY(int i){
	return  i * (HEIGHT + 2) + 20;
}
void Bricks::draw_bricks(SDL_Renderer *renderer){
	for(int i = 0; i < ROW; i ++) {
		for(int j = 0; j < COLUMN; j ++) {
			if(matrixBricks[i][j] != -1){
				rectBrick.x = Bricks::getPosBlockX(j);
				rectBrick.y = Bricks::getPosBlockY(i);
				rectBrick.w = WIDTH;
				rectBrick.h = HEIGHT;

				SDL_Rect rectBrick = Bricks::rectBrick;
				
				SDL_RenderCopy( renderer, Bricks::brickTexture, NULL , &rectBrick);
			}
		}
	}
}
void Bricks::createBricks() {
	Bricks::matrixBricks = (int**) malloc(ROW * sizeof(int*));

	for(int i = 0; i < COLUMN; i ++)
		Bricks::matrixBricks[i] =(int*) malloc(COLUMN * sizeof(int));
}

void Bricks::close(){
	SDL_DestroyTexture(Bricks::brickTexture);
		Bricks::brickTexture = NULL;
}

SDL_Texture* Bricks::loadTexture(std::string path, SDL_Renderer *renderer){
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ){
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else{
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL ){
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

bool Bricks::loadImage(SDL_Renderer *renderer){
	bool success = true;

	Bricks::brickTexture = loadTexture("Images/bricks.png", renderer);

	if(Bricks::brickTexture == NULL){
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

void Bricks::collisionBallWithBricks(Ball *ball, int *point){
	SDL_Rect rectBall = ball->getRectBall();
	bool collision = false;

	for(int i = 0; i < ROW; i ++) {
		for(int j = 0; j < COLUMN; j ++) {
			if(Bricks::matrixBricks[i][j] != -1){
				if(rectBall.x < Bricks::getPosBlockX(j) + WIDTH && rectBall.x + ball->getWidthBall() > Bricks::getPosBlockX(j) && rectBall.y < Bricks::getPosBlockY(i) + HEIGHT && rectBall.y + ball->getHeightBall() > Bricks::getPosBlockY(i)){
					Bricks::matrixBricks[i][j] = -1;
					collision = true;
					ball->setInvertion();
					*point += 100;
					break;
				}
			}
		}
		if(collision)
			break;
	}
}
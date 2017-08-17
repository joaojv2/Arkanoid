#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stdlib.h>

#include "Ball.h"
#include "Player.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int WIDTH = 16;
const int HEIGHT = 16;

using namespace std;

Ball::Ball(){
	Ball::rectBall.x = SCREEN_WIDTH / 2 - WIDTH / 2;
	Ball::rectBall.y = SCREEN_HEIGHT / 2;
	Ball::rectBall.w = WIDTH;
	Ball::rectBall.h = HEIGHT;
	Ball::speedBallX = 2;
	Ball::speedBallY = 7;
}

void Ball::eventMovimentBall(){
	Ball::rectBall.y += Ball::speedBallY;
	Ball::rectBall.x += Ball::speedBallX;
}

void Ball::close(){
	SDL_DestroyTexture(Ball::ballTexture);
		Ball::ballTexture = NULL;
}

SDL_Texture* Ball::loadTexture(std::string path, SDL_Renderer *renderer){
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

bool Ball::loadImage(SDL_Renderer *renderer){
	bool success = true;

	Ball::ballTexture = loadTexture("Images/ball.png", renderer);

	if(Ball::ballTexture == NULL){
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

void Ball::render(SDL_Renderer *renderer){
	SDL_Rect rectBrick = Ball::rectBall;

	SDL_RenderCopy(renderer, Ball::ballTexture, NULL , &rectBall);
}

bool Ball::collisionBallWithScreen(){
	bool game = true;

	if(Ball::rectBall.x < 0){
		Ball::speedBallX *= -1;
	}

	if(Ball::rectBall.x > SCREEN_WIDTH - WIDTH){
		Ball::speedBallX *= -1;
	}

	if(Ball::rectBall.y < 0){
		Ball::speedBallY *= -1;
	}

	if(Ball::rectBall.y > SCREEN_HEIGHT - HEIGHT){
		game = false;
	}

	return game;
}

void Ball::collisionBallWithPlayer(Player player){
	srand(time(NULL));
	int x = rand() % 4 + 1;

	SDL_Rect rectPlayer = player.getRectPlayer();

	if(Ball::rectBall.x < rectPlayer.x + player.getWidthPlayer() && Ball::rectBall.x + WIDTH > rectPlayer.x && Ball::rectBall.y < rectPlayer.y + player.getHeightPlayer() && Ball::rectBall.y + HEIGHT > rectPlayer.y){
		Ball::speedBallY *= -1;
		if(Ball::speedBallX < 0)
			Ball::speedBallX = -x;
		if(Ball::speedBallX > 0)
			Ball::speedBallX = x;
	}
}

void Ball::setInvertion(){
	Ball::speedBallY *= -1;
	Ball::speedBallX *= -1;
}

SDL_Rect Ball::getRectBall(){
	return Ball::rectBall;
}

int Ball::getWidthBall(){
	return WIDTH;
}

int Ball::getHeightBall(){
	return HEIGHT;
}

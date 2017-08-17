#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Player.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int WIDTH = 100;
const int HEIGHT = 15;

using namespace std;

Player::Player(){
	Player::rectPlayer.x = SCREEN_WIDTH / 2 - WIDTH / 2;
	Player::rectPlayer.y = SCREEN_HEIGHT - HEIGHT;
	Player::rectPlayer.w = WIDTH;
	Player::rectPlayer.h = HEIGHT;
	Player::speedPlayer = 5;
}

void Player::eventMovimentPlayer(){
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if(state[SDL_SCANCODE_LEFT])
		Player::rectPlayer.x += -speedPlayer;

	else if(state[SDL_SCANCODE_RIGHT])
		Player::rectPlayer.x += speedPlayer;
}

void Player::close(){
	SDL_DestroyTexture(Player::playerTexture);
		Player::playerTexture = NULL;
}

SDL_Texture* Player::loadTexture(std::string path, SDL_Renderer *renderer){
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

bool Player::loadImage(SDL_Renderer *renderer){
	bool success = true;

	Player::playerTexture = loadTexture("Images/player.png", renderer);

	if(Player::playerTexture == NULL){
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

void Player::render(SDL_Renderer *renderer){
	SDL_Rect rectBrick = Player::rectPlayer;

	SDL_RenderCopy(renderer, Player::playerTexture, NULL , &rectPlayer);
}

void Player::collisionPlayerWithScreen(){
	if(Player::rectPlayer.x < 0)
		Player::rectPlayer.x += Player::speedPlayer;

	if(Player::rectPlayer.x > SCREEN_WIDTH - WIDTH)
		Player::rectPlayer.x -= Player::speedPlayer;
}

SDL_Rect Player::getRectPlayer(){
	return Player::rectPlayer;
}

int Player::getWidthPlayer(){
	return WIDTH;
}

int Player::getHeightPlayer(){
	return HEIGHT;
}
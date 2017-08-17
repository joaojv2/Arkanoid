#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>

#include "Bricks.h"
#include "Player.h"
#include "Ball.h"
#include "Font.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


using namespace std;

bool quit = false;

int point = 0;

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

Bricks bricks;
Player player;
Ball ball;
Font font;

bool init() {
	bricks.createBricks();

	bool success = true;

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if( TTF_Init() == -1 ){
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	if(window == NULL){
		cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
		success = false;
	}
	else{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if(renderer == NULL){
			cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}		
		else{
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			int imgFlags = IMG_INIT_PNG;

			if(!(IMG_Init(imgFlags) & imgFlags)){
				cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
                success = false;
            }
		}
	}

	return success;
}

void close(){
	bricks.close();
	player.close();
	ball.close();
	font.close();

    SDL_DestroyRenderer(renderer);
    	renderer = NULL;

    SDL_DestroyWindow(window);
    	window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char const *argv[]){
	if( !init() ){
		cout << "Failed to initialize!" << endl;
	}
	else{
		if(!bricks.loadImage(renderer) || !player.loadImage(renderer) || !ball.loadImage(renderer) || !font.loadFont("Fonts/Naughty Squirrel Demo.otf" , 16)){
			cout << "Failed to load media!" << endl;
		}
		else{
			bool quit = false;
			SDL_Event e;

			while( !quit ){
				unsigned frame = SDL_GetTicks();					

				font.setTextToLoad("Pontuacao: " + SSTR(point), renderer);

				while( SDL_PollEvent( &e ) != 0 ){
					if( e.type == SDL_QUIT ){
						quit = true;
					}
				}

				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );

				if(ball.collisionBallWithScreen()){
					bricks.draw_bricks(renderer);
					player.render(renderer);
					ball.render(renderer);
					font.renderFont(0, 0, renderer);

					player.eventMovimentPlayer();
					ball.eventMovimentBall();

					player.collisionPlayerWithScreen();
					ball.collisionBallWithPlayer(player);
					bricks.collisionBallWithBricks(&ball, &point);			

				}else{
					font.loadFont("Fonts/Naughty Squirrel Demo.otf" , 25);
					font.setTextToLoad("Voce perdeu! Pontuacao: " + SSTR(point), renderer);
					font.renderFont((SCREEN_WIDTH  - font.getWidth() ) / 2, (SCREEN_HEIGHT - font.getHeight()) / 2, renderer);
				}


				SDL_RenderPresent( renderer );

			    if (SDL_GetTicks() - frame < SCREEN_TICK_PER_FRAME){
			     	SDL_Delay(SCREEN_TICK_PER_FRAME - (SDL_GetTicks() - frame));
			    }
			}
			
		}
	}

	close();

	return 0;
}
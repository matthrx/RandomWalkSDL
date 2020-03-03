/*
 * Screen.cpp
 *
 *  Created on: Feb 29, 2020
 *      Author: matthieu
 */

#include <iostream>
#include <unistd.h>


using namespace std;

#include "Screen.h"

Screen::Screen(): window(NULL), buffer(NULL), texture(NULL), renderer(NULL), x(NULL), y(NULL){

}

Screen::~Screen() {
	// TODO Auto-generated destructor stub
}


bool Screen::init(void){
	getRealColor();
	x = new int;
	y = new int;
	*x = WIDTH_WINDOW/2;
	*y = HEIGHT_WINDOW/2;
	cout << "Ok";
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
	    	return false;
		}

	   this->window = SDL_CreateWindow("Random Walk",
	                                           SDL_WINDOWPOS_CENTERED,
	                                           SDL_WINDOWPOS_CENTERED,
	                                           WIDTH_WINDOW, HEIGHT_WINDOW,
											   SDL_WINDOW_SHOWN);

	    if (window == NULL){
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
	    	SDL_Quit();
	    	return false;
	    }
	   this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	   if (this->renderer == NULL){
		   SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't initialize SDL Renderer %s", SDL_GetError());
		   SDL_DestroyWindow(window);
		   SDL_Quit();
	   }

	   this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			   WIDTH_WINDOW, HEIGHT_WINDOW);

	   if (texture == NULL){
		   SDL_LogError(SDL_LOG_CATEGORY_ERROR, "COuldn't initialize SDL Texture %s", SDL_GetError());
		   SDL_DestroyRenderer(renderer);
		   SDL_DestroyWindow(window);
		   SDL_Quit();
	   }

	   // very likely to succeed
	   buffer =  new Uint32[WIDTH_WINDOW*HEIGHT_WINDOW];
	   if (this->buffer == NULL){
		   SDL_DestroyRenderer(renderer);
		   SDL_DestroyWindow(window);
		   SDL_Quit();
		   std::cout << "Error when initializing " << std::endl;
	   }
	   // we just created a buffer with a size of width*height
	   memset(this->buffer, 0xFF, WIDTH_WINDOW*HEIGHT_WINDOW*sizeof(Uint32)); // Allow to put in white, allow to set a block of
	   //memory with a specific value, value can be hexa or 10Base
	   std::cout << (this->buffer)[12345] << std::endl;
	   std::cout << sizeof(unsigned int)*8 << std::endl;


	 return true;
}


void Screen::update(void){
	   SDL_UpdateTexture(this->texture, NULL, this->buffer, WIDTH_WINDOW*sizeof(Uint32));
	   SDL_RenderClear(renderer);
	   SDL_RenderCopy(renderer, texture, NULL, NULL); // NULL indicates we want to update whole screen
	   SDL_RenderPresent(renderer); // Display renderer to the screen
}

void Screen::handleSingleMouvementParticule(void){
	unsigned short dx = rand() % 10;
	unsigned short dy = rand() % 10;
	bool isPositiveX = rand() % 2;
	bool isPositiveY = rand() % 2;
	if (isPositiveX && isPositiveY) {(*x)+=dx; (*y)+=dy;}
	else if (isPositiveX && !(isPositiveY)){(*x)+=dx; (*y)-=dy;}
	else if (!(isPositiveX) && isPositiveY){(*x)-=dx; (*y)+=dy;}
	else { (*x)-=dx; (*y)-=dy;}
	*x %= WIDTH_WINDOW;
	*y %= HEIGHT_WINDOW;
	std::cout << "In it" << std::flush;
	setPixel();

}


void Screen::processEvent(){
	std::cout << "Running..." << std::flush;
	SDL_Event event;
	while (!(close)){
		usleep(MILLISECONDS);
		handleSingleMouvementParticule();
		update();
		while (SDL_PollEvent(&event)) {
			switch(event.type) {

			case SDL_KEYUP:
				std::cout << "KeyUp !" << std::endl;
				break;
			case SDL_QUIT:
				close = true;
				break;
			}
		}
	}
}

void Screen::getRealColor(void){
	this->color += RED;
	this->color <<= 8;
	this->color += GREEN;
	this->color <<= 8;
	this->color += BLUE;
	this->color <<= 8;
	this->color += ALPHA;
}

void Screen::setPixel(void){
	cout << "Value of x " << *x << endl;
	(this->buffer)[abs(*y) * WIDTH_WINDOW + abs(*x)] = this->color;
}

void Screen::quit(){
	SDL_DestroyTexture(this->texture);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	delete [] this->buffer;
	delete x,y;
	SDL_Quit();
}

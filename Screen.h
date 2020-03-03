/*
 * Screen.h
 *
 *  Created on: Feb 29, 2020
 *      Author: matthieu
 */


#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

class Screen {

public:
	const static unsigned int MILLISECONDS = 500;
	const static int WIDTH_WINDOW = 800;
	const static int HEIGHT_WINDOW  = 800;
	const static unsigned char BLUE = 0xFF;
	const static unsigned char GREEN = 0x00;
	const static unsigned char RED = 0x00;
	const static unsigned char ALPHA = 0XFF;
	Uint32 color;
	int* x;
	int* y;
private:
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Window *window;
	Uint32 *buffer;

	bool close = false;

public:
	Screen();
	virtual ~Screen();
	bool init(void);
	void quit();
	void update();
	void processEvent(void);
	void getRealColor(void);
	void setPixel(void);
	void handleSingleMouvementParticule(void);
	// getters & setters
	bool getClose(void){return this->close;};
	void setClose(bool close){this->close = close;};
	void setPixel(int x, int y, Uint8 green, Uint8 red, Uint8 blue);

};

#endif /* SCREEN_H_ */

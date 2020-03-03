/*
 * main.cpp
 *
 *  Created on: Feb 29, 2020
 *      Author: matthieu
 *
 * Consist of simulating a particle explosion through a pretty mathematical approach
 */

#include <iostream>
#include <SDL.h>

#include "Screen.h"

using namespace std;

int main(void){
	Screen *screen = new Screen;
	screen->init();

	screen->processEvent();

	cout << "Over ! " << endl;
	screen->quit();
    delete screen;

	return 0;
}

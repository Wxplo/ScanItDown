#ifndef FILTER_H_
#define FILTER_H_
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "pixel.operations.h"
void binarisation(SDL_Surface *s);
void grayscale(SDL_Surface *s);
#endif

#ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
# include <stdlib.h>
# include <SDL.h>
 
Uint32 getpix(SDL_Surface *s, int x, int y);
void putpix(SDL_Surface *s, int x, int y, Uint32 pix);
void DrawLine(SDL_Surface *img, int y);

# endif

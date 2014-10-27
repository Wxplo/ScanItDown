#include "filter.h"

void binarisation(SDL_Surface *s)
{
	/*Parcours l'image et putpix(noir ou blanc) */
	int x, y,currentpix;
	Uint8 r, g, b;
	int myArray[s->w][s->h];
	for(x = 0; x < s->w; x++) {
		for(y = 0; y < s->h; y++) {
			SDL_GetRGB(getpix(s, x, y), s->format, &r, &g, &b);
			currentpix=(r+g+b)/3;
			if(currentpix<180)
				myArray[x][y] =1; 
			else
				myArray[x][y]=0;
		}
	}  

	for(x = 0; x < s->w; x++) {
		for(y = 0; y < s->h; y++) {
		   if(myArray[x][y]==1)
		     {putpix(s, x, y, SDL_MapRGB(s->format, 0, 0, 0));}

		   else
		     {putpix(s, x, y, SDL_MapRGB(s->format, 255, 255, 255));}
		}
	}

}

void grayscale(SDL_Surface *s)
{
	int x, y;
	Uint8 r, g, b, c;

	for(x = 0; x < s->w; x++) {
		for(y = 0; y < s->h; y++) {
			SDL_GetRGB(getpix(s, x, y), s->format, &r, &g, &b);
			c = r * .3 + g * .6 + b * .1;
			putpix(s, x, y, SDL_MapRGB(s->format, c, c, c));
		}
	}
}

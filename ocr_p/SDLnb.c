#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "segstruct.h"
#include "pixel_operations.h"
#include "pixel_operations.c"
#include "filter.h"
#include "filter.c"
/*void binarisation(SDL_Surface *s)
{
	//Parcours l'image et putpix(noir ou blanc) 
	unsigned int x, y,currentpix;
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

*/
int segline(SDL_Surface *img,struct line *line_tab,int sizetab )
{
	//Variable
	int x,y ;
	int onLine=0;
	for(y=0 ; y<=img->h ; y++)
	{
		//Parcour l'image en width, si pixel = blanc,continue, sinon
		for (x=0;
				(getpix(img,x,y)==SDL_MapRGB(img->format,255,255,255)) && (x< img->w); 
				x++);
	
		
		if(x!= img ->w && onLine==0) //Début de ligne,n'a pas fini de parcourir, et a recontré un pixel noir
			{
				DrawLine(img,y);
				onLine = 1; //on est sur une ligne
				line_tab[sizetab].yb= y-1;
			}

		if(x== img ->w && onLine==1)
		{
			DrawLine(img,y);
			onLine = 0 ;
			line_tab[sizetab].ye=y;
			sizetab=sizetab+ 1;
		}
		
	}
	return 0;
}
int main(int argc, char **argv)
{
	//Variable
	char filename_in[256];
	char filename_out[256];
	SDL_Surface *scr, *bmp;
	//pour segline
	int size=1;
//	int *sizetab=&(size);
	struct line line_tab[100];
	struct line p;
	p.yb=0;
	p.ye=bmp->h;
	line_tab[0]=p;
	/*Rensigne le nom de l'image*/
	printf("\nEntrez le nom du fichier BMP : ");
	fgets(filename_in, sizeof filename_in, stdin);
	filename_in[strlen(filename_in) - 1] = 0;
	printf("\nEntrez le nom du fichier de sortie: ");
	fgets(filename_out, sizeof filename_out, stdin);
	filename_out[strlen(filename_out) - 1] = 0;

	bmp = SDL_LoadBMP(filename_in);
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
	if(!(scr = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE)))
		return 2;
	/*  if(!(bmp = SDL_LoadBMP("bird.bmp")))
	    return 3;*/

	//  grayscale(bmp);
	binarisation(bmp);
	segline(bmp,line_tab,size);
	SDL_SaveBMP(bmp,filename_out);
	SDL_BlitSurface(bmp, 0, scr, 0);
	SDL_Flip(scr);


	while(1) {
		SDL_Event e;
		SDL_WaitEvent(&e);
		if(e.type == SDL_QUIT)
			break;
	}
	SDL_FreeSurface(bmp);
	SDL_Quit();
	return 0;
}

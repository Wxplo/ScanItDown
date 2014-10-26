#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "segstruct.h"
#include "pixel_operations.h"
#include "pixel_operations.c"
#include "filter.h"
#include "filter.c"


void Bloc(SDL_Surface *s)
{
        //Parcours l'image et putpix(noir ou blanc) 
        unsigned int x, y,currentpix;
        Uint8 r, g, b;
        int myArrayX[s->w][s->h];
	int myArrayY[s->w][s->h];
	

	//Binarisation
        for(x = 0; x < s->w; x++) {
                for(y = 0; y < s->h; y++) {
                        SDL_GetRGB(getpix(s, x, y), s->format, &r, &g, &b);
                        currentpix=(r+g+b)/3;
                        if(currentpix<180){
                               	 myArrayY[x][y] = 1;
				 myArrayX[x][y] = 1;
			} 
                        else{
				myArrayY[x][y] = 0;
                                myArrayX[x][y] = 0;
			}
                }
        }

	//Lissage horizontal
	int i,j;
//	int nb_space = 0;
	int threshold = 20;

	for(y = 0; y< s->h; y++){
		for( x = 0; x < s->w; x++){
			if(myArrayX[x][y] == 1 && myArrayX[x+1][y] == 0){
				for(i = x+1 ; myArrayX[i][y] == 0 && i< s->w; i++){
						myArrayX[i][y]= 1;
				}
			}		
	
	}

}

	//Lissage vertical
	for(x= 0; x < s->w; x++) {
                for(y = 0; y< s->h; y++){
                        if(myArrayY[x][y] == 1 && myArrayY[x][y+1] == 0){
                                 for(i = y+1; i < s->h; i++)       
					 	myArrayY[x][i] = 1;
			}
                 }

         }
	int size = 0;
	struct letter *bloc_tab;
	int *sizetab = &(size);
		
	/* BLOC DE TEXTE */
       for(x = 0; x < s->w; x++) {
                for(y = 0; y < s->h; y++) {
                        if(myArrayX[x][y] == 1 &&  myArrayY[x][y] == 1)
                        {putpix(s, x, y, SDL_MapRGB(s->format, 0, 0, 0));}
			
                        else
                        {putpix(s, x, y, SDL_MapRGB(s->format, 255, 255, 255));}
                }
        }

 	/*--- SEGMENTATION BLOC EN VERT--- */
       
	/* En largeur*/

	for(i = 0; i < s->h; i++){
                for (j = 0; j < s->w
                            && (getpix(s,j,i) == SDL_MapRGB(s->format,255,255,255))
			    &&(getpix(s,j,i+6) == SDL_MapRGB(s->format,255,255,255)) ;
                            j++);

                if(j == s->w){	
			DrawLine(s, 0, i, s->w); 
		} 
        }

	/*En Hauteur*/

	for(i = 0; i < s->w; i++){
                for (j = 0; j < s->h
                            && ((getpix(s,i,j) == SDL_MapRGB(s->format,255,255,255))
                            ||(getpix(s,i,j) == SDL_MapRGB(s->format,0,250,0))); 
			    j++);

                if(j == s->h){
                           DrawColumn(s, i, 0, s->h);
                }
        }

/*	for(i = 0; i < s->w; i++){
		for(j = 0; j <s->h; j++){
			if(((getpix(s,i,j) == SDL_MapRGB(s->format,255,255,255))
			    &&(getpix(s,i-1,j) == SDL_MapRGB(s->format,0,250,0)))
		            &&(getpix(s,i,j-1) == SDL_MapRGB(s->format,0,250,0)))
				{	
					
					bloc_tab[*sizetab].xb = i;
					bloc_tab[*sizetab].yb = j;
					//printf("%d", bloc_tab[*sizetab]);
					*sizetab= *sizetab + 1;
					//putpix(s, i, j, SDL_MapRGB(s->format, 0, 0, 250));}
				}
			}
	}*/


}

int main(int argc, char **argv)
{
	//Variable
	char filename_in[256];
	char filename_out[256];
	SDL_Surface *scr, *bmp;

	/*Renseigne le nom de l'image*/
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

	Bloc(bmp);

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

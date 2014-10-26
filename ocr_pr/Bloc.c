#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "segstruct.h"
#include "pixel_operations.h"
#include "pixel_operations.c"
#include "filter.h"
#include "filter.c"
#include "Bloc.h"

void Bloc(SDL_Surface *s)
{

        unsigned int x, y,currentpix;
        Uint8 r, g, b;
        int myArrayX[s->w][s->h];
	int myArrayY[s->w][s->h];
	

	//Binarization
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

	//Horizontal smoothing
	int i,j;

	for(y = 0; y< s->h; y++){
		for( x = 0; x < s->w; x++){
			if(myArrayX[x][y] == 1 && myArrayX[x+1][y] == 0){
				for(i = x+1 ; myArrayX[i][y] == 0 && i< s->w; i++){
						myArrayX[i][y]= 1;
				}
			}		
	
	}

}

	//Vertical smoothing
	for(x= 0; x < s->w; x++) {
                for(y = 0; y< s->h; y++){
                        if(myArrayY[x][y] == 1 && myArrayY[x][y+1] == 0){
                                 for(i = y+1; i < s->h; i++)       
					 	myArrayY[x][i] = 1;
			}
                 }

         }
	
	/* Combining smoothing */
       for(x = 0; x < s->w; x++) {
                for(y = 0; y < s->h; y++) {
                        if(myArrayX[x][y] == 1 &&  myArrayY[x][y] == 1)
                        {putpix(s, x, y, SDL_MapRGB(s->format, 0, 0, 0));}
			
                        else
                        {putpix(s, x, y, SDL_MapRGB(s->format, 255, 255, 255));}
                }
        }

 	/*--- BLOC SEGMENTATION in green --- */
       
	/* In width */

	for(i = 0; i < s->h; i++){
                for (j = 0; j < s->w
                            && (getpix(s,j,i) == SDL_MapRGB(s->format,255,255,255))
			    &&(getpix(s,j,i+6) == SDL_MapRGB(s->format,255,255,255)) ;
                            j++);

                if(j == s->w){	
			DrawLine(s, 0, i, s->w); 
		} 
        }

	/* In height */

	for(i = 0; i < s->w; i++){
                for (j = 0; j < s->h
                            && ((getpix(s,i,j) == SDL_MapRGB(s->format,255,255,255))
                            ||(getpix(s,i,j) == SDL_MapRGB(s->format,0,250,0))); 
			    j++);

                if(j == s->h){
                           DrawColumn(s, i, 0, s->h);
                }
        }

}

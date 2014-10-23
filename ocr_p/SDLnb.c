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
int segline(SDL_Surface *img,struct line *line_tab,int *sizetab )
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
				DrawLine(img,y-1);
				onLine = 1; //on est sur une ligne
				line_tab[*sizetab].yb= y-1;
			}

		if(x== img ->w && onLine==1)
		{
			DrawLine(img,y);
			onLine = 0 ;
			line_tab[*sizetab].ye=y;
			*sizetab=*sizetab+ 1;
		}
		
	}
	return 0;
}
void DrawColumn(SDL_Surface *img, int beginx, int beginy,int end)
{
	int y; 
	for (y=beginy; y< end;y++)
        putpix(img,beginx,y , SDL_MapRGB(img->format, 0,250,0));
}
void DrawColumnB(SDL_Surface *img, int beginx, int beginy,int end)
{
        int y;
        for (y=beginy; y< end;y++)
        putpix(img,beginx,y , SDL_MapRGB(img->format, 255,0,0));
}

void DrawLineB(SDL_Surface *img, int beginx, int beginy,int end)
{
        int x; 
        for (x=beginx; x< end;x++)
        putpix(img,x,beginy , SDL_MapRGB(img->format, 255,0,0));
}

int segletter(SDL_Surface *img,struct line line, struct letter *letter_tab, int *sizetab)
{
	int x,y ;
	int i ;
	int onLetter=0;
	printf("segline s'est lancé\n");
	for(x=0 ; x <img->w; x++)
	{
		for (y=line.yb +1;
			 (getpix(img,x,y)==SDL_MapRGB(img->format,255,255,255)) && (y< line.ye);
			 y++);
		if(onLetter==0 && y!= line.ye)
		{	
			DrawColumn(img,x,line.yb,line.ye);
			onLetter=1;	
		}
		if((onLetter==1) &&(y ==line.ye))
		{
			DrawColumn(img,x,line.yb,line.ye);
			onLetter =0;
		}
	}

	return 0;

}
int segblocY (SDL_Surface *img, struct blocY *blocY_tab,int bloc_tabsize)
{
	int x,y;
	int onBlocy = 0;
	for(x=0 ; x<=img->w ; x++)
        {
                //Parcour l'image en width, si pixel = blanc,continue, sinon
                for (y=0;
                     	(  getpix(img,x,y)==SDL_MapRGB(img->format,255,255,255))
			&& (getpix(img,x+3,y)==SDL_MapRGB(img->format,255,255,255))
			&& (y< img->h);
                                y++);
		if(onBlocy==0 && y!= img ->h)
		{
		//	DrawColumnB(img,x,0,img->h);
			onBlocy=1;
			blocY_tab[bloc_tabsize].xb=x;
			
		}
		if((y==img->h) && onBlocy==1)
		{
		//	DrawColumnB(img,x,0,img->h);
			onBlocy =0;
			blocY_tab[bloc_tabsize].xe=x;
			bloc_tabsize++;
		}

		
	}
	return 0;

}

int segblocX (SDL_Surface *img, struct blocX *blocX_tab,int bloc_tabsize)
{
        int x,y;
        int onBlocx = 0;
        for(y=0 ; y<=img->h ; y++)
        {
                //Parcour l'image en width, si pixel = blanc,continue, sinon
                for (x=0;
                        (  getpix(img,x,y)==SDL_MapRGB(img->format,255,255,255))
                        && (getpix(img,x,y+10)==SDL_MapRGB(img->format,255,255,255))
                        && (x< img->w);
                                x++);
                if(x!= img->w && onBlocx==0 )
                {
                     //   DrawLineB(img,0,y,img->w);
			onBlocx=1;
                        blocX_tab[bloc_tabsize].yb=y;

                }
                if(x==img->w && onBlocx==1)
                {
                       // DrawLineB(img,0,y,img->w);
                        onBlocx =0;
                        blocX_tab[bloc_tabsize].ye=y;
                        bloc_tabsize++;
                }


        }
        return 0;

}
int segBloc(SDL_Surface *img, struct blocX *blocX_tab,int sizeblocX, struct blocY *blocY_tab,int sizeblocY, struct Bloc *Bloc_tab, int bloc_tabsize)
{
	int x,y;
	int i=0;
	int j;
	int onBlocx=0;
	int onBlocy=0;
	//On commence par les Lignes, on utilise les blocY
	for(i = 0;i<=2;i++)
	{
		//for(y=blocY_tab[i].xb; y<=blocY_tab[i].xe;y++)
		for(y=0; y<=img->h;y++)
		{
			for (x=blocY_tab[i].xb;
                        (  getpix(img,x,y)==SDL_MapRGB(img->format,255,255,255))
                        && (getpix(img,x,y+11)==SDL_MapRGB(img->format,255,255,255))
                        && (x< blocY_tab[i].xe);
                                x++);
			if(x!= blocY_tab[i].xe && onBlocx==0)
			{
				DrawLineB(img,blocY_tab[i].xb,y,blocY_tab[i].xe);
				onBlocx=1;
				Bloc_tab[bloc_tabsize].yb=y;
			}
			if(x==blocY_tab[i].xe && onBlocx==1)
			{
				DrawLineB(img,blocY_tab[i].xb,y,blocY_tab[i].xe);
				onBlocx=0;
				Bloc_tab[bloc_tabsize].ye=y;
				bloc_tabsize++;
			}
		}
		//On trace les colonnes
	for(j=0; j<= 2;j++)
	{
		for(x=0; x<=img->w;x++)
		        {
		                for (y=Bloc_tab[j].yb;
		                (  getpix(img,x,y)==SDL_MapRGB(img->format,255,255,255))
		                && (getpix(img,x,y)==SDL_MapRGB(img->format,255,255,255))
		                && (y< Bloc_tab[j].ye);
		                        y++);
		                if(y!= Bloc_tab[j].ye && onBlocy==0)
		                {
		                        DrawColumnB(img,x,Bloc_tab[j].yb,Bloc_tab[j].ye);
		                        onBlocy=1;
		                        Bloc_tab[j].xb=x;
		                }
		                if(y==Bloc_tab[j].ye && onBlocy==1)
		                {
					DrawColumnB(img,x,Bloc_tab[j].yb,Bloc_tab[j].ye);
		                        onBlocy=0;
					Bloc_tab[j].xe=x;
		//			bloc_tabsize++;
				}

			}


	}
		
		return 0;
	}
}
int main(int argc, char **argv)
{
	//Variable
	char filename_in[256];
	char filename_out[256];
	SDL_Surface *scr, *bmp;
//-----------------pour segline
	int size=0;
	int *sizetab=&(size);
	struct line line_tab[100];
//	struct line p;
//	line_tab[0]=p;
//----------------pour segletter
	struct letter letter_tab[100];
//---------------------pour segBlocy
	struct blocY blocY_tab[100];
	int sizeblocY=0;
//---------------------pour segBlocx
	struct blocX blocX_tab[100];
	int sizeblocX=0;

//---------------------pour segBloc
	struct Bloc Bloc_tab[100];
	int sizeBloc=0;

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

	//  grayscale(bmp);
	binarisation(bmp);
/*	segline(bmp,line_tab,sizetab);
	
	for(int i =0; i <size; i++)
	{	
	segletter(bmp,line_tab[i],letter_tab,sizetab);
	}*/
	segblocY(bmp,blocY_tab,sizeblocY);
	segblocX(bmp,blocX_tab,sizeblocX);
	segBloc(bmp,blocX_tab,sizeblocX,blocY_tab,sizeblocY,Bloc_tab,0);

//  DrawColumnB(bmp,30,Bloc_tab[0].yb,Bloc_tab[0].ye);
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

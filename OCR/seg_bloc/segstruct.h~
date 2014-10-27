#ifndef SEGSTRUCT_H_
# define SEGSTRUCT_H_
# include <stdlib.h>
# include <SDL.h>
struct line
{
int yb;
int ye;
};
struct letter
{
int yb;
int ye;
int xb;
int xe;
};
struct blocY
{
int yb;
int ye;
};
struct blocX
{
int xb;
int xe;
};
struct bloc
{
int x;
int y;
int h;
int w;
};

int segline(SDL_Surface *img,struct line *line_tab,int *sizetab );
int segletter(SDL_Surface *img,struct line line, struct letter *letter_tab, int *sizetab);
int segblocY (SDL_Surface *img, int y1, int y2/*struct blocY *blocY_tab,int bloc_tabsize*/);
int segblocX (SDL_Surface *img);
//int segletter(SDL_Surface *img,struct line line);

#endif

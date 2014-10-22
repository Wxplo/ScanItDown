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

int segline(SDL_Surface *img,struct line *line_tab,int *sizetab );
int segletter(SDL_Surface *img,struct line line, struct letter *letter_tab, int *sizetab);
//int segletter(SDL_Surface *img,struct line line);

#endif

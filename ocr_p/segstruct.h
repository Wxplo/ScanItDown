#ifndef SEGSTRUCT_H_
# define SEGSTRUCT_H_
# include <stdlib.h>
# include <SDL.h>
struct line
{
int yb;
int ye;
};
int segline(SDL_Surface *img,struct line *line_tab,int sizetab );
#endif

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
int xb;
int xe;
};
struct blocX
{
int yb;
int ye;
};
struct Bloc
{
int xb;
int xe;
int yb;
int ye;
};

int segline(SDL_Surface *img,struct line *line_tab,int *sizetab,struct Bloc Bloc );
int segletter(SDL_Surface *img,struct line line, struct letter *letter_tab, int *sizetab,struct Bloc Bloc);
int segblocY (SDL_Surface *img, struct blocY *blocY_tab,int bloc_tabsize);
int segblocX (SDL_Surface *img, struct blocX *blocX_tab,int bloc_tabsize);
int segBloc(SDL_Surface *img, struct blocX *blocX_tab,int sizeblocX, struct blocY *blocY_tab,int sizeblocY, struct Bloc *Bloc_tab, int bloc_tabsize);
int segBloc2(SDL_Surface *img, struct Bloc *Bloc_tab,int Bloc_size, int bloc_tabsize);
//int segletter(SDL_Surface *img,struct line line);

#endif

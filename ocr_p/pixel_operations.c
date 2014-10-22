# include "pixel_operations.h"

Uint32 getpix(SDL_Surface *s, int x, int y)
{
        Uint8 *p = (Uint8 *)s->pixels + y * s->pitch + x * s->format->BytesPerPixel;

        switch(s->format->BytesPerPixel)
        {
                case 1:
                        return *p;
                case 2:
                        return *(Uint16 *)p;
                case 3:
                        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                                return p[0] << 16 | p[1] << 8 | p[2];
                        else
                                return p[0] | p[1] << 8 | p[2] << 16;
                case 4:
                        return *(Uint32 *)p;
                default:
                        return 0;
        }


}

void putpix(SDL_Surface *s, int x, int y, Uint32 pix)
{
        Uint8 *p = (Uint8 *)s->pixels + y * s->pitch + x * s->format->BytesPerPixel;

        switch(s->format->BytesPerPixel)
        {
                case 1:
                        *p = pix;
                        break;
                case 2:
                        *(Uint16 *)p = pix;
                        break;
                case 3:
                        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                                p[0] = (pix >> 16) & 0xff;
                                p[1] = (pix >> 8) & 0xff;
                                p[2] =  pix & 0xff;
                        }
                        else {
                                p[0] =  pix & 0xff;
                                p[1] = (pix >> 8) & 0xff;
                                p[2] = (pix >> 16) & 0xff;
                        }
                        break;
                case 4:
                        *(Uint32 *)p = pix;
                        break;
                default:
                        break;
        }
}
void DrawLine(SDL_Surface *img, int y)
{
	int x;
	for (x=0; x< img->w;x++)
	putpix(img,x,y , SDL_MapRGB(img->format, 0, 0,250));
}


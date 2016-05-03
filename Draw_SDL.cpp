#include <math.h>
#include <SDL.h>
inline void setpixel(SDL_Surface * screen, const int x, const int y, const Uint8 r, const Uint8 g,
					 const Uint8 b)
{
	if (x < 0 || y < 0)
		return;
	if (x >= screen->w || y >= screen->h)
		return;
	Uint32 *pixmem32;
	Uint32 colour;
	colour = SDL_MapRGB(screen->format, r, g, b);
	// switch(screen->format->BytesPerPixel)
	pixmem32 = (Uint32 *) screen->pixels + y * screen->w + x;
	*pixmem32 = colour;

}

void Draw_X(SDL_Surface * screen,int dy)
{
	// X轴
	for (int x = 0; x < screen->w; x++)
	{
		setpixel(screen, x, dy, 255, 255, 255);
	}
}

void Draw_Y(SDL_Surface * screen,int dx)
{
	// Y轴
	for (int y = 0; y < screen->h; y++)
	{
		setpixel(screen, dx, y, 255, 255, 255);
	}
}
void _in_DrawLine(SDL_Surface *s,double x1,double y1,double x2,double y2)
{

	if(fabs(x1-x2)<1e-5)
	{
	if(y1>y2)
	{
		double t;
		t=y1;y1=y2;y2=t;
	}
		for(double y=y1;y<y2;y++)
		{
			setpixel(s,x1,y,255,255,255);
		}
	}
	else
	{
	double k=(y1-y2)/(x1-x2);
	if(x1>x2)
	{
		double t=x1;x1=x2;x2=t;
		t=y1;y1=y2;y2=t;
	}
	for(double x=x1;x<x2;x++)
	{
		double y=k*(x-x1)+y1;
	setpixel(s,x,y,0xff,0xff,0xff);
	}
	
	}

}
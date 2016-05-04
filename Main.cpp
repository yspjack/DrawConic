#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

#define WIDTH 720
#define HEIGHT 1280
#define BPP 4
#define DEPTH 32

inline int min(int a, int b)
{
	return a < b ? a : b;
}

inline int max(int a, int b)
{
	return a > b ? a : b;
}

inline double sec(double t)
{
	return 1.0 / cos(t);
}

inline double csc(double t)
{
	return 1.0 / sin(t);
}

#include "Draw_SDL.cpp"
#include "Main.h"
extern double EPS;
extern double FROM;
extern double TO;
extern int dx, dy;
extern int zoomx, zoomy;
int need_update;
void DrawConic(SDL_Surface * screen, double (*fx) (double),
			   double (*fy) (double), Uint8 r, Uint8 g, Uint8 b)
{
	register int MUSTLOCK = SDL_MUSTLOCK(screen);
	if (MUSTLOCK)
	{
		if (SDL_LockSurface(screen) < 0)
			return;
	}
	// X轴
	Draw_X(screen, dy);
	// Y轴
	Draw_Y(screen, dx);
	// 参数方程
	for (double t = FROM; t < TO; t += EPS)
	{
		setpixel(screen, dx + zoomx * fx(t), dy + zoomy * -fy(t), r, g, b);
		// SDL_Flip(screen);
		// SDL_Delay(1);
	}

	if (MUSTLOCK)
		SDL_UnlockSurface(screen);
}


void DrawPolar(SDL_Surface * screen, double (*fx) (double), Uint8 r, Uint8 g, Uint8 b)
{
	register int MUSTLOCK = SDL_MUSTLOCK(screen);
	if (MUSTLOCK)
	{
		if (SDL_LockSurface(screen) < 0)
			return;
	}
	// 极轴
	for (int x = dx; x < screen->w; x++)
	{
		setpixel(screen, x, dy, 255, 255, 255);
	}

	// 极坐标方程

	for (double t = FROM; t < TO; t += EPS)
	{
		setpixel(screen, dx + zoomx * fx(t) * cos(t), dy + zoomy * -fx(t) * sin(t), r, g,
				 b);
	}

	if (MUSTLOCK)
		SDL_UnlockSurface(screen);
}

void DrawLine(SDL_Surface * s, double x1, double y1, double x2, double y2)
{
	register int MUSTLOCK = SDL_MUSTLOCK(s);
	if (MUSTLOCK)
	{
		if (SDL_LockSurface(s) < 0)
			return;
	}
	_in_DrawLine(s, x1 + dx, -y1 + dy, x2 + dx, -y2 + dy);
	if (MUSTLOCK)
		SDL_UnlockSurface(s);
}


void reset_draw(SDL_Surface * screen)
{
	dx = screen->w >> 2;
	dy = screen->h >> 2;
	dx = 100;
	dy = 1000;
	zoomx = min(screen->w, screen->h) >> 3;
	zoomy = min(screen->w, screen->h) >> 3;
}

int main(int argc, char *argv[])
{
	// freopen("sdl.out", "w", stdout);
	atexit(SDL_Quit);
	SDL_Surface *screen;
	SDL_Event event;
	register int keypress = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF)))
	{
		SDL_Quit();
		return 1;
	}
	printf("w=%d\nh=%d\npitch=%d\n", screen->w, screen->h, screen->pitch);
	fflush(stdout);
	need_update = 1;
	reset_draw(screen);
	while (!keypress)
	{
		if (need_update)
		{
			need_update = 0;
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
			Draw(screen);
			SDL_Flip(screen);

		}
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				keypress = 1;
				break;
			case SDL_KEYDOWN:
				need_update = 1;
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					dy -= zoomy;
					break;
				case SDLK_RIGHT:
					dx += zoomx;
					break;
				case SDLK_DOWN:
					dy += zoomy;
					break;
				case SDLK_LEFT:
					dx -= zoomx;
					break;
				case SDLK_s:
					SDL_SaveBMP(screen, "conic.bmp");
					break;
				case SDLK_KP_PLUS:
//				zoomx=zoomx+10;
//				zoomy=zoomy+10;
				
					break;
				case SDLK_KP_MINUS:
					break;
				 default:
					keypress = 1;
					break;
				}
				break;
			}
		}
	}
	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}
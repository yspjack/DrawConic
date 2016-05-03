#include <stdio.h>
#include <math.h>
#include <SDL.h>

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

double EPS = 0.01;
double FROM;
double TO;
int dx, dy;
int zoomx, zoomy;
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


inline double fx(double t)
{
	return t;
}

inline double fy(double t)
{
	return 800.0 / (1.0 + (800.0 / 3.0 - 1.0) * exp(-0.8 * t));
}

inline double dfy(double x)
{
	return (1530240.0 * exp(-0.8 * x)) / (635209 * exp(-2 * 0.8 * x) +
										  4782.0 * exp(-0.8 * x) + 9.0);
}

void Lorenz(SDL_Surface * s)
{
	register int MUSTLOCK = SDL_MUSTLOCK(s);
	if (MUSTLOCK)
	{
		if (SDL_LockSurface(s) < 0)
			return;
	}
	double x = 3.051522, y = 1.582542, z = 15.62388, x1, y1, z1;
	double dt = 1e-4;
	int a = 5, b = 15, c = 1;
	// X轴
	for (int x = 0; x < s->w; x++)
	{
		setpixel(s, x, dy, 255, 255, 255);
	}
	// Y轴
	for (int y = 0; y < s->h; y++)
	{
		setpixel(s, dx, y, 255, 255, 255);
	}
	int i = 0;
	int n = 100 / dt;
	while (i < n)
	{
		x1 = x + a * (-x + y) * dt;
		y1 = y + (b * x - y - z * x) * dt;
		z1 = z + (-c * z + x * y) * dt;
		x = x1;
		y = y1;
		z = z1;
		setpixel(s, zoomx * (y - x * 0.292893) + dx,
				 -zoomy * (z + x * 0.292893) + dy, 255, 255, 0);
		i++;
	}
	if (MUSTLOCK)
		SDL_UnlockSurface(s);
}

// square wave
double sq(double x)
{
	/* double r=0; for(int i=1;i<100;i+=2) { r+=sin((i)* x)/(i); } return r; */
	return sin(x * 1) / 1 + sin(x * 3) / 3 + sin(x * 5) / 5 + sin(x * 7) / 7 +
		sin(x * 9) / 9 + sin(x * 11) / 11 + sin(x * 13) / 13 + sin(x * 15) / 15 +
		sin(x * 17) / 17 + sin(x * 19) / 19 + sin(x * 21) / 21 + sin(x * 23) / 23 +
		sin(x * 25) / 25 + sin(x * 27) / 27 + sin(x * 29) / 29 + sin(x * 31) / 31 +
		sin(x * 33) / 33 + sin(x * 35) / 35 + sin(x * 37) / 37 + sin(x * 39) / 39 +
		sin(x * 41) / 41 + sin(x * 43) / 43 + sin(x * 45) / 45 + sin(x * 47) / 47 +
		sin(x * 49) / 49 + sin(x * 51) / 51 + sin(x * 53) / 53 + sin(x * 55) / 55 +
		sin(x * 57) / 57 + sin(x * 59) / 59 + sin(x * 61) / 61 + sin(x * 63) / 63 +
		sin(x * 65) / 65 + sin(x * 67) / 67 + sin(x * 69) / 69 + sin(x * 71) / 71 +
		sin(x * 73) / 73 + sin(x * 75) / 75 + sin(x * 77) / 77 + sin(x * 79) / 79 +
		sin(x * 81) / 81 + sin(x * 83) / 83 + sin(x * 85) / 85 + sin(x * 87) / 87 +
		sin(x * 89) / 89 + sin(x * 91) / 91 + sin(x * 93) / 93 + sin(x * 95) / 95 +
		sin(x * 97) / 97 + sin(x * 99) / 99;
}

// triangle wave
double tri(double x)
{
	return 5 + sin(x * 1) / 1 + sin(x * 2) / 2 + sin(x * 3) / 3 + sin(x * 4) / 4 +
		sin(x * 5) / 5 + sin(x * 6) / 6 + sin(x * 7) / 7 + sin(x * 8) / 8 +
		sin(x * 9) / 9 + sin(x * 10) / 10 + sin(x * 11) / 11 + sin(x * 12) / 12 +
		sin(x * 13) / 13 + sin(x * 14) / 14 + sin(x * 15) / 15 + sin(x * 16) / 16 +
		sin(x * 17) / 17 + sin(x * 18) / 18 + sin(x * 19) / 19 + sin(x * 20) / 20 +
		sin(x * 21) / 21 + sin(x * 22) / 22 + sin(x * 23) / 23 + sin(x * 24) / 24 +
		sin(x * 25) / 25 + sin(x * 26) / 26 + sin(x * 27) / 27 + sin(x * 28) / 28 +
		sin(x * 29) / 29 + sin(x * 30) / 30 + sin(x * 31) / 31 + sin(x * 32) / 32 +
		sin(x * 33) / 33 + sin(x * 34) / 34 + sin(x * 35) / 35 + sin(x * 36) / 36 +
		sin(x * 37) / 37 + sin(x * 38) / 38 + sin(x * 39) / 39 + sin(x * 40) / 40 +
		sin(x * 41) / 41 + sin(x * 42) / 42 + sin(x * 43) / 43 + sin(x * 44) / 44 +
		sin(x * 45) / 45 + sin(x * 46) / 46 + sin(x * 47) / 47 + sin(x * 48) / 48 +
		sin(x * 49) / 49 + sin(x * 50) / 50 + sin(x * 51) / 51 + sin(x * 52) / 52 +
		sin(x * 53) / 53 + sin(x * 54) / 54 + sin(x * 55) / 55 + sin(x * 56) / 56 +
		sin(x * 57) / 57 + sin(x * 58) / 58 + sin(x * 59) / 59 + sin(x * 60) / 60 +
		sin(x * 61) / 61 + sin(x * 62) / 62 + sin(x * 63) / 63 + sin(x * 64) / 64 +
		sin(x * 65) / 65 + sin(x * 66) / 66 + sin(x * 67) / 67 + sin(x * 68) / 68 +
		sin(x * 69) / 69 + sin(x * 70) / 70 + sin(x * 71) / 71 + sin(x * 72) / 72 +
		sin(x * 73) / 73 + sin(x * 74) / 74 + sin(x * 75) / 75 + sin(x * 76) / 76 +
		sin(x * 77) / 77 + sin(x * 78) / 78 + sin(x * 79) / 79 + sin(x * 80) / 80 +
		sin(x * 81) / 81 + sin(x * 82) / 82 + sin(x * 83) / 83 + sin(x * 84) / 84 +
		sin(x * 85) / 85 + sin(x * 86) / 86 + sin(x * 87) / 87 + sin(x * 88) / 88 +
		sin(x * 89) / 89 + sin(x * 90) / 90 + sin(x * 91) / 91 + sin(x * 92) / 92 +
		sin(x * 93) / 93 + sin(x * 94) / 94 + sin(x * 95) / 95 + sin(x * 96) / 96 +
		sin(x * 97) / 97 + sin(x * 98) / 98 + sin(x * 99) / 99;
}

double tayor(double x)
{
	double s = 1, xx = 1;
	int i, fact = 1;
	for (i = 1; i < 10; i++)
	{
		fact *= i;
		xx *= x;
		s += xx / fact;
	}
	return s;
}

// error function
double F(double x)
{
	return exp(-x * x);
}

double simpson(double a, double b)
{
	double c = a + (b - a) / 2;
	return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}

double asr(double a, double b, double eps, double A)
{
	double c = a + (b - a) / 2;
	double L = simpson(a, c), R = simpson(c, b);
	if (fabs(L + R - A) <= 15 * eps)
		return L + R + (L + R - A) / 15.0;
	return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}

double asr(double a, double b, double eps)
{
	return asr(a, b, eps, simpson(a, b));
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
			FROM = -5;
			TO = 5;
			EPS = 1e-3;
			// zoomy = 1;
			// DrawPolar(screen, fx,0,255,255);
			DrawConic(screen, fx, F, 0, 255, 255);
			DrawConic(screen, fx,[](double x)
					  {
					  return asr(0, x, 1e-4);
					  }
					  , 255, 255, 0);
			// DrawLine(screen,100,0,100,100);
			// Lorenz(screen);
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
#ifndef __DrawConic_Main
#define __DrawConic_Main
	double EPS = 0.01;
	double FROM;
	double TO;
	int dx, dy;
	int zoomx, zoomy;
extern "C"
{
	void Draw(SDL_Surface * s);
	void DrawConic(SDL_Surface * screen, double (*fx) (double),
				   double (*fy) (double), Uint8 r, Uint8 g, Uint8 b);

	void DrawPolar(SDL_Surface * screen, double (*fx) (double), Uint8 r, Uint8 g,
				   Uint8 b);
	void reset_draw(SDL_Surface * screen);
}
#endif	/* __DrawConic_Main */
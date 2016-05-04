#include <SDL/SDL.h>
#include "Main.cpp"

void Draw(SDL_Surface *s)
{
	FROM=0;
	TO=20;
	EPS=0.005;
	DrawConic(s,[](double x){return x;},sin,255,255,255);
}
#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

class Text {
public:
	Text();
	~Text();
	void Init(string textContent, int width, int height, int xpos, int ypos, SDL_Color textColor);
	void Render();
private:

	SDL_Texture* Message;
	SDL_Surface* surfaceMessage;
	SDL_Rect destRect;

	TTF_Font* font;
};
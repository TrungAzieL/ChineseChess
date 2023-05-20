#include "Game.hpp"
#include "TextManager.hpp"

Text::Text() {
}

Text::~Text() {
}

void Text::Init(string textContent, int width, int height, int xpos, int ypos, const SDL_Color textColor) {
	destRect.w = width;
	destRect.h = height;
	destRect.x = xpos;
	destRect.y = ypos;

	font = TTF_OpenFont("assets/consola.ttf", 24);

	const char* text = textContent.c_str();

	surfaceMessage = TTF_RenderText_Solid(font, text, textColor);
	Message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
}

void Text::Render() {
	SDL_RenderCopy(Game::renderer, Message, NULL, &destRect);
}
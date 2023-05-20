#include "Game.hpp"
#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tmpSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, int rotateDeg)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, rotateDeg, NULL, SDL_FLIP_NONE);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, int rotateDeg, int opacity)
{
	SDL_SetTextureAlphaMod(tex, opacity);
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, rotateDeg, NULL, SDL_FLIP_NONE);
}

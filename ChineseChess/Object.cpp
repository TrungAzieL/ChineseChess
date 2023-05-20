#include "Game.hpp"
#include "Object.hpp"
#include "TextureManager.hpp"

Object::Object() {
}

Object::~Object() {

}

void Object::Init(const char* texturesheet, int width, int height, int xpos, int ypos) {
	objTexture = TextureManager::LoadTexture(texturesheet);
	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.h = height;
	srcRect.w = width;

	destRect.h = height;
	destRect.w = width;

	destRect.x = xpos;
	destRect.y = ypos;
}

void Object::Init(const char* texturesheet, int srcXpos, int srcYpos, int width, int height, int chessX, int chessY) {
	objTexture = TextureManager::LoadTexture(texturesheet);
	srcRect.x = srcYpos;
	srcRect.y = srcXpos;

	srcRect.w = width;
	srcRect.h = height;

	destRect.w = width;
	destRect.h = height;
}

void Object::Update(int width, int height, int xpos, int ypos) {
	srcRect.h = destRect.h = height;
	srcRect.w = destRect.w = width;

	destRect.x = xpos;
	destRect.y = ypos;
}

void Object::ChangeSrc(int srcX, int srcY) {
	srcRect.x = srcX;
	srcRect.y = srcY;
}

bool Object::checkMouseOn(int x, int y) {
	SDL_Rect mouseDest;
	mouseDest.x = x;
	mouseDest.y = y;
	mouseDest.w = mouseDest.h = 1;

	return (SDL_HasIntersection(&mouseDest, &destRect));
}

SDL_Rect Object::getDest() {
	return (destRect);
}


void Object::Render() {
	TextureManager::Draw(objTexture, srcRect, destRect, 0);
}

void Object::Render(int opacity) {
	TextureManager::Draw(objTexture, srcRect, destRect, 0, opacity);
}
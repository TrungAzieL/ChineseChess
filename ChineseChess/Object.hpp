#pragma once
#include <SDL.h>

class Object {
public:
	Object();
	~Object();

	void Init(const char* texturesheet, int width, int height, int xpos, int ypos);
	virtual void Init(const char* texturesheet, int srcXpos, int srcYpos, int width, int height, int xpos, int ypos);

	void Update(int width, int height, int xpos, int ypos);
	void ChangeSrc(int srcX, int srcY);
	bool checkMouseOn(int x, int y);

	SDL_Rect getDest();
	void Render();
	void Render(int opacity);

protected:
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};
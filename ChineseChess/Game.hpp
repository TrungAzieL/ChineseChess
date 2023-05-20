#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>
#include <vector>

enum piecesName { Vua = 0, Si = 1, Ma = 2, Tuong = 3, Xe = 4, Phao = 5, Tot = 6 };

using namespace std;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() {
		return isRunning;
	}


	static SDL_Renderer* renderer;
	static SDL_Event event;

	static bool isRunning;
	static bool isFinish;

private:
	SDL_Window* window;
};
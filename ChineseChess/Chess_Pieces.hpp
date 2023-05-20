#pragma once
#include "Object.hpp"
#include <vector>

class Chess_Pieces : public Object {
public:
	void Init(const char* texturesheet, int srcXpos, int srcYpos, int width, int height, int chessX, int chessY);

	std::vector<std::pair<int, int>> getMoves(int index, bool isBlackPiece);
	//void getMoves(int index, bool isBlackPiece);
	void setPos(int xPos, int yPos);

	std::pair<int, int> getChessPos();
	void Update();
	void Update(int width, int height, int x, int y);

	void Delete();

	int getStateOf(int x, int y);
	int getState();

	void changeState(int state);
	void changeStateOf(int state, int x, int y);

	const char* getSrcFile() {
		return srcFile;
	}

	SDL_Rect getSrcRect() {
		return srcRect;
	}

	static std::pair<int, int> kingPos[2];
	static int hasPiece[10][9];
	static Chess_Pieces* getPiece[10][10];
private:
	const char* srcFile;
	int ChessX, ChessY;
};
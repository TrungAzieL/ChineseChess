#include "Chess_Pieces.hpp"
#include <iostream>
#include "TextureManager.hpp"


/*
0: Don't have piece
1: Have black piece
2: Have red peice
*/

std::pair<int, int> Chess_Pieces::kingPos[2];
Chess_Pieces *Chess_Pieces::getPiece[10][10];

int Chess_Pieces::hasPiece[10][9] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void Chess_Pieces::Init(const char* texturesheet, int srcXpos, int srcYpos, int width, int height, int chessX, int chessY) {
	objTexture = TextureManager::LoadTexture(texturesheet);

	srcFile = texturesheet;

	srcRect.x = srcYpos;
	srcRect.y = srcXpos;

	srcRect.w = width;
	srcRect.h = height;

	destRect.w = width;
	destRect.h = height;

	ChessX = chessX;
	ChessY = chessY;

	destRect.x = 38 + (int)(62.5 * ChessX);
	destRect.y = 40 + 65 * ChessY;
}

void Chess_Pieces::setPos(int xPos, int yPos) {
	ChessX = xPos;
	ChessY = yPos;
}

std::pair<int, int> Chess_Pieces::getChessPos() {
	return { ChessX, ChessY };
}

std::vector<std::pair<int, int>> Chess_Pieces::getMoves(int index, bool isBlackPiece) {
	//Vua = 0, Si = 1-2, Ma = 3-4, Tuong = 5-6, Xe = 7-8, Phao = 9-10, Tot = 11-12-13-14-15
	std::vector<std::pair<int, int>> moves;
	pair<int, int> targetKing;
	vector<pair<int, int>> suitable_moves;

	if (isBlackPiece)
		switch (index)
		{
		case 0: // Vua
			if (ChessY - 1 >= 0 && hasPiece[ChessY - 1][ChessX] != 1)
				moves.push_back({ ChessX, ChessY - 1 });

			if (ChessY + 1 <= 2 && hasPiece[ChessY + 1][ChessX] != 1)
				moves.push_back({ ChessX, ChessY + 1});

			if (ChessX - 1 >= 3 && hasPiece[ChessY][ChessX - 1] != 1)
				moves.push_back({ ChessX - 1, ChessY });

			if (ChessX + 1 <= 5 && hasPiece[ChessY][ChessX + 1] != 1)
				moves.push_back({ ChessX + 1, ChessY });

			//Vua doi dien
			targetKing = kingPos[1];
			if (ChessX != targetKing.first) break;
			for (int i = ChessY + 1; i <= 9; ++i) {
				if (hasPiece[i][ChessX])
					if (i == targetKing.second) {
						moves.push_back({ ChessX, i });
					}
					else break;
			}

			break;

		case 1: case 2:
			for (int i = max(ChessY - 1, 0); i <= min(ChessY + 1, 2); i++) {
				for (int j = max(ChessX - 1, 3); j <= min(ChessX + 1, 5); j++) {
					if (abs(i - ChessY) + abs(j - ChessX) != 2) continue;
					if (!hasPiece[i][j] || hasPiece[i][j] == 2) moves.push_back({ j, i });
				}
			}

			break;

		case 3: case 4:

			/*
				 .   .
			  .    1     .
				4  x  2
			  .    3    .
				 .   .
			*/
			if (ChessY - 1 >= 0 && !hasPiece[ChessY - 1][ChessX]) {
				if (ChessY - 2 >= 0 && ChessX - 1 >= 0)
					if (!hasPiece[ChessY - 2][ChessX - 1] || (hasPiece[ChessY - 2][ChessX - 1] != isBlackPiece))
						moves.push_back({ ChessX - 1, ChessY - 2 });

				if (ChessY - 2 >= 0 && ChessX + 1 <= 8)
					if (!hasPiece[ChessY - 2][ChessX + 1] || (hasPiece[ChessY - 2][ChessX + 1] != isBlackPiece))
						moves.push_back({ ChessX + 1, ChessY - 2 });
			}

			if (ChessX + 1 <= 8 && !hasPiece[ChessY][ChessX + 1]) {
				if (ChessY + 1 <= 9 && ChessX + 2 <= 8)
					if (!hasPiece[ChessY + 1][ChessX + 2] || (hasPiece[ChessY + 1][ChessX + 2] != isBlackPiece))
						moves.push_back({ ChessX + 2, ChessY + 1 });

				if (ChessY - 1 >= 0 && ChessX + 2 <= 8)
					if (!hasPiece[ChessY - 1][ChessX + 2] || (hasPiece[ChessY - 1][ChessX + 2] != isBlackPiece))
						moves.push_back({ ChessX + 2, ChessY - 1 });
			}

			if (ChessY + 1 <= 9 && !hasPiece[ChessY + 1][ChessX]) {
				if (ChessY + 2 <= 9 && ChessX + 1 <= 8)
					if (!hasPiece[ChessY + 2][ChessX + 1] || (hasPiece[ChessY + 2][ChessX + 1] != isBlackPiece))
						moves.push_back({ ChessX + 1, ChessY + 2 });

				if (ChessY + 2 <= 9 && ChessX - 1 >= 0)
					if (!hasPiece[ChessY + 2][ChessX - 1] || (hasPiece[ChessY + 2][ChessX - 1] != isBlackPiece))
						moves.push_back({ ChessX - 1, ChessY + 2 });
			}

			if (ChessX - 1 >= 0 && !hasPiece[ChessY][ChessX - 1]) {
				if (ChessY + 1 <= 9 && ChessX - 2 >= 0)
					if (!hasPiece[ChessY + 1][ChessX - 2] || (hasPiece[ChessY + 1][ChessX - 2] != isBlackPiece))
						moves.push_back({ ChessX - 2, ChessY + 1 });

				if (ChessY - 1 >= 0 && ChessX - 2 >= 0)
					if (!hasPiece[ChessY - 1][ChessX - 2] || (hasPiece[ChessY - 1][ChessX - 2] != isBlackPiece))
						moves.push_back({ ChessX - 2, ChessY - 1 });
			}
			break;

		case 5: case 6:
			if (ChessY - 2 >= 0 && ChessX - 2 >= 0) {
				if (!hasPiece[ChessY - 1][ChessX - 1] && (!hasPiece[ChessY - 2][ChessX - 2] || hasPiece[ChessY - 2][ChessX - 2] != isBlackPiece))
					moves.push_back({ ChessX - 2 , ChessY - 2 });
			}

			if (ChessY - 2 >= 0 && ChessX + 2 <= 8) {
				if (!hasPiece[ChessY - 1][ChessX + 1] && (!hasPiece[ChessY - 2][ChessX + 2] || hasPiece[ChessY - 2][ChessX + 2] != isBlackPiece))
					moves.push_back({ ChessX + 2 , ChessY - 2 });
			}

			if (ChessY + 2 <= 4 && ChessX - 2 >= 0) {
				if (!hasPiece[ChessY + 1][ChessX - 1] && (!hasPiece[ChessY + 2][ChessX - 2] || hasPiece[ChessY + 2][ChessX - 2] != isBlackPiece))
					moves.push_back({ ChessX - 2 , ChessY + 2 });
			}

			if (ChessY + 2 <= 4 && ChessX + 2 <= 8) {
				if (!hasPiece[ChessY + 1][ChessX + 1] && (!hasPiece[ChessY + 2][ChessX + 2] || hasPiece[ChessY + 2][ChessX + 2] != isBlackPiece))
					moves.push_back({ ChessX + 2 , ChessY + 2 });
			}

			break;

		case 7: case 8:
			for (int i = ChessY + 1; i <= 9; ++i) {
				if (hasPiece[i][ChessX] == 1)
					break;
				else if (hasPiece[i][ChessX] == 2) {
					moves.push_back({ ChessX, i });
					break;
				}
				moves.push_back({ ChessX, i });
			}

			for (int i = ChessY - 1; i >= 0; --i) {
				if (hasPiece[i][ChessX] == 1)
					break;
				else if (hasPiece[i][ChessX] == 2) {
					moves.push_back({ ChessX, i });
					break;
				}
				moves.push_back({ ChessX, i });
			}

			for (int j = ChessX + 1; j <= 8; ++j) {
				if (hasPiece[ChessY][j] == 0)
					moves.push_back({ j, ChessY });

				else if (hasPiece[ChessY][j] == 2) {
					moves.push_back({ j, ChessY });
					break;
				}

				else break;
			}

			for (int j = ChessX - 1; j >= 0; --j) {
				if (hasPiece[ChessY][j] == 0)
					moves.push_back({ j, ChessY });

				else if (hasPiece[ChessY][j] == 2) {
					moves.push_back({ j, ChessY });
					break;
				}

				else break;
			}

			break;

		case 9: case 10:
			for (int i = ChessY + 1; i <= 9; ++i) {
				if (!hasPiece[i][ChessX]) moves.push_back({ ChessX, i });
				else if (hasPiece[i][ChessX]) {
					for (int j = i + 1; j <= 9; ++j) {
						if (hasPiece[j][ChessX] == 2) {
							moves.push_back({ ChessX, j });
							break;
						}
						else if (hasPiece[j][ChessX] == 1)
							break;
					}
					break;
				}
			}

			for (int i = ChessY - 1; i >= 0; --i) {
				if (!hasPiece[i][ChessX]) moves.push_back({ ChessX, i });
				else if (hasPiece[i][ChessX]) {
					for (int j = i - 1; j >= 0; --j) {
						if (hasPiece[j][ChessX] == 2) {
							moves.push_back({ ChessX, j });
							break;
						}
						else if (hasPiece[j][ChessX] == 1)
							break;
					}
					break;
				}
			}

			for (int i = ChessX + 1; i <= 8; ++i) {
				if (!hasPiece[ChessY][i]) moves.push_back({ i, ChessY });
				else if (hasPiece[ChessY][i]) {
					for (int j = i + 1; j <= 8; ++j) {
						if (hasPiece[ChessY][j] == 2) {
							moves.push_back({ j, ChessY });
							break;
						}
						else if (hasPiece[ChessY][j] == 1)
							break;
					}
					break;
				}
			}

			for (int i = ChessX - 1; i >= 0; --i) {
				if (!hasPiece[ChessY][i]) moves.push_back({ i, ChessY });
				else if (hasPiece[ChessY][i]) {
					for (int j = i - 1; j >= 0; --j) {
						if (hasPiece[ChessY][j] == 2) {
							moves.push_back({ j, ChessY });
							break;
						}
						else if (hasPiece[ChessY][j] == 1) 
							break;
					}
					break;
				}
			}

			break;
		default: //Tot
			if (ChessY + 1 <= 9 && hasPiece[ChessY + 1][ChessX] != 1)
				moves.push_back({ ChessX, ChessY + 1 });

			if (ChessY > 4) {
				if (ChessX - 1 >= 0 && hasPiece[ChessY][ChessX - 1] != 1)
					moves.push_back({ ChessX - 1, ChessY });

				if (ChessX + 1 <= 8 && hasPiece[ChessY][ChessX + 1] != 1)
					moves.push_back({ ChessX + 1, ChessY });
			}

			break;
		}
	else
		switch (index)
		{
		case 0: // Vua
			if (ChessY - 1 >= 7 && hasPiece[ChessY - 1][ChessX] != 2)
				moves.push_back({ ChessX, ChessY - 1 });

			if (ChessY + 1 <= 9 && hasPiece[ChessY + 1][ChessX] != 2)
				moves.push_back({ ChessX, ChessY + 1 });

			if (ChessX - 1 >= 3 && hasPiece[ChessY][ChessX - 1] != 2)
				moves.push_back({ ChessX - 1, ChessY });

			if (ChessX + 1 <= 5 && hasPiece[ChessY][ChessX + 1] != 2)
				moves.push_back({ ChessX + 1, ChessY });

			//Vua doi dien
			targetKing = kingPos[0];
			if (ChessX != targetKing.first) break;
			for (int i = ChessY - 1; i >= 0; --i) {
				if (hasPiece[i][ChessX])
					if (i == targetKing.second) {
						moves.push_back({ ChessX, i });
					}
					else break;
			}
			break;

		case 1: case 2:
			for (int i = max(ChessY - 1, 7); i <= min(ChessY + 1, 9); i++) {
				for (int j = max(ChessX - 1, 3); j <= min(ChessX + 1, 5); j++) {
					if (abs(i - ChessY) + abs(j - ChessX) != 2) continue;
					if (!hasPiece[i][j] || hasPiece[i][j] == 1) moves.push_back({ j, i });
				}
			}
			break;

		case 3: case 4:
			if (ChessY - 1 >= 0 && !hasPiece[ChessY - 1][ChessX]) {
				if (ChessY - 2 >= 0 && ChessX - 1 >= 0)
					if (!hasPiece[ChessY - 2][ChessX - 1] || (hasPiece[ChessY - 2][ChessX - 1] == 1))
						moves.push_back({ ChessX - 1, ChessY - 2 });

				if (ChessY - 2 >= 0 && ChessX + 1 <= 8)
					if (!hasPiece[ChessY - 2][ChessX + 1] || (hasPiece[ChessY - 2][ChessX + 1] == 1))
						moves.push_back({ ChessX + 1, ChessY - 2 });
			}

			if (ChessX + 1 <= 8 && !hasPiece[ChessY][ChessX + 1]) {
				if (ChessY + 1 <= 9 && ChessX + 2 <= 8)
					if (!hasPiece[ChessY + 1][ChessX + 2] || (hasPiece[ChessY + 1][ChessX + 2] == 1))
						moves.push_back({ ChessX + 2, ChessY + 1 });

				if (ChessY - 1 >= 0 && ChessX + 2 <= 8)
					if (!hasPiece[ChessY - 1][ChessX + 2] || (hasPiece[ChessY - 1][ChessX + 2] == 1))
						moves.push_back({ ChessX + 2, ChessY - 1 });
			}

			if (ChessY + 1 <= 9 && !hasPiece[ChessY + 1][ChessX]) {
				if (ChessY + 2 <= 9 && ChessX + 1 <= 8)
					if (!hasPiece[ChessY + 2][ChessX + 1] || (hasPiece[ChessY + 2][ChessX + 1] == 1))
						moves.push_back({ ChessX + 1, ChessY + 2 });

				if (ChessY + 2 <= 9 && ChessX - 1 >= 0)
					if (!hasPiece[ChessY + 2][ChessX - 1] || (hasPiece[ChessY + 2][ChessX - 1] == 1))
						moves.push_back({ ChessX - 1, ChessY + 2 });
			}

			if (ChessX - 1 >= 0 && !hasPiece[ChessY][ChessX - 1]) {
				if (ChessY + 1 <= 9 && ChessX - 2 >= 0)
					if (!hasPiece[ChessY + 1][ChessX - 2] || (hasPiece[ChessY + 1][ChessX - 2] == 1))
						moves.push_back({ ChessX - 2, ChessY + 1 });

				if (ChessY - 1 >= 0 && ChessX - 2 >= 0)
					if (!hasPiece[ChessY - 1][ChessX - 2] || (hasPiece[ChessY - 1][ChessX - 2] == 1))
						moves.push_back({ ChessX - 2, ChessY - 1 });
			}
			break;

		case 5: case 6:
			if (ChessY - 2 >= 4 && ChessX - 2 >= 0) {
				if (!hasPiece[ChessY - 1][ChessX - 1] && (!hasPiece[ChessY - 2][ChessX - 2] || hasPiece[ChessY - 2][ChessX - 2] != 2))
					moves.push_back({ ChessX - 2 , ChessY - 2 });
			}

			if (ChessY - 2 >= 4 && ChessX + 2 <= 8) {
				if (!hasPiece[ChessY - 1][ChessX + 1] && (!hasPiece[ChessY - 2][ChessX + 2] || hasPiece[ChessY - 2][ChessX + 2] != 2))
					moves.push_back({ ChessX + 2 , ChessY - 2 });
			}

			if (ChessY + 2 <= 9 && ChessX - 2 >= 0) {
				if (!hasPiece[ChessY + 1][ChessX - 1] && (!hasPiece[ChessY + 2][ChessX - 2] || hasPiece[ChessY + 2][ChessX - 2] != 2))
					moves.push_back({ ChessX - 2 , ChessY + 2 });
			}

			if (ChessY + 2 <= 9 && ChessX + 2 <= 8) {
				if (!hasPiece[ChessY + 1][ChessX + 1] && (!hasPiece[ChessY + 2][ChessX + 2] || hasPiece[ChessY + 2][ChessX + 2] != 2))
					moves.push_back({ ChessX + 2 , ChessY + 2 });
			}
			break;

		case 7: case 8:
			for (int i = ChessY + 1; i <= 9; ++i) {
				if (!hasPiece[i][ChessX])
					moves.push_back({ ChessX, i });

				else if (hasPiece[i][ChessX] == 1) {
					moves.push_back({ ChessX, i });
					break;
				}

				else break;
			}

			for (int i = ChessY - 1; i >= 0; --i) {
				if (!hasPiece[i][ChessX])
					moves.push_back({ ChessX, i });

				else if (hasPiece[i][ChessX] == 1) {
					moves.push_back({ ChessX, i });
					break;
				}

				else break;
			}

			for (int j = ChessX + 1; j <= 8; ++j) {
				if (!hasPiece[ChessY][j])
					moves.push_back({ j, ChessY });

				else if (hasPiece[ChessY][j] == 1) {
					moves.push_back({ j, ChessY });
					break;
				}

				else break;
			}

			for (int j = ChessX - 1; j >= 0; --j) {
				if (!hasPiece[ChessY][j])
					moves.push_back({ j, ChessY });

				else if (hasPiece[ChessY][j] == 1) {
					moves.push_back({ j, ChessY });
					break;
				}

				else break;
			}

			break;

		case 9: case 10:
			for (int i = ChessY + 1; i <= 9; ++i) {
				if (!hasPiece[i][ChessX]) moves.push_back({ ChessX, i });
				else if (hasPiece[i][ChessX]) {
					for (int j = i + 1; j <= 9; ++j) {
						if (hasPiece[j][ChessX] == 1) {
							moves.push_back({ ChessX, j });
							break;
						}
						else if (hasPiece[j][ChessX] == 2)
							break;
					}
					break;
				}
			}

			for (int i = ChessY - 1; i >= 0; --i) {
				if (!hasPiece[i][ChessX]) moves.push_back({ ChessX, i });
				else if (hasPiece[i][ChessX]) {
					for (int j = i - 1; j >= 0; --j) {
						if (hasPiece[j][ChessX] == 1) {
							moves.push_back({ ChessX, j });
							break;
						}
						else if (hasPiece[j][ChessX] == 2)
							break;
					}
					break;
				}
			}

			for (int i = ChessX + 1; i <= 8; ++i) {
				if (!hasPiece[ChessY][i]) moves.push_back({ i, ChessY });
				else if (hasPiece[ChessY][i]) {
					for (int j = i + 1; j <= 8; ++j) {
						if (hasPiece[ChessY][j] == 1) {
							moves.push_back({ j, ChessY });
							break;
						}
						else if (hasPiece[ChessY][j] == 2)
							break;
					}
					break;
				}
			}

			for (int i = ChessX - 1; i >= 0; --i) {
				if (!hasPiece[ChessY][i]) moves.push_back({ i, ChessY });
				else if (hasPiece[ChessY][i]) {
					for (int j = i - 1; j >= 0; --j) {
						if (hasPiece[ChessY][j] == 1) {
							moves.push_back({ j, ChessY });
							break;
						}
						else if (hasPiece[ChessY][j] == 2)
							break;
					}
					break;
				}
			}

			break;
		default:
			if (ChessY - 1 >= 0 && hasPiece[ChessY - 1][ChessX] != 2)
				moves.push_back({ ChessX, ChessY - 1 });

			if (ChessY < 5) {
				if (ChessX - 1 >= 0 && hasPiece[ChessY][ChessX - 1] != 2)
					moves.push_back({ ChessX - 1, ChessY });

				if (ChessX + 1 <= 8 && hasPiece[ChessY][ChessX + 1] != 2)
					moves.push_back({ ChessX + 1, ChessY });
			}

			break;
		}

	return moves;
	moves.clear();
}


int Chess_Pieces::getState() {
	return hasPiece[ChessY][ChessX];
}

int Chess_Pieces::getStateOf(int x, int y) {
	return hasPiece[y][x];
}

void Chess_Pieces::changeState(int state) {
	hasPiece[ChessY][ChessX] = state;
}

void Chess_Pieces::changeStateOf(int state, int x, int y) {
	hasPiece[y][x] = state;
}

void Chess_Pieces::Update() {
	destRect.x = 38 + (int)(62.5 * ChessX);
	destRect.y = 40 + 65 * ChessY;
}

void Chess_Pieces::Update(int width, int height, int x, int y) {
	destRect.w = width;
	destRect.h = height;

	destRect.x = x;
	destRect.y = y;
}

void Chess_Pieces::Delete() {
	srcRect.h = srcRect.w = srcRect.x = srcRect.y = 0;
	destRect.h = destRect.w = destRect.x = destRect.y = 0;

	SDL_DestroyTexture(objTexture);
}
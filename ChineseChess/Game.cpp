#include "Game.hpp"
#include "Object.hpp"
#include "Chess_Pieces.hpp"
#include "TextManager.hpp"


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;
bool Game::isFinish = false;

Object chess_board;

//Vua = 0, Si = 1-2, Ma = 3-4, Tuong = 5-6, Xe = 7-8, Phao = 9-10, Tot = 11-12-13-14-15
Chess_Pieces red_pieces[16];
Chess_Pieces black_pieces[16];

Object target;
Object endingLayer;

vector<Chess_Pieces> target_moves;
Chess_Pieces target_move;
Chess_Pieces* targeting_piece = nullptr;

int turn;
int mouseX, mouseY;

Text playerTurn, endingMess;

Game::Game() {

}

Game::~Game() {

}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 241, 203, 158, 255);
		}

		isRunning = true;
	}

	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
	}

	turn = 0;

	chess_board.Init("assets/chess_board.jpg", 640, 640, 0, 40);
	/*
	x 0 1 2 3 4 5 6 7 8
	y -----------------
	0|x m t s v s t m x
	1|
	2|  p           p
	3|t   t   t   t   t
	4|
	5|
	6|t   t   t   t   t
	7|  p           p
	8|
	9|x m t s v s t m x

	*/


	//Vua
	red_pieces[0].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Vua, 60, 60, 4, 9);
	black_pieces[0].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Vua, 60, 60, 4, 0);


	//Si
	red_pieces[1].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Si, 60, 60, 3, 9);
	black_pieces[1].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Si, 60, 60, 3, 0);

	red_pieces[2].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Si, 60, 60, 5, 9);
	black_pieces[2].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Si, 60, 60, 5, 0);


	//Ma
	red_pieces[3].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Ma, 60, 60, 1, 9);
	black_pieces[3].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Ma, 60, 60, 1, 0);

	red_pieces[4].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Ma, 60, 60, 7, 9);
	black_pieces[4].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Ma, 60, 60, 7, 0);


	//Tuong
	red_pieces[5].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Tuong, 60, 60, 2, 9);
	black_pieces[5].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Tuong, 60, 60, 2, 0);

	red_pieces[6].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Tuong, 60, 60, 6, 9);
	black_pieces[6].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Tuong, 60, 60, 6, 0);


	//Xe
	red_pieces[7].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Xe, 60, 60, 0, 9);
	black_pieces[7].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Xe, 60, 60, 0, 0);

	red_pieces[8].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Xe, 60, 60, 8, 9);
	black_pieces[8].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Xe, 60, 60, 8, 0);

	//Phao
	red_pieces[9].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Phao, 60, 60, 1, 7);
	black_pieces[9].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Phao, 60, 60, 1, 2);

	red_pieces[10].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Phao, 60, 60, 7, 7);
	black_pieces[10].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Phao, 60, 60, 7, 2);

	//Tot
	for (int i = 11; i <= 15; ++i) {
		red_pieces[i].Init("assets/xiangqi-pieces-sprites.png", 0, 60 * Tot, 60, 60, (0 + (i - 11) * 2), 6);
		black_pieces[i].Init("assets/xiangqi-pieces-sprites.png", 60, 60 * Tot, 60, 60, (0 + (i - 11) * 2), 3);
	}

	for (int i = 0; i < 16; ++i) {
		black_pieces[i].changeState(1);
		red_pieces[i].changeState(2);
	}

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 9; ++j) {
			cout << red_pieces[0].hasPiece[i][j] << ' ';
		}
		cout << '\n';
	}

	target.Init("assets/target.png", 0, 0, 0, 0, 0, 0);

	endingLayer.Init("assets/ending_layer.png", 800, 800, 0, 0);

}


void Game::handleEvents() {
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (Game::isFinish) break;

		SDL_GetMouseState(&mouseX, &mouseY);
		for (auto move : target_moves) {
			if (move.checkMouseOn(mouseX, mouseY)) {
				auto oldPos = targeting_piece->getChessPos();
				auto newPos = move.getChessPos();

				int old_piece_state = targeting_piece->getState();
				int new_piece_state = Chess_Pieces::hasPiece[newPos.second][newPos.first];

				targeting_piece->changeState(0);

				targeting_piece->setPos(newPos.first, newPos.second);
				targeting_piece->changeState(old_piece_state);

				Chess_Pieces::getPiece[oldPos.first][oldPos.second] = nullptr;

				if (new_piece_state != 0) {
					Chess_Pieces::getPiece[newPos.first][newPos.second]->Delete();
				}

				if (newPos == Chess_Pieces::kingPos[0]) {
					Game::isFinish = true;
					endingMess.Init("Red Win!", 240, 60, 210, 320, { 255, 255, 0 });
				}
				
				if (newPos == Chess_Pieces::kingPos[1]) {
					Game::isFinish = true;
					endingMess.Init("Black Win!", 270, 60, 200, 320, { 255, 255, 0 });
				}

				Chess_Pieces::getPiece[newPos.first][newPos.second] = targeting_piece;

				target.Update(0, 0, 0, 0);
				target_moves.clear();
				targeting_piece = nullptr;

				turn++;
				return;
			}
		}

		//RED
		for (int i = 0; i < 16; ++i) {
			if (turn % 2 == 0 && red_pieces[i].checkMouseOn(mouseX, mouseY)) {

				SDL_Rect destRect = red_pieces[i].getDest();
				target.Update(60, 60, destRect.x, destRect.y);
				auto suitable_moves = red_pieces[i].getMoves(i, false);

				target_moves.clear();
				for (auto move : suitable_moves) {
					if (Chess_Pieces::hasPiece[move.second][move.first] == 0)
						target_move.Init("assets/move_target.png", 0, 0, 60, 60, move.first, move.second);
					else
						target_move.Init("assets/move_target.png", 0, 60, 60, 60, move.first, move.second);
					target_moves.push_back(target_move);
				}
				targeting_piece = &red_pieces[i];
				break;
			}

			if (turn & 1 && black_pieces[i].checkMouseOn(mouseX, mouseY)) {
				SDL_Rect destRect = black_pieces[i].getDest();
				target.Update(60, 60, destRect.x, destRect.y);
				auto suitable_moves = black_pieces[i].getMoves(i, true);

				target_moves.clear();
				for (auto move : suitable_moves) {
					if (Chess_Pieces::hasPiece[move.second][move.first] == 0)
						target_move.Init("assets/move_target.png", 60, 0, 60, 60, move.first, move.second);
					else
						target_move.Init("assets/move_target.png", 60, 60, 60, 60, move.first, move.second);
					target_moves.push_back(target_move);
				}
				targeting_piece = &black_pieces[i];
				break;
			}
		}


		//for (int i = 0; i < 10; ++i) {
		//	for (int j = 0; j < 9; ++j) {
		//		cout << Chess_Pieces::hasPiece[i][j] << ' ';
		//	}
		//	cout << '\n';
		//}

		break;
	}
}

void Game::update() {
	for (int i = 0; i < 16; ++i) {
		red_pieces[i].Update();
		std::pair<int, int> dest = red_pieces[i].getChessPos();
		Chess_Pieces::getPiece[dest.first][dest.second] = &red_pieces[i];

		black_pieces[i].Update();
		dest = black_pieces[i].getChessPos();
		Chess_Pieces::getPiece[dest.first][dest.second] = &black_pieces[i];
	}
	target_move.Update();

	Chess_Pieces::kingPos[0] = black_pieces[0].getChessPos();
	Chess_Pieces::kingPos[1] = red_pieces[0].getChessPos();

	if (turn & 1) {
		target.ChangeSrc(60, 0);
		playerTurn.Init("Black turn", 150, 32, 250, 10, { 0, 0, 0 });
	}
	else {
		target.ChangeSrc(0, 0);
		playerTurn.Init("Red turn", 140, 32, 250, 10, { 255, 0, 0 });
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	chess_board.Render();

	for (int i = 0; i < 16; ++i) {
		if (red_pieces[i].getState() != 0)
			red_pieces[i].Render();
		if (black_pieces[i].getState() != 0)
			black_pieces[i].Render();
	}

	target.Render();
	for (auto move : target_moves) {
		move.Render();
	}
	playerTurn.Render();
	if (Game::isFinish) {
		endingLayer.Render(150);
		endingMess.Render();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

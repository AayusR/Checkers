//game.cpp
#include<SFML/Graphics.hpp>
#include "game.h"
#include <iostream>

Game::Game(sf::RenderWindow* win) :  turn(sf::Color::White), window(win){
	board = new Board(win);
	selected = NULL;// (no piece selected)
	running = true;
}

void Game::update()  {
	window->clear();
	board->draw();
	drawValidMoves(validmoves);
	window->display();
}

void Game::reset() {
	delete board;
	board = new Board(window);
	turn = sf::Color::White;
	selected = NULL;
	validmoves.clear();
}

bool Game::select(int row, int col){
	
	if (selected) { // If a piece is already selected, try to move it to the specified position
		bool result = move(row, col);
		
		if (!result) {
			selected = NULL;
			select(row, col);
		}
		
	}

	Piece* p = board->getPiece(row, col);
		
	if (p->colour == turn and p->isPieceOnBoard()) {	
		selected = p;
		
		// Get valid moves for the selected piece
		validmoves = board->get_valid_moves(p);
		return true;
		
	}
	return false;
}

bool Game::move(int row, int col) {
	Piece* piece = board->getPiece(row, col);

	// Check if a piece is selected, the destination is empty, and the move is valid
	if (selected && !piece->isPieceOnBoard() && validmoves.find(std::make_pair(row, col)) != validmoves.end()) {
		board->move(selected, row, col);

		std::vector<Piece>& skipped = validmoves[std::make_pair(row, col)];
		
		// Remove captured pieces from the board
		if (!skipped.empty()) {
			for (const Piece& skippedPiece : skipped) {
				board->removePiece(skippedPiece.row, skippedPiece.col);
			}
		}
		
		changeTurn();
		int win = board->winner();
		if (win == 1 or win == -1) {
			running = false;
		}
	}
	else {
		
		return false;
	}
	return true;
}

void Game::changeTurn() {
	validmoves.clear();
	if (turn == sf::Color::Red) {
		turn = sf::Color::White;	
	}	
	else if(turn == sf::Color::White) {
		turn = sf::Color::Red;
	}
	
}

void Game::drawValidMoves(std::map<std::pair<int, int>, std::vector<Piece>> moves)  {
	
	int row, col;

	// Iterate through each valid move in the map
	for (const auto& move : moves) {
		row = move.first.first;
		col = move.first.second;

		
		border.loadFromFile("resources/borderr.png");
		// Create a sprite for the border
		sf::Sprite s(border);
		s.setScale(sf::Vector2f(1.2, 1.2));
		int x = 900.0 / 8.0 * col + 900.0 / 16.0 + 450;
		int y = 900.0 / 8.0 * row + 900.0 / 16.0 + 30;
		s.setPosition(x, y);
		board->window->draw(s);
	}
}


bool Game::isRunning() {
	return running;
}
//game.h
#pragma once
#include "board.h"

#include<utility>
#include<unordered_set>
#include <SFML/Graphics.hpp>
class Game {
private: 
	
	// valid_moves array
	sf::RenderWindow* window;
	Piece* selected;
	std::map<std::pair<int, int>, std::vector<Piece>> validmoves;
	sf::Texture border;
	bool running;
public:
	sf::Color turn;
	void ai_move(Board* board_);
	Board* board;
	Game(sf::RenderWindow* win);
	void update();
	void reset();
	bool select(int, int);
	bool move(int, int);
	void changeTurn();
	void drawValidMoves(std::map<std::pair<int, int>, std::vector<Piece>> moves);
	bool isRunning();
};
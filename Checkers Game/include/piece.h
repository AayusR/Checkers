//piece.h
#pragma once
#include <SFML/Graphics.hpp>


class Piece {
private:
	bool king;

	float x, y;
	sf::CircleShape circle;
	sf::Texture kingTexture;
	bool onBoard;
	sf::Texture pawnTexture;


public:

	int row, col;

	friend class Board;

	sf::Color colour;

	Piece() {}
	Piece(int row, int col, sf::Color color);

	void makeKing();

	void draw(sf::RenderWindow&);
	void calculatePosition();
	void move(int r, int c);
	void remove();
	bool isPieceOnBoard() const;
};

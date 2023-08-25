//piece.cpp
#include <iostream>
#include "piece.h"

Piece::Piece(int row, int col, sf::Color color) :row(row), col(col), colour(color), king(false),onBoard(false) {
	
	x = 0; y = 0;
	calculatePosition();
	if (colour == sf::Color::Red) {
		kingTexture.loadFromFile("resources/brown_king.png");
	}
	else if (colour == sf::Color::White) {
		kingTexture.loadFromFile("resources/white_king.png");
	}

	if (colour == sf::Color::Red) {
		pawnTexture.loadFromFile("resources/brown_pawn.png");
	}
	else if (colour == sf::Color::White) {
		pawnTexture.loadFromFile("resources/white_pawn.png");
	}
	
}

void Piece::makeKing() {
	king = true;
}

void Piece::remove() {
	onBoard = false;
	colour = sf::Color::Black;
}

void Piece::calculatePosition(){
	x = 900.0 / 8.0 * col + 900.0 / 16.0+435;
	y = 900.0 / 8.0 * row + 900.0 / 16.0+15;
}

void Piece::draw(sf::RenderWindow& window) {

	circle.setPosition(x, y);
	if (colour == sf::Color::Red) {
		circle.setFillColor(sf::Color(255, 40, 0));
	}

	circle.setRadius(76);
	circle.setTexture(&pawnTexture, true);
	if (king) {
		circle.setTexture(&kingTexture,true);
	}
	
	window.draw(circle);
}

void Piece::move(int r,int c) {
	row = r;
	col = c;
	calculatePosition();	
}

bool Piece::isPieceOnBoard() const {
	return onBoard;
}
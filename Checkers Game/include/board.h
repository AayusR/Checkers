// board.h
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "piece.h"
#include <array>
#include <map>
class Board {
private:
	sf::Vector2f BoardPosition;
	sf::RenderWindow* window;
	float length;
	sf::Texture darkTexture,lightTexture;
	sf::Texture bgImage;
	std::array<std::array<sf::RectangleShape,8>, 8> squares;
	float squareSize;
	int red_left = 12, white_left = 12;
	int red_king = 0, white_king = 0;
	Piece board[8][8];
	sf::RectangleShape box;
	sf::SoundBuffer sound_buffer;
	sf::Sound moveSound;
public:
	friend class Game;
	int winner() const;
	Board( sf::RenderWindow* , float l = 900.0);
	void drawSquares();
	void createBoard();
	void draw();
	void move(Piece* piece, int row, int col);
	Piece* getPiece(int row, int col);
	std::map<std::pair<int, int>, std::vector<Piece>> get_valid_moves(Piece* piece) const;
	std::map<std::pair<int, int>, std::vector<Piece>> traverse_left(int start, int stop, int step, sf::Color color, int left, const std::vector<Piece>& skipped) const;
	std::map<std::pair<int, int>, std::vector<Piece>>traverse_right(int start, int stop, int step, sf::Color color, int right, const std::vector<Piece>& skipped) const;
	void removePiece(int row,int col);
	float evaluate() const;
	std::vector<Piece> getAllPiece(sf::Color color) const;
	std::vector<std::vector<Piece>> getBoardCopy() const;
	
};
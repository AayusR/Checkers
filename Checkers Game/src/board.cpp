// board.cpp
#include "board.h"
#include "piece.h"
#include<iostream>
Board::Board(sf::RenderWindow* win,float l) : window(win),length(l), squareSize(l / 8) {
	// Load textures for dark and light squares
	darkTexture.loadFromFile("resources/dark_texture.jpg", sf::IntRect(0, 0, 800, 800));
	lightTexture.loadFromFile("resources/light_texture.jpg", sf::IntRect(0, 0, 800, 800));
	// Load background image
	bgImage.loadFromFile("resources/menu2.jpg", sf::IntRect(0, 0, 800, 800));
	// Initialize the box representing the game board
	box.setSize(sf::Vector2f(l,l));
	box.setPosition((window->getSize().x - box.getSize().x)/2,(window->getSize().y - box.getSize().y)/2) ;
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(10);
	BoardPosition = box.getPosition();

	// Load sound buffer and set it for moveSound
	sound_buffer.loadFromFile("resources/sound.wav");
	moveSound.setBuffer(sound_buffer);
		
	// Calculate the size of textures for squares
	 sf::Vector2u textureSizeD = darkTexture.getSize();
	textureSizeD.x /= 8;
	textureSizeD.y /= 8;

	sf::Vector2u textureSizeL = lightTexture.getSize();
	textureSizeL.x /= 8;
	textureSizeL.y /= 8;

	//Set light and dark texture on squares
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if ((i + j) % 2 == 0) {
				squares[i][j].setTexture(&lightTexture);
				squares[i][j].setTextureRect(sf::IntRect(textureSizeL.x * i, textureSizeL.y * j, textureSizeL.x, textureSizeL.y));
				
			}
			else {
				squares[i][j].setTexture(&darkTexture);
				squares[i][j].setTextureRect(sf::IntRect(textureSizeD.x * i, textureSizeD.y * j, textureSizeD.x, textureSizeD.y));
			}
			
			squares[i][j].setPosition(box.getPosition().x + i * length/8  , box.getPosition().y + j * length/8);
			squares[i][j].setSize(sf::Vector2f(box.getSize().x/8, box.getSize().y / 8));
		}
	}
	// Create the initial state of the game board
	createBoard();
}

// Draw the background image and squares on the game board
void Board::drawSquares() {

	sf::Sprite s(bgImage);
	// Scale the sprite to fit the window size
	float scaleX = static_cast<float>(window->getSize().x) / bgImage.getSize().x;
	float scaleY = static_cast<float>(window->getSize().y) / bgImage.getSize().y;
	s.setScale(scaleX, scaleY);
	// Draw the background image
	window->draw(s);
	// Draw the outline box of the game board
	window->draw(box);
	// Draw each individual square on the game board
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			window->draw(squares[i][j]);
		}
	}
}
   


void Board::createBoard() {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (j % 2 == (i+1 )%2) {// when j is even i is odd and viceversa
				if (i < 3) {
					
					board[i][j] = Piece(i, j, sf::Color::Red);
					board[i][j].onBoard = true;
					
				}
				else if (i > 4) {
					
					
					board[i][j] = Piece(i, j, sf::Color::White);
					board[i][j].onBoard = true;
					
				}
				else {
					//empty square
					board[i][j] = Piece(i, j, sf::Color::Black);
				}
			}
			else {
				// empty square
				board[i][j] = Piece(i, j, sf::Color::Black);
			}
		}
	}
}

void Board::draw() {
	drawSquares();
	//Draw all red and white piece
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece& piece = board[i][j];
			if (piece.isPieceOnBoard()) {
				piece.draw(*window);
			}
		}
	}
}

void Board::move(Piece* piece, int nrow, int ncol) {
	int row = piece->row;
	int col = piece->col;
	
	// Exchange the position on board
	Piece temp = board[nrow][ncol]; 
	board[nrow][ncol] = board[row][col];
	board[row][col] = temp;

	// Update the moved piece's position
	board[nrow][ncol].move(nrow, ncol);
	board[row][col].move(row, col);
	
	moveSound.play();

	
	if (nrow == 0 or nrow == 7) {
		board[nrow][ncol].makeKing();
		if (piece->colour == sf::Color::White)
			white_king++;
		else if (piece->colour == sf::Color::Red)
			red_king++;
	}
}

Piece* Board:: getPiece(int r, int c) {
	return &board[r][c];
}

// Return valid moves of a piece
std::map<std::pair<int, int>, std::vector<Piece>> Board::get_valid_moves(Piece* piece) const {
	
	std::map<std::pair<int, int>, std::vector<Piece>> moves;
	int left = piece->col - 1;
	int right = piece->col + 1;
	int row = piece->row;

	if (piece->colour == sf::Color::White || piece->king) {
		std::map<std::pair<int, int>, std::vector<Piece>> left_moves = traverse_left(row - 1, std::max(row - 3, -1), -1, piece->colour, left, {});
		moves.insert(left_moves.begin(), left_moves.end());

		std::map<std::pair<int, int>, std::vector<Piece>> right_moves = traverse_right(row - 1, std::max(row - 3, -1), -1, piece->colour, right, {});
		moves.insert(right_moves.begin(), right_moves.end());
	}
	if (piece->colour == sf::Color::Red || piece->king) {
		std::map<std::pair<int, int>, std::vector<Piece>> left_moves = traverse_left(row + 1, std::min(row + 3, 8), 1, piece->colour, left, {});
		moves.insert(left_moves.begin(), left_moves.end());

		std::map<std::pair<int, int>, std::vector<Piece>> right_moves = traverse_right(row + 1, std::min(row + 3, 8), 1, piece->colour, right, {});
		moves.insert(right_moves.begin(), right_moves.end());
	}
	return moves;
} 


std::map<std::pair<int, int>, std::vector<Piece>> Board::traverse_left(int start, int stop, int step, sf::Color color, int left, const std::vector<Piece>& skipped) const {
	// Map to store valid moves in the left diagonal direction
	std::map<std::pair<int, int>, std::vector<Piece>> moves;

	// Vector to store captured pieces
	std::vector<Piece> last;

	for (int r = start; r != stop; r += step) {
		if (left < 0) {
			break;
		}

		Piece current = board[r][left];
		if (!current.isPieceOnBoard()) {
			if (last.empty() and !skipped.empty()) {
				break;
			}
			else if (!skipped.empty()) {
			// Combine skipped pieces with previous moves
			moves[std::make_pair(r, left)] = last;
			moves[std::make_pair(r, left)].insert(moves[std::make_pair(r, left)].end(), skipped.begin(), skipped.end());
			
			}
			else {
					moves[std::make_pair(r, left)] = last;
				}
			
			if (!last.empty()) {
				int row = (step == -1) ? std::max(r - 3, 0) : std::min(r + 3, 8);
				std::map<std::pair<int, int>, std::vector<Piece>> left_moves = traverse_left(r + step, row, step, color, left - 1, last);
				moves.insert(left_moves.begin(), left_moves.end());

				std::map<std::pair<int, int>, std::vector<Piece>> right_moves = traverse_right(r + step, row, step, color, left + 1, last);
				moves.insert(right_moves.begin(), right_moves.end());
			}
			break;
		}
		else if (current.colour == color) {
			// Stop if we encounter a piece of the same color
			break;
		}
		else {
			last = { current };
		}

		left -= 1;
	}

	return moves;
}

std::map<std::pair<int, int>, std::vector<Piece>> Board::traverse_right(int start, int stop, int step, sf::Color color, int right, const std::vector<Piece>& skipped) const {
	
	std::map<std::pair<int, int>, std::vector<Piece>> moves;

	// Vector to store captured pieces
	std::vector<Piece> last;

	for (int r = start; r != stop; r += step) {
		if (right >= 8) {
			break;
		}

		Piece current = board[r][right];
		if (!current.isPieceOnBoard()) {
			if (last.empty() && !skipped.empty()) {
				break;
			}
			else if (!skipped.empty()) {
				// Combine skipped pieces with previous moves
				moves[std::make_pair(r, right)] = last;
				moves[std::make_pair(r, right)].insert(moves[std::make_pair(r, right)].end(), skipped.begin(), skipped.end());
			}
			else {
				moves[std::make_pair(r, right)] = last;
			}

			if (!last.empty()) {
				int row = (step == -1) ? std::max(r - 3, 0) : std::min(r + 3, 8);
				std::map<std::pair<int, int>, std::vector<Piece>> left_moves = traverse_left(r + step, row, step, color, right - 1, last);
				moves.insert(left_moves.begin(), left_moves.end());

				std::map<std::pair<int, int>, std::vector<Piece>> right_moves = traverse_right(r + step, row, step, color, right + 1, last);
				moves.insert(right_moves.begin(), right_moves.end());
			}

			break;
		}
		else if (current.colour == color) {
			break;
		}
		else {
			last = { current };
		}

		right += 1;
	}

	return moves;
}


void Board::removePiece(int row, int col) {
	if (board[row][col].colour == sf::Color::Red) {
		red_left--;
	}else if (board[row][col].colour == sf::Color::White) {
		white_left--;
	}
	board[row][col].remove();
}

int Board::winner() const {
	// 1 if white wins
	//-1 if red wins
	// else -> 0
	if (red_left <= 0) {
		return 1;
	}
	else if (white_left <= 0) {
		return -1;
	}
	else 
		return 0;
}

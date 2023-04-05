#include "piece.hpp"
#include <vector>
using namespace std;

/* Shapes look like:
   [
    [1, 0],
    [1, 0],
    [1, 1]
   ]
This would make an L piece*/
Piece::Piece(vector<vector<int>> shape) {
    this->shape = shape;
    this->size[0] = shape[0].size();
    this->size[1] = shape.size();
    inBoard = false;
}

Piece::Piece() {
    this->shape = {{1}};
    this->size[0] = 1;
    this->size[1] = 1;
    inBoard = false;
}

vector<vector<int>> Piece::getShape() {
    return shape;
}

int* Piece::getSize() {
    return size;
}

bool Piece::isInBoard() {
    return inBoard;
}

int Piece::getBoardX() {
    return boardX;
}

int Piece::getBoardY() {
    return boardY;
}

void Piece::setInBoard(bool inBoard) {
    this->inBoard = inBoard;
}

void Piece::setBoardX(int boardX) {
    this->boardX = boardX;
}

void Piece::setBoardY(int boardY) {
    this->boardY = boardY;
}
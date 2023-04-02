#include "piece.hpp"
#include <vector>
using namespace std;

Piece::Piece(vector<vector<int>> shape) {
    this->shape = shape;
    this->size[0] = shape[0].size();
    this->size[1] = shape.size();
}

Piece::Piece() {
    this->shape = {{1}};
    this->size[0] = 1;
    this->size[1] = 1;
}

vector<vector<int>> Piece::getShape() {
    return shape;
}

int* Piece::getSize() {
    return size;
}
#include "piece.hpp"
#include <vector>
using namespace std;

Piece::Piece(vector<int> size, vector<vector<int>> shape) {
    this->size = size;
    this->shape = shape;
}

vector<int> Piece::getSize() {
    return size;
}

vector<vector<int>> Piece::getShape() {
    return shape;
}
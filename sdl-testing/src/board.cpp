#include "board.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

Board::Board() {
}

Board::Board(int w, int h) {
    vector<int> row;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            row.push_back(0);
        }
        board.push_back(row);
    }
}

vector<vector<int>> Board::getBoard() {
    return board;
}

vector<Piece*> Board::getPieces() {
    return pieces;
}

void Board::addPiece(Piece* piece, int x, int y) {
    pieces.push_back(piece);
    vector<vector<int>> shape = piece->getShape();
    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[0].size(); j++) {
            int sum = shape[i][j] + board[i+y][j+x];
            board[i+y][j+x] = sum;
            // cout << sum << " ";
        }
        // cout << endl;
    }
    piece->setInBoard(true);
    piece->setBoardX(x);
    piece->setBoardY(y);
}

void Board::removePiece(Piece* piece) {
    vector<vector<int>> shape = piece->getShape();
    piece->setInBoard(false);
    int x = piece->getBoardX();
    int y = piece->getBoardY();
    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[0].size(); j++) {
            int diff = board[i+y][j+x] - shape[i][j];
            board[i+y][j+x] = diff;
            // cout << sum << " ";
        }
        // cout << endl;
    }
    pieces.erase(remove(pieces.begin(), pieces.end(), piece), pieces.end());
}

bool Board::pieceEligible(Piece piece, int x, int y) {
    vector<vector<int>> shape = piece.getShape();
    if (shape.size() + y > board.size() || shape[0].size() + x > board[0].size()) {
        return false;
    }
    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[0].size(); j++) {
            int sum = shape[i][j] + board[i+y][j+x];
            if (sum > 1) {
                return false;
            }
        }
    }
    return true;
}

// int main () {
//     Piece piece = Piece({{1, 0, 0}, {1, 1, 1}});
//     Piece piece2 = Piece({{1, 1}, {1, 0}});
//     Board board = Board(3, 3);
//     board.addPiece(piece, 0, 1);
//     board.addPiece(piece2, 1, 0);
//     for (int i = 0; i < board.getBoard().size(); i++) {
//         for (int j = 0; j < board.getBoard()[0].size(); j++) {
//             cout << board.getBoard()[i][j] << " ";
//         }
//         cout << endl;
//     } cout << endl;
// }
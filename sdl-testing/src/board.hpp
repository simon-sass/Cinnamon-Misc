#ifndef board_h
#define board_h
#include <vector>
#include "piece.cpp"
using namespace std;

class Board {
    protected:
    vector<vector<int>> board;
    vector<Piece> pieces;

    public:
    Board();
    Board(int w, int h);
    vector<vector<int>> getBoard();
    vector<Piece> getPieces();
    void addPiece(Piece piece, int x, int y);
    bool pieceEligible(Piece piece, int x, int y);
};

#endif
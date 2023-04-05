#ifndef piece_h
#define piece_h
#include <vector>
using namespace std;

class Piece {
    protected:
    vector<vector<int>> shape;
    int size[2];
    bool inBoard;
    int boardX;
    int boardY;

    public:
    Piece(vector<vector<int>> shape);
    Piece();
    vector<vector<int>> getShape();
    int* getSize();
    bool isInBoard();
    int getBoardX();
    int getBoardY();
    void setInBoard(bool inBoard);
    void setBoardX(int boardX);
    void setBoardY(int boardY);
};

#endif
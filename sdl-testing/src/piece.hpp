#ifndef piece_h
#define piece_h
#include <vector>
using namespace std;

class Piece {
    protected:
    vector<vector<int>> shape;
    int size[2];

    public:
    Piece(vector<vector<int>> shape);
    Piece();
    vector<vector<int>> getShape();
    int* getSize();
};

#endif
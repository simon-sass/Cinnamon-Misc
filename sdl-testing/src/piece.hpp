#ifndef piece_h
#define piece_h
#include <vector>
using namespace std;

class Piece {
    private:
    vector<int> size;
    vector<vector<int>> shape;

    public:
    Piece(vector<int> size, vector<vector<int>> shape);
    vector<int> getSize();
    vector<vector<int>> getShape();
};

#endif
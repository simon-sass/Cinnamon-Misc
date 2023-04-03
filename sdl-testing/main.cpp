#include <iostream>
#include <SDL2/SDL.h>
#include "src/piece.cpp"
#include <vector>
#include <array>
using namespace std;

const int WIDTH = 1280, HEIGHT = 720;
const int FPS = 60;
const int frameDelay = 1000/FPS;

// Inherited class that handles the visual aspects of the piece class
class PieceR : public Piece {
    private:
    vector<SDL_Rect> pieceRects;
    int x, y;
    bool beingMoved;

    public:
    PieceR() : Piece() {}

    PieceR(vector<vector<int>> shape, int x = 0, int y = 0) : Piece(shape) {
        this->x = x;
        this->y = y;
        int tempX = x, tempY = y;
        for (int i = 0; i < shape.size(); i++) {
            tempX = x;
            for (int j = 0; j < shape[0].size(); j++) {
                if (shape[i][j]) {
                    pieceRects.push_back({tempX, tempY, 20, 20});
                }
                tempX += 20;
            }
            tempY += 20;
        }
    }
    
    PieceR(Piece piece, int x = 0, int y = 0) {
        this->shape = piece.getShape();
        this->size[0] = piece.getSize()[0];
        this->size[1] = piece.getSize()[1];
        this->x = x;
        this->y = y;
        int tempX = x, tempY = y;
        for (int i = 0; i < shape.size(); i++) {
            tempX = x;
            for (int j = 0; j < shape[0].size(); j++) {
                if (shape[i][j]) {
                    pieceRects.push_back({tempX, tempY, 20, 20});
                }
                tempX += 20;
            }
            tempY += 20;
        }
    }

    vector<SDL_Rect> getPieceRects() {
        return pieceRects;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    bool isBeingMoved() {
        return beingMoved;
    }

    void updateLoc(int x = 0, int y = 0) {
        for (int i = 0; i < pieceRects.size(); i++) {
            pieceRects[i].x += x-this->x;
            pieceRects[i].y += y-this->y;
        }
        this->x = x;
        this->y = y;
    }

    void setBeingMoved(bool moved) {
        beingMoved = moved;
    }

    void drawPiece(SDL_Renderer* renderer) {
        SDL_Rect arr[pieceRects.size()];
        copy(pieceRects.begin(),pieceRects.end(),arr);
        SDL_RenderDrawRects(renderer, arr, pieceRects.size());
    }

    bool pointInPiece(int x, int y) {
        SDL_Point point = {x, y};
        for (SDL_Rect rect : pieceRects) {
            if (SDL_PointInRect(&point, &rect)) {
                return true;
            }
        }
        return false;
    }

    void rotate() {
        vector<vector<int>> newShape;
        for (int c = 0; c < shape[0].size(); c++) {
            vector<int> vector;
            for (int r = 0; r < shape.size(); r++) {
                vector.insert(vector.begin(), shape[r][c]);
            }
            newShape.push_back(vector);
        }
        shape = newShape;

        pieceRects.clear();
        int tempX = x, tempY = y;
        for (int i = 0; i < shape.size(); i++) {
            tempX = x;
            for (int j = 0; j < shape[0].size(); j++) {
                if (shape[i][j]) {
                    pieceRects.push_back({tempX, tempY, 20, 20});
                }
                tempX += 20;
            }
            tempY += 20;
        }
    }
};

int main (int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Inventory Management", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetVSync(renderer, 1);

    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event event;

    vector<PieceR> pieces;

    Piece piece1 = Piece({{1, 0}, {1, 1}});
    Piece piece2 = Piece();

    // PieceR piecer = PieceR(piece, 200, 200);

    pieces.emplace_back(piece1, 200, 200);
    pieces.emplace_back(piece2, 800, 200);

    int mouseX, mouseY, gapX, gapY, mouseState;

    PieceR* pieceBeingMoved = nullptr;

    // Main Loop
    bool running = true;
    while (running) {

        // -----Input handling-----
        mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        if (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouseState = SDL_GetMouseState(NULL, NULL);
                    if (mouseState == 1) {
                        for (int i = 0; i < pieces.size(); i++) {
                            if (pieces[i].pointInPiece(mouseX, mouseY)) {
                                pieceBeingMoved = &pieces[i];
                                pieces[i].setBeingMoved(true);
                                gapX = mouseX - pieces[i].getX();
                                gapY = mouseY - pieces[i].getY();
                            }
                        }
                    }
                    else if (mouseState == 5) {
                        pieceBeingMoved->rotate();
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouseState = SDL_GetMouseState(NULL, NULL);
                    if (mouseState == 0) {
                        if (pieceBeingMoved != nullptr) {
                            pieceBeingMoved->setBeingMoved(false);
                            pieceBeingMoved = nullptr;
                        }
                    }
                    break;
            }
        }

        // -----In-Game Logic-----
        if (pieceBeingMoved != nullptr) {
            pieceBeingMoved->updateLoc(mouseX - gapX, mouseY - gapY);
        }

        // -----Rendering-----

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        for (PieceR piece : pieces) {
            piece.drawPiece(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
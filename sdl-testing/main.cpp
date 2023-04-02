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
    int x;
    int y;

    public:
    PieceR(vector<vector<int>> shape, int x = 0, int y = 0) : Piece(shape) {
        this->x = x;
        this->y = y;
    }
    
    PieceR(Piece piece, int x = 0, int y = 0) {
        this->shape = piece.getShape();
        this->size[0] = piece.getSize()[0];
        this->size[1] = piece.getSize()[1];
        this->x = x;
        this->y = y;
    }

    void drawPiece(SDL_Renderer* renderer) {
        vector<SDL_Rect> pieceRects;
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
        SDL_Rect arr[pieceRects.size()];
        copy(pieceRects.begin(),pieceRects.end(),arr);
        SDL_RenderDrawRects(renderer, arr, pieceRects.size());
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

    Piece piece = Piece({{1, 0}, {1, 1}});

    PieceR piecer = PieceR(piece, 200, 200);

    int mouseX, mouseY;

    while (true) {
        if (SDL_PollEvent(&event)){
            if (SDL_QUIT == event.type) {
                break;
            }
        }

        SDL_GetMouseState(&mouseX, &mouseY);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        piecer.drawPiece(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
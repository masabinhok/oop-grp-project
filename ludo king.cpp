#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "raylib.h"
#include "dice.h"
#include "board.h"

//enum Color { RED, GREEN, BLUE, YELLOW };

const int screenWidth = 1000;
const int screenHeight = 1000;
const int boardSize = 810;
const int cellSize = boardSize / 15;
const Color playersColors[4] = { RED,  GREEN,  YELLOW ,BLUE, };
const int diceSize = 50;   // Size of the dice
const float rollDuration = 0.5f; // Duration of dice roll animation
float dicePosX = screenWidth / 2 - diceSize / 2;
float dicePosY = screenHeight / 2 - diceSize / 2;

class Position {
public:
    int x, y;
    Position() {
        x = 0;
        y = 0;
    }
    Position(int a, int b) {
        x = a;
        y = b;
    }
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

void DrawPiece(Position position1, Color color) {
    Vector2 position = { static_cast<float>(position1.x), static_cast<float>(position1.y) };
    // Draw the base of the piece (a slightly larger circle)
    DrawCircleV(position, 23, DARKGRAY);

    // Draw the main body of the piece (a circle)
    DrawCircleV(position, 20, color);

    // Add a gradient effect by overlaying a semi-transparent circle on top
    DrawCircleGradient(position.x, position.y, 20, Fade(WHITE, 0.3f), Fade(color, 0.3f));

    // Add a small circle on top to give a rounded top
    DrawCircleV(position, 10, WHITE);
}



std::vector<Position> ludoPath = {
    {176,446},{230,446},{284,446},{338,446},{392,446},{446,392},{446,338},{446,284},{446,230},{446,176},{446,122},{500,122},{554,122},{554,176},
    {554,230},{554,284},{554,338},{554,392},{608,446},{662,446},{716,446},{770,446},{824,446},{878,446},{878,500},{878,554},{824,554},{770,554},{716,554},
    {662,554},{608,554},{554,608},{554,662},{554,716},{554,770},{554,824},{554,878},{500,878},{446,878},{446,824},{446,770},{446,716},{446,662},{446,608},
    {392,554},{338,554},{284,554},{230,554},{176,554},{122,554},{122,500},{122,446}
};

std::vector<Position> PiecePath[4]{
 {//red path
    {176,446},{230,446},{284,446},{338,446},{392,446},{446,392},{446,338},{446,284},{446,230},{446,176},{446,122},{500,122},{554,122},{554,176},
    {554,230},{554,284},{554,338},{554,392},{608,446},{662,446},{716,446},{770,446},{824,446},{878,446},{878,500},{878,554},{824,554},{770,554},{716,554},
    {662,554},{608,554},{554,608},{554,662},{554,716},{554,770},{554,824},{554,878},{500,878},{446,878},{446,824},{446,770},{446,716},{446,662},{446,608},
    {392,554},{338,554},{284,554},{230,554},{176,554},{122,554},{122,500},{176,500},{230,500},{284,500},{338,500},{392,500},{446,500}

},

 {//Green path
    {554,176},{554,230},{554,284},{554,338},{554,392},{608,446},{662,446},{716,446},{770,446},{824,446},{878,446},{878,500},{878,554},{824,554},{770,554},{716,554},
    {662,554},{608,554},{554,608},{554,662},{554,716},{554,770},{554,824},{554,878},{500,878},{446,878},{446,824},{446,770},{446,716},{446,662},{446,608},
    {392,554},{338,554},{284,554},{230,554},{176,554},{122,554},{122,500},{122,446},{176,446},{230,446},{284,446},{338,446},{392,446},{446,392},{446,338},
    {446,284},{446,230},{446,176},{446,122},{500,122},{500,176},{500,230},{500,284},{500,338},{500,392},{500,446}
},
 {// Yellow path
    {824,554},{770,554},{716,554},{662,554},{608,554},{554,608},{554,662},{554,716},{554,770},{554,824},{554,878},{500,878},{446,878},{446,824},{446,770},{446,716},{446,662},{446,608},
    {392,554},{338,554},{284,554},{230,554},{176,554},{122,554},{122,500},{122,446}, {176,446},{230,446},{284,446},{338,446},{392,446},{446,392},{446,338},{446,284},{446,230},{446,176},{446,122},{500,122},{554,122},{554,176},
    {554,230},{554,284},{554,338},{554,392},{608,446},{662,446},{716,446},{770,446},{824,446},{878,446},{878,500},{824,500},{770,500},{716,500},{662,500},{608,500},{554,500}
},
{//blue path
    {446,824},{446,770},{446,716},{446,662},{446,608},{392,554},{338,554},{284,554},{230,554},{176,554},{122,554},{122,500},{122,446},{176,446},{230,446},{284,446},{338,446},{392,446},{446,392},{446,338},{446,284},{446,230},{446,176},{446,122},{500,122},{554,122},{554,176},
    {554,230},{554,284},{554,338},{554,392},{608,446},{662,446},{716,446},{770,446},{824,446},{878,446},{878,500},{878,554},{824,554},{770,554},{716,554},
    {662,554},{608,554},{554,608},{554,662},{554,716},{554,770},{554,824},{554,878},{500,878},{500,824},{500,770},{500,716},{500,662},{500,608},{500,554}
}
};

std::vector<Position> Home[4]{
 {//redHome
    {203,203},{311,203},{203,311},{311,311}
},
{//greenHome
    {689,203},{797,203},{689,311},{797,311}
},
 {//yellowHome
    {689,689},{797,689},{689,797},{797,797}
},
{//blueHome
    {203,689},{311,689},{203,797},{311,797}
},


};
class Piece {
public:
    Position position;
    bool inPlay;
    Color color;
    bool inHome;
    bool inFinalHome;
    const Position InitialPosition;
    int ColorIndex;
    int PathIndex;


    // initializer list

    Piece(Color color, Position InitialPosition, int ci) : InitialPosition(InitialPosition), position(InitialPosition), inPlay(false), color(color), inFinalHome(false), inHome(true) {
        ColorIndex = ci;
    }

    void setPosition(const Position& newPos) {
        position = newPos;
    }

    Position getPosition() {
        return position;
    }

    void move(int steps) {
        if (inHome && steps == 1) {
            inHome = false;
            inPlay = true;
            setPosition(PiecePath[ColorIndex][0]);
            PathIndex = 0;

        }
        else {

            PathIndex += steps;
            setPosition(PiecePath[ColorIndex][PathIndex]);


        }

    }


    bool isInHome() {
        return inHome;
    }

    bool isInPlay() const {
        return inPlay;
    }
};


class Player {
public:
    Color color;
    int colorIndex;
    Piece pieces[4];
    bool hasWon;


    Player(Color color, int ci) : color(color), colorIndex(ci), hasWon(false),
        pieces{ Piece(color,Home[ci][0],ci) ,Piece(color,Home[ci][1],ci), Piece(color,Home[ci][2],ci), Piece(color,Home[ci][3],ci) } { }


    int rollDice() {
        return (rand() % 6) + 1;
    }

    void movePiece(int pieceIndex, int steps) {
        if (pieces[pieceIndex].isInPlay() || (steps == 1 && pieces[pieceIndex].isInHome())) {
            pieces[pieceIndex].move(steps);
        }
        else {

        }
    }

    bool allPiecesHome() const {
        // This should be updated to check if all pieces have reached the final position.
        return false;
    }
};

class Board {
public:

    Player players[4];

    Board() : currentPlayerIndex(0),
        players{ Player(playersColors[0],0), Player(playersColors[1],1), Player(playersColors[2],2), Player(playersColors[3],3) } {

    }

    void startGame() {
        while (!gameOver()) {
            update();
        }
        std::cout << "Player " << currentPlayerIndex + 1 << " has won the game!" << std::endl;
    }

private:
    int currentPlayerIndex;

    void update() {
        Player& currentPlayer = players[currentPlayerIndex];
        static int diceValue = 1;
        bool rolling = false; // Flag for dice rolling state
        float rollTime = 0.0f; // Timer for dice roll animation
        int flag = 0;

        while (!flag) {

            if (IsKeyPressed(KEY_SPACE)) {
                rolling = true;

            }


            if (rolling) {
                rollTime += GetFrameTime(); // Increment roll timer
                if (rollTime >= rollDuration) {
                    rolling = false;
                    diceValue = currentPlayer.rollDice(); // Random dice value between 1 and 6
                    flag = 1;
                }
                else {
                    // Optional: Simulate rolling by randomly changing diceValue
                    diceValue = currentPlayer.rollDice();;
                }
            }
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawLudoBoard();
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    DrawPiece(players[i].pieces[j].getPosition(), playersColors[i]);
                }
            }

            DrawDice((int)dicePosX, (int)dicePosY, diceValue);
            EndDrawing();

        }


        // For simplicity, we move the first piece that is available.
        currentPlayer.movePiece(0, diceValue);

        if (currentPlayer.allPiecesHome()) {
            currentPlayer.hasWon = true;
        }

        nextTurn();
    }

    void nextTurn() {
        currentPlayerIndex = (currentPlayerIndex + 1) % 4;
    }

    bool gameOver() const {
        for (int i = 0; i < 4; i++) {
            if (players[i].hasWon) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    InitWindow(screenWidth, screenHeight, "Ludo Game");
    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        // Update
        ClearBackground(RAYWHITE);
        BeginDrawing();
        DrawLudoBoard();
        EndDrawing();

        Board board;
        board.startGame();


    }

    CloseWindow();
    return 0;


}
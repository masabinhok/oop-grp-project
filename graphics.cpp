#include "raylib.h"
#include <cmath>
#include <cstdlib> // For rand()
#include <ctime>   // For time()


const int screenWidth = 800;
const int screenHeight = 800;
const int boardSize = 600;
const int cellSize = boardSize / 15;

Color playersColors[4] = { RED, GREEN, BLUE, YELLOW };

const int diceSize = 50;   // Size of the dice
const float rollDuration = 0.5f; // Duration of dice roll animation

void DrawDice(int x, int y, int value);

void DrawDice(int x, int y, int value) {
    // Draw dice body
    DrawRectangle(x, y, diceSize, diceSize, LIGHTGRAY);

    // Draw dice dots based on value
    int dotSize = 10; // Size of dice dots
    int dotSpacing = 20; // Space between dots

    switch (value) {
    case 1:
        DrawCircle(x + diceSize / 2, y + diceSize / 2, dotSize, BLACK);
        break;
    case 2:
        DrawCircle(x + diceSize / 4, y + diceSize / 4, dotSize, BLACK);
        DrawCircle(x + 3 * diceSize / 4, y + 3 * diceSize / 4, dotSize, BLACK);
        break;
    case 3:
        DrawCircle(x + diceSize / 4, y + diceSize / 4, dotSize, BLACK);
        DrawCircle(x + diceSize / 2, y + diceSize / 2, dotSize, BLACK);
        DrawCircle(x + 3 * diceSize / 4, y + diceSize / 4, dotSize, BLACK);
        break;
    case 4:
        DrawCircle(x + diceSize / 4, y + diceSize / 4, dotSize, BLACK);
        DrawCircle(x + 3 * diceSize / 4, y + diceSize / 4, dotSize, BLACK);
        DrawCircle(x + diceSize / 4, y + 3 * diceSize / 4, dotSize, BLACK);
        DrawCircle(x + 3 * diceSize / 4, y + 3 * diceSize / 4, dotSize, BLACK);
        break;
    case 5:
        DrawCircle(x + diceSize / 4, y + diceSize / 4, dotSize, BLACK);
        DrawCircle(x + 3 * diceSize / 4, y + diceSize / 4, dotSize, BLACK);
        DrawCircle(x + diceSize / 4, y + diceSize / 2, dotSize, BLACK);
        DrawCircle(x + 3 * diceSize / 4, y + diceSize / 2, dotSize, BLACK);
        DrawCircle(x + diceSize / 4, y + 3 * diceSize / 4, dotSize, BLACK);
        DrawCircle(x + 3 * diceSize / 4, y + 3 * diceSize / 4, dotSize, BLACK);
        break;
    case 6:
        DrawCircle(x + diceSize / 4, y + diceSize / 4, dotSize, BLACK);
        DrawCircle(x + 3 * diceSize / 4, y + diceSize / 4, dotSize, BLACK);
        DrawCircle(x + diceSize / 4, y + diceSize / 2, dotSize, BLACK);
        DrawCircle(x + 3 * diceSize / 4, y + diceSize / 2, dotSize, BLACK);
        DrawCircle(x + diceSize / 4, y + 3 * diceSize / 4, dotSize, BLACK);
        DrawCircle(x + 3 * diceSize / 4, y + 3 * diceSize / 4, dotSize, BLACK);
        break;
    }
}


void DrawStar(int centerX, int centerY, int radius, int points, Color color) {
    Vector2* vertices = new Vector2[points * 2];
    float angleStep = PI / points;

    for (int i = 0; i < points * 2; i++) {
        float angle = i * angleStep;
        float r = (i % 2 == 0) ? radius : radius / 2;
        vertices[i] = { centerX + r * cosf(angle), centerY + r * sinf(angle) };
    }

    for (int i = 0; i < points * 2; i++) {
        DrawLineV(vertices[i], vertices[(i + 1) % (points * 2)], color);
    }

    delete[] vertices;

}void DrawLudoBoard() {
    // Draw base square
    DrawRectangle((screenWidth - boardSize) / 2, (screenHeight - boardSize) / 2, boardSize, boardSize, WHITE);
    // Draw safe zone
    DrawRectangle((screenWidth - boardSize + 2 * cellSize) / 2, (screenHeight - cellSize) / 2, 5 * cellSize, cellSize, playersColors[0]);
    DrawRectangle((screenHeight - cellSize) / 2, (screenWidth + 3 * cellSize) / 2, cellSize, 5 * cellSize, playersColors[2]);
    DrawRectangle((screenWidth + 3 * cellSize) / 2, (screenHeight - cellSize) / 2, 5 * cellSize, cellSize, playersColors[3]);
    DrawRectangle((screenHeight - cellSize) / 2, (screenHeight - boardSize + 2 * cellSize) / 2, cellSize, 5 * cellSize, playersColors[1]);

    //Draw stars in red home 
    DrawStar((screenWidth - boardSize + 3 * cellSize) / 2, (screenHeight - 2 * cellSize) / 2, 17.5, 5, playersColors[0]);
    DrawStar((screenWidth - boardSize + 3 * cellSize) / 2, (screenHeight + 2 * cellSize) / 2, 17.5, 5, BLACK);

    //Draw stars in green home
    DrawStar((screenWidth + 2 * cellSize) / 2, (screenHeight - boardSize + 3 * cellSize) / 2, 17.5, 5, playersColors[1]);
    DrawStar((screenWidth - 2 * cellSize) / 2, (screenHeight - boardSize + 3 * cellSize) / 2, 17.5, 5, BLACK);

    // draw stars in yellow home
    DrawStar((screenWidth + boardSize - 3 * cellSize) / 2, (screenHeight - 2 * cellSize) / 2, 17.5, 5, BLACK);
    DrawStar((screenWidth + boardSize - 3 * cellSize) / 2, (screenHeight + 2 * cellSize) / 2, 17.5, 5, playersColors[3]);

    // draw stars in blue home 
   //Draw stars in green home
    DrawStar((screenWidth + 2 * cellSize) / 2, (screenHeight + boardSize - 3 * cellSize) / 2, 17.5, 5, BLACK);
    DrawStar((screenWidth - 2 * cellSize) / 2, (screenHeight + boardSize - 3 * cellSize) / 2, 17.5, 5, playersColors[2]);

    // Draw grid lines
    for (int i = 0; i <= 15; i++) {
        DrawLine((screenWidth - boardSize) / 2 + i * cellSize, (screenHeight - boardSize) / 2, (screenWidth - boardSize) / 2 + i * cellSize, (screenHeight + boardSize) / 2, BLACK);
        DrawLine((screenWidth - boardSize) / 2, (screenHeight - boardSize) / 2 + i * cellSize, (screenWidth + boardSize) / 2, (screenHeight - boardSize) / 2 + i * cellSize, BLACK);
    }

    // Draw home areas
    DrawRectangle((screenWidth - boardSize) / 2, (screenHeight - boardSize) / 2, cellSize * 6, cellSize * 6, playersColors[0]); // Red Home
    DrawRectangle((screenWidth + boardSize) / 2 - cellSize * 6, (screenHeight - boardSize) / 2, cellSize * 6, cellSize * 6, playersColors[1]); // Green Home
    DrawRectangle((screenWidth - boardSize) / 2, (screenHeight + boardSize) / 2 - cellSize * 6, cellSize * 6, cellSize * 6, playersColors[2]); // Blue Home
    DrawRectangle((screenWidth + boardSize) / 2 - cellSize * 6, (screenHeight + boardSize) / 2 - cellSize * 6, cellSize * 6, cellSize * 6, playersColors[3]); // Yellow Home
    // Inside home areas
    DrawRectangle((screenWidth - boardSize + 2 * cellSize) / 2, (screenHeight - boardSize + 2 * cellSize) / 2, cellSize * 4, cellSize * 4, RAYWHITE);
    DrawRectangle((screenWidth + 5 * cellSize) / 2, (screenHeight - boardSize + 2 * cellSize) / 2, cellSize * 4, cellSize * 4, RAYWHITE);
    DrawRectangle((screenWidth - boardSize + 2 * cellSize) / 2, (screenHeight + 5 * cellSize) / 2, cellSize * 4, cellSize * 4, RAYWHITE);
    DrawRectangle((screenWidth + 5 * cellSize) / 2, (screenHeight + 5 * cellSize) / 2, cellSize * 4, cellSize * 4, RAYWHITE);
    // inside home areas circle
    //circle of red
    DrawCircle((screenWidth - boardSize + 4 * cellSize) / 2, (screenHeight - boardSize + 4 * cellSize) / 2, 17, playersColors[0]);
    DrawCircle((screenWidth - boardSize + 8 * cellSize) / 2, (screenHeight - boardSize + 4 * cellSize) / 2, 17, playersColors[0]);
    DrawCircle((screenWidth - boardSize + 4 * cellSize) / 2, (screenHeight - boardSize + 8 * cellSize) / 2, 17, playersColors[0]);
    DrawCircle((screenWidth - boardSize + 8 * cellSize) / 2, (screenHeight - boardSize + 8 * cellSize) / 2, 17, playersColors[0]);
    // circle of blue
    DrawCircle((screenWidth - boardSize + 4 * cellSize) / 2, (screenHeight + 7 * cellSize) / 2, 17, playersColors[2]);
    DrawCircle((screenWidth - boardSize + 8 * cellSize) / 2, (screenHeight + 7 * cellSize) / 2, 17, playersColors[2]);
    DrawCircle((screenWidth - boardSize + 4 * cellSize) / 2, (screenHeight + 11 * cellSize) / 2, 17, playersColors[2]);
    DrawCircle((screenWidth - boardSize + 8 * cellSize) / 2, (screenHeight + 11 * cellSize) / 2, 17, playersColors[2]);
    // circle of green
    DrawCircle((screenWidth + 7 * cellSize) / 2, (screenHeight - boardSize + 4 * cellSize) / 2, 17, playersColors[1]);
    DrawCircle((screenWidth + 11 * cellSize) / 2, (screenHeight - boardSize + 4 * cellSize) / 2, 17, playersColors[1]);
    DrawCircle((screenWidth + 7 * cellSize) / 2, (screenHeight - boardSize + 8 * cellSize) / 2, 17, playersColors[1]);
    DrawCircle((screenWidth + 11 * cellSize) / 2, (screenHeight - boardSize + 8 * cellSize) / 2, 17, playersColors[1]);

    // circle of yellow
    DrawCircle((screenWidth + 7 * cellSize) / 2, (screenHeight + 7 * cellSize) / 2, 17, playersColors[3]);
    DrawCircle((screenWidth + 11 * cellSize) / 2, (screenHeight + 7 * cellSize) / 2, 17, playersColors[3]);
    DrawCircle((screenWidth + 7 * cellSize) / 2, (screenHeight + 11 * cellSize) / 2, 17, playersColors[3]);
    DrawCircle((screenWidth + 11 * cellSize) / 2, (screenHeight + 11 * cellSize) / 2, 17, playersColors[3]);

    // Draw center square
    DrawRectangle((screenWidth - cellSize * 3) / 2, (screenHeight - cellSize * 3) / 2, cellSize * 3, cellSize * 3, DARKGRAY);
    // divison of centre square
    // for red
    DrawTriangle({ screenWidth / 2,screenHeight / 2 }, { (screenWidth - 3 * cellSize) / 2,(screenHeight - 3 * cellSize) / 2 }, { (screenWidth - 3 * cellSize) / 2,(screenHeight + 3 * cellSize) / 2 }, playersColors[0]);
    // for blue
    DrawTriangle({ screenWidth / 2,screenHeight / 2 }, { (screenWidth - 3 * cellSize) / 2,(screenHeight + 3 * cellSize) / 2 }, { (screenWidth + 3 * cellSize) / 2,(screenHeight + 3 * cellSize) / 2 }, playersColors[2]);
    //for green
    DrawTriangle({ (screenWidth + 3 * cellSize) / 2,(screenHeight - 3 * cellSize) / 2 }, { (screenWidth - 3 * cellSize) / 2,(screenHeight - 3 * cellSize) / 2 }, { screenWidth / 2,screenHeight / 2 }, playersColors[1]);
    //for yellow
    DrawTriangle({ (screenWidth + 3 * cellSize) / 2,(screenHeight + 3 * cellSize) / 2 }, { (screenWidth + 3 * cellSize) / 2,(screenHeight - 3 * cellSize) / 2 }, { screenWidth / 2,screenHeight / 2 }, playersColors[3]);

}



int main() {
    InitWindow(screenWidth, screenHeight, "Ludo Game");
    SetTargetFPS(60);

    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    int diceValue = 1; // Current dice value
    bool rolling = false; // Flag for dice rolling state
    float rollTime = 0.0f; // Timer for dice roll animation
    float dicePosX = screenWidth / 2 - diceSize / 2;
    float dicePosY = screenHeight / 2 - diceSize / 2;

    while (!WindowShouldClose()) {
        // Update
        ClearBackground(RAYWHITE);

        DrawLudoBoard();
        if (IsKeyPressed(KEY_SPACE)) {
            rolling = true;
            rollTime = 0.0f; // Reset roll timer
        }

        if (rolling) {
            rollTime += GetFrameTime(); // Increment roll timer
            if (rollTime >= rollDuration) {
                rolling = false;
                diceValue = (rand() % 6) + 1; // Random dice value between 1 and 6
            }
            else {
                // Optional: Simulate rolling by randomly changing diceValue
                diceValue = (rand() % 6) + 1;
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the dice
        DrawDice((int)dicePosX, (int)dicePosY, diceValue);

        EndDrawing();
    }

    CloseWindow();
    return 0;


}

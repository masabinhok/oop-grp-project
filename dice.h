#pragma once

#include "raylib.h"
#include <cmath>
#include <cstdlib> 
#include <ctime>   

extern const int screenWidth ;
extern const int screenHeight ;
extern const int boardSize ;
extern const int cellSize ;

extern const Color playersColors[4] ;


extern const int diceSize ;   // Size of the dice
extern const float rollDuration ; // Duration of dice roll animation
extern void DrawDice(int x, int y, int value, Color colour);



void DrawDice(int x, int y, int value, Color colour) {
    // Draw dice body
    DrawRectangle(x, y, diceSize, diceSize, colour);
	DrawRectangleLines(x, y, diceSize, diceSize, BLACK);

    // Draw dice dots based on value
    int dotSize = 5; // Size of dice dots
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
        DrawCircle(x + diceSize / 2, y + diceSize / 2, dotSize, BLACK);
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



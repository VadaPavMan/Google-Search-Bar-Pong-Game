#include "include/raylib.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

const int screenWidth = 1600, screenHeight = 900;
float lastBackgroundSwitch = 0.0f;
bool showFirstBackground = true;

int main(void)
{
    // Menu Code
    char choose[300] = "Choose The Mode\n\n\n1.\t  EASY\t    [Ez Pz.]\n\n\n2.\t MEDIUM\t [For Casuals.]\n\n\n3.\t HARD\t    [Impossible To Defeat.]";
    char select[100] = "Press Numbers 1 , 2 , 3\n\n\nAccordingly For Choosing The Mode.";

    InitWindow(screenWidth, screenHeight, "Google Pong Game");
    SetTargetFPS(60);

    Image menubackgroundb = LoadImage("assests/blackpage.png");
    ImageResize(&menubackgroundb, 1600, 900);
    Texture2D menubgb = LoadTextureFromImage(menubackgroundb);

    Image menubackgroundw = LoadImage("assests/whitepage.png");
    ImageResize(&menubackgroundw, 1600, 900);
    Texture2D menubgw = LoadTextureFromImage(menubackgroundw);

    while (!WindowShouldClose())
    {

        // Background Refresh In 3 Sec
        if (GetTime() - lastBackgroundSwitch >= 3.0f)
        {
            showFirstBackground = !showFirstBackground;
            lastBackgroundSwitch = GetTime();
        }
        BeginDrawing();

        ClearBackground(RAYWHITE);
        if (showFirstBackground)
        {
            DrawTexture(menubgw, 0, 0, RAYWHITE);
            DrawText(choose, 540, 120, 40, BLACK);
            DrawText(select, 490, 680, 40, BLACK);
        }
        else
        {
            DrawTexture(menubgb, 0, 0, RAYWHITE);
            DrawText(choose, 540, 120, 40, WHITE);
            DrawText(select, 490, 680, 40, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(menubgb);
    UnloadTexture(menubgw);
    return 0;
}
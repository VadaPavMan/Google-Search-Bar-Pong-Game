#include "include/raylib.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

int mainSecond(void)
{
    const int screenWidth = 1600, screenHeight = 900;
    float lastBackgroundSwitch = 0.0f;
    bool showFirstBackground = true;
    // Menu Code
    char choose[300] = "Choose The Mode\n\n\n1.\t  EASY\t    [Ez Pz.]\n\n\n2.\t MEDIUM\t [For Casuals.]\n\n\n3.\t HARD\t    [Impossible To Defeat.]\n\n\n4.\t 2 Players\t    [For PvP]";
    char select[100] = "Press Numbers 1 , 2 , 3 And 4\n\n\nAccordingly For Choosing The Mode.";

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

        if (IsKeyDown(KEY_KP_1) || IsKeyDown(KEY_ONE))
        {
            UnloadTexture(menubgb);
            UnloadTexture(menubgw);
            CloseWindow();
            return 1;
        }
        if (IsKeyDown(KEY_KP_2) || IsKeyDown(KEY_TWO))
        {
            UnloadTexture(menubgb);
            UnloadTexture(menubgw);
            CloseWindow();
            return 2;
        }
        if (IsKeyDown(KEY_KP_3) || IsKeyDown(KEY_THREE))
        {
            UnloadTexture(menubgb);
            UnloadTexture(menubgw);
            CloseWindow();
            return 3;
        }
        if (IsKeyDown(KEY_KP_4) || IsKeyDown(KEY_FOUR))
        {
            UnloadTexture(menubgb);
            UnloadTexture(menubgw);
            CloseWindow();
            return 4;
        }

        EndDrawing();
    }

    UnloadTexture(menubgb);
    UnloadTexture(menubgw);
    CloseWindow();
    return false;
}

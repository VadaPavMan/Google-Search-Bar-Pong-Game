/*******************************************************************************************
 *
 *   raylib [core] example - Basic window
 *
 *   Welcome to raylib!
 *
 *   To test examples, just press F6 and execute raylib_compile_execute script
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   Example originally created with raylib 1.0, last time updated with raylib 1.0
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "include/raylib.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

const int screenWidth = 1600;
const int screenHeight = 900;
float lastBackgroundSwitch = 0.0f;
bool showFirstBackground = true;
float reactionThresholdX = 400.0f;

void ballmovement(Vector2 *position, Vector2 velocity, int playerlose)
{
    if (playerlose == 1)
    {
        position->x += velocity.x;
        position->y += velocity.y;
    }
    else if (playerlose == 0)
    {
        position->x -= velocity.x;
        position->y -= velocity.y;
    }
}

void resetballEasy(Vector2 *position, Vector2 *velocity)
{
    Vector2 pos = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
    Vector2 vel = {10.0f, 4.0f};
    *position = pos;
    *velocity = vel;
}

void resetballMedium(Vector2 *position, Vector2 *velocity)
{
    Vector2 pos = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
    Vector2 vel = {17.0f, 4.0f};
    *position = pos;
    *velocity = vel;
}

void resetballHard(Vector2 *position, Vector2 *velocity)
{
    Vector2 pos = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
    Vector2 vel = {25.0f, 4.0f};
    *position = pos;
    *velocity = vel;
}

void resetballPlayer(Vector2 *position, Vector2 *velocity)
{
    Vector2 pos = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
    Vector2 vel = {22.0f, 4.0f};
    *position = pos;
    *velocity = vel;
}

void Rightbar(Vector2 *position, int diff, float *y)
{
    float easyspeed = 3.0f;
    float mediumspeed = 7.0f;
    float hardspeed = 9.0f;

 if (position->x >= reactionThresholdX)
        {
            if (*y + 360.0 / 2.0 > position->y)
            {
                if (diff == 1)
                {
                    *y -= easyspeed;
                }
                if (diff == 2)
                {
                    *y -= mediumspeed;
                }
                if (diff == 3)
                {
                    *y -= hardspeed;
                }
            }

            if (*y <= 0)
            {
                *y = 0;
            }

            if (*y + 360.0 / 2.0 <= position->y)
            {
                if (diff == 1)
                {
                    *y += easyspeed;
                }
                if (diff == 2)
                {
                    *y += mediumspeed;
                }
                if (diff == 3)
                {
                    *y += hardspeed;
                }
            }

            if (*y + 360 >= GetScreenHeight())
            {
                *y = GetScreenHeight() - 360;
            }
        }   
}

void RightbarPlayer(float *y, float speed)
{
    if (IsKeyDown(KEY_UP))
        {
            *y -= speed;
        }

        if (*y <= 0)
        {
            *y = 0;
        }

        if (IsKeyDown(KEY_DOWN))
        {
            *y += speed;
        }

        if (*y + 360 >= GetScreenHeight())
        {
            *y = GetScreenHeight() - 360;
        }
}

class bars
{
public:
    float height, width;
    float x, y;
    float bar1speed;
};

bars b1, b2;

int mainSecond(void);

int main(void)
{
    // Menu Program
    int diff= mainSecond();
    if(diff == false)
    {
        CloseWindow();
        return 0;
    }

    // Initializations
    int playerwin = 0;
    int player1 = 0;
    int win1 = 0;
    int player2 = 0;

    bool gameover = false;
    bool showtext = true;

    char score[50];
    char gameex[100] = "Press 1 or Enter To Start The New Game.\n\n          Press Esc or 0 To Exit.";
    char blackwin[100] = "Black Search Bar Won.";
    char whitewin[100] = "White Search Bar Won.";
    char musicpause[100] = "Press M To Pause And N To Play The Music.";

    float rotateAngle = 0.0f;
    float speed = 7.0f;

    // Class Objects Declaration
    b1.bar1speed = 7.0f;
    b1.height = 360.0f;
    b1.width = 82.0f;
    b1.x = 50.0f;
    b1.y = screenHeight / 2.0f - 360.0f;

    b2.bar1speed = 7.0f;
    b2.height = 360.0f;
    b2.width = 82.0f;
    b2.x = screenWidth - 92.0f;
    b2.y = screenHeight / 2.0f - 360.0f;

    InitWindow(screenWidth, screenHeight, "Google Pong Game");
    InitAudioDevice();

    SetTargetFPS(60);

    // For Background
    Image backgroundimg = LoadImage("assests/mixpage.png");
    ImageResize(&backgroundimg, 1600, 900);
    Texture2D background = LoadTextureFromImage(backgroundimg);

    // For Left Bar
    Image barwhite = LoadImage("assests/whitebar.png");
    ImageResize(&barwhite, b1.width, b1.height);
    Texture2D bar1 = LoadTextureFromImage(barwhite);

    // For Right Bar
    Image barblack = LoadImage("assests/blackbar.png");
    ImageResize(&barblack, b2.width, b2.height);
    Texture2D bar2 = LoadTextureFromImage(barblack);

    // For Ball
    Image google = LoadImage("assests/icon.png");
    ImageResize(&google, 60, 60);
    Texture2D ball = LoadTextureFromImage(google);

    // For Game Over
    Texture2D finalwinwhite = LoadTexture("assests/whitepage.png");
    Texture2D finalwinblack = LoadTexture("assests/blackpage.png");

    Vector2 position = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
    Vector2 velocity;
    switch (diff)
    {
    case 1:
        velocity = {10.0f, 4.0f};
        break;
    case 2:
        velocity = {17.0f, 4.0f};
        break;
    case 3:
        velocity = {25.0f, 4.0f};
        break;
    case 4:
        velocity = {22.0f, 4.0f};
        break;
    }
    float ballradius = ball.width / 2.0f;

    // Audio
    Music bgmusic = LoadMusicStream("assests/sound.wav");
    PlayMusicStream(bgmusic);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Audio
        UpdateMusicStream(bgmusic);
        if (IsKeyDown(KEY_M))
        {
            PauseMusicStream(bgmusic);
        }
        if (IsKeyDown(KEY_N))
        {
            PlayMusicStream(bgmusic);
            UpdateMusicStream(bgmusic);
        }

        // WINNER CHECK
        if (player1 > 9 || player2 > 9)
        {
            gameover = true;
        }

        if (player1 > 9)
        {
            win1 = 1;
        }
        else if (player1 > 9)
        {
            win1 = 0;
        }

        // Background Refresh In 3 Sec
        if (GetTime() - lastBackgroundSwitch >= 3.0f)
        {
            showFirstBackground = !showFirstBackground;
            lastBackgroundSwitch = GetTime();
        }

        // Check For Collisions
        ballmovement(&position, velocity, playerwin);

        if (CheckCollisionCircleRec(Vector2{position.x, position.y}, ballradius, Rectangle{b1.x, b1.y, b1.width, b1.height}))
        {
            velocity.x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{position.x, position.y}, ballradius, Rectangle{b2.x, b2.y, b2.width, b2.height}))
        {
            velocity.x *= -1;
        }

        // For Ball Rotation
        rotateAngle += 2.0f;
        if (rotateAngle >= 360.0f)
        {
            rotateAngle -= 360.0f;
        }

        // Score Board
        sprintf(score, "Player: %d | CPU: %d ", player1, player2);

        // Left Bar Movement
        if (IsKeyDown(KEY_W))
        {
            b1.y -= speed;
        }

        if (b1.y <= 0)
        {
            b1.y = 0;
        }

        if (IsKeyDown(KEY_S))
        {
            b1.y += speed;
        }

        if (b1.y + 360 >= GetScreenHeight())
        {
            b1.y = GetScreenHeight() - 360;
        }

        // Right Bar Movement

        if(diff == 1 || diff == 2 || diff == 3)
        {
            Rightbar(&position, diff, &b2.y);
        }
        else if(diff == 4)
        {
            RightbarPlayer(&b2.y, speed); 
        }

        // Ball Collision.

        if (position.y - (float)ball.height / 2.0f <= 0 || position.y + (float)ball.height / 2.0f >= 930)
        {
            velocity.y *= -1.0f;
        }

        // Round Win Update And Ball Position Reset.
        if (position.x - (float)ball.width / 2.0f <= 0 || position.x + (float)ball.width / 2.0f >= 1660)
        {
            if (position.x - (float)ball.width / 2.0f <= 0)
            {
                playerwin = 1;
                player2 += 1;
                if (diff == 1)
                {
                    resetballEasy(&position, &velocity);
                }
                if (diff == 2)
                {
                    resetballMedium(&position, &velocity);
                }
                if (diff == 3)
                {
                    resetballHard(&position, &velocity);
                }
                if(diff == 4)
                {
                    resetballPlayer(&position, &velocity);
                }

            }
            else if (position.x + (float)ball.width / 2.0f >= 1630)
            {
                playerwin = 0;
                player1 += 1;
                if (diff == 1)
                {
                    resetballEasy(&position, &velocity);
                }
                if (diff == 2)
                {
                    resetballMedium(&position, &velocity);
                }
                if (diff == 3)
                {
                    resetballHard(&position, &velocity);
                }
                if(diff == 4)
                {
                    resetballPlayer(&position, &velocity);
                }
            }
        }

        // Main Contents Draw.
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(bar1, b1.x, b1.y, WHITE);
        DrawTexture(bar2, (b2.x) - 50, b2.y, WHITE);
        DrawText(musicpause, 1010, 850, 20, BLACK);
        if (showtext)
        {
            DrawText(score, 633.0f, 700.0f, 30.0f, WHITE);
        }
        DrawLine(785.0f, 0, 785.0f, 900.0f, WHITE);

        DrawTexturePro(ball, (Rectangle){0, 0, (float)ball.width, (float)ball.height}, (Rectangle){position.x - (float)ball.width / 2.0f, position.y - (float)ball.height / 2.0f, (float)ball.width, (float)ball.height}, (Vector2){(float)ball.width / 2, (float)ball.height / 2}, rotateAngle, WHITE);

        // Game Over Check
        if (gameover == true)
        {
            player1 = 0;
            player2 = 0;
            showtext = false;
            if (win1 == 1)
            {
                if (showFirstBackground)
                {

                    DrawTexture(finalwinwhite, 0, 0, WHITE);
                    DrawText(whitewin, 530, 260, 50, BLACK);
                    DrawText(gameex, 530, 700, 30, BLACK);
                    DrawText(musicpause, 1010, 850, 20, BLACK);
                }
                else
                {
                    DrawTexture(finalwinblack, 0, 0, WHITE);
                    DrawText(whitewin, 530, 260, 50, WHITE);
                    DrawText(gameex, 530, 700, 30, WHITE);
                    DrawText(musicpause, 1010, 850, 20, WHITE);
                }
            }
            else if (win1 == 0)
            {
                if (showFirstBackground)
                {

                    DrawTexture(finalwinwhite, 0, 0, WHITE);
                    DrawText(blackwin, 530, 260, 50, BLACK);
                    DrawText(gameex, 530, 700, 30, BLACK);
                    DrawText(musicpause, 1010, 850, 20, BLACK);
                }
                else
                {
                    DrawTexture(finalwinblack, 0, 0, WHITE);
                    DrawText(blackwin, 530, 260, 50, WHITE);
                    DrawText(gameex, 530, 700, 30, WHITE);
                    DrawText(musicpause, 1010, 850, 20, WHITE);
                }
            }

            // For New Game And To Exit Program.
            if (IsKeyDown(KEY_ONE) || IsKeyDown(KEY_KP_1) || IsKeyDown(KEY_ENTER))
            {
                CloseWindow();
                system("game.exe");
                
            }
            if (IsKeyDown(KEY_ZERO) || IsKeyDown(KEY_KP_0) || IsKeyDown(KEY_ESCAPE))
            {
                UnloadTexture(background);
                UnloadTexture(bar1);
                UnloadTexture(bar2);
                UnloadTexture(ball);
                UnloadTexture(finalwinwhite);
                UnloadTexture(finalwinblack);
                CloseAudioDevice();
                CloseWindow();
                return 0;
            }
        }

        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(bar1);
    UnloadTexture(bar2);
    UnloadTexture(ball);
    UnloadTexture(finalwinwhite);
    UnloadTexture(finalwinblack);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

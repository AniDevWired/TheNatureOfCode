/* EXERCISE - 0.1*/

#include "raylib.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 700;

typedef struct Ball {
    Vector2 position;
    float radius;
} Ball;

void setValue(Ball *ball);
void checkEdgeCollision(Ball *ball);

int main(void) {

    // window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Random Walker");

    // Ball
    Ball ball;
    setValue(&ball);

    while (!WindowShouldClose()) {

        int choice = GetRandomValue(1, 100);

        if(choice <= 40) {
            ball.position.x++;
        }

        if (choice >= 41 && choice <= 50) {
            ball.position.x--;
        }

        if (choice >= 51 && choice <= 60) {
            ball.position.y--;
        }

        if(choice >= 61) {
            ball.position.y++;
        }

        checkEdgeCollision(&ball);
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawCircleV(ball.position, ball.radius+10, BLUE);
            DrawCircleV(ball.position, ball.radius, SKYBLUE);

        EndDrawing();

        TraceLog(LOG_INFO, TextFormat("%d", choice));

    }

    CloseWindow();
}

void setValue(Ball *ball) {
    ball->position.x = GetScreenWidth()/2.0f;
    ball->position.y = GetScreenHeight()/2.0f;

    ball->radius = GetRandomValue(30, 50);
}

void checkEdgeCollision(Ball *ball) {

    if(ball->position.x > GetScreenWidth() - ball->radius) {
        ball->position.x = GetScreenWidth() - ball->radius;
    }

    if (ball->position.x < ball->radius) {
        ball->position.x = ball->radius;
    }

    if (ball->position.y > GetScreenHeight() - ball->radius) {
        ball->position.y = GetScreenHeight() - ball->radius;
    }

    if (ball->position.y < ball->radius) {
        ball->position.y = ball->radius;
    }
}
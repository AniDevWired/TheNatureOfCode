#include "raylib.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 700;

typedef struct Ball {
    Vector2 position;
    float radius;
} Ball;

void setValue(Ball *ball);

int main(void) {

    // window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Random Walker");

    // Ball
    Ball ball;
    setValue(&ball);

    while (!WindowShouldClose()) {

        int choice = GetRandomValue(0, 3);

        if(choice == 0) {
            ball.position.x++;
        }

        if (choice == 1) {
            ball.position.x--;
        }

        if (choice == 2) {
            ball.position.y++;
        }

        if(choice == 3) {
            ball.position.y--;
        }
        
        BeginDrawing();

            //ClearBackground(RAYWHITE);
            DrawCircleV(ball.position, ball.radius+10, BLUE);
            DrawCircleV(ball.position, ball.radius, SKYBLUE);

        EndDrawing();

    }

    CloseWindow();
}

void setValue(Ball *ball) {
    ball->position.x = GetScreenWidth()/2.0f;
    ball->position.y = GetScreenHeight()/2.0f;

    ball->radius = GetRandomValue(30, 50);
}
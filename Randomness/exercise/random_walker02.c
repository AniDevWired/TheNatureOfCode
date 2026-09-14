/* BALL WHICH HAS 50% CHANCE TO FOLLOW MOUSE */

#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 900;

const float FRICTION = 0.998f;
float ACC_SPEED = 1000.0f;

typedef struct Ball {
    Vector2 position;
    Vector2 velocity;
    Vector2 acc;
    float radius;
} Ball;

void setValue(Ball *ball);
void checkEdgeCollision(Ball *ball);
void drawArrow(Vector2 start, Vector2 dir, float scale, float thick, Color color);

int main(void) {

    // window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "BALL FOLLOWER");
    SetTargetFPS(100);

    // Ball
    Ball ball;
    setValue(&ball);

    bool canDraw = false;

    while (!WindowShouldClose()) {

        int choice = GetRandomValue(1, 100);
        float dt = GetFrameTime();
        Vector2 mousePos = GetMousePosition();
        Vector2 dir = Vector2Subtract(mousePos, ball.position);

        if(choice <= 50) {
            if(mousePos.x < 1.0f && mousePos.y < 1.0f) {
                canDraw = false;
            } else {
                float dist = Vector2Length(dir);

                if(dist > 5.0f) {
                    Vector2 normal = Vector2Normalize(dir);
                    ball.acc = Vector2Scale(normal, ACC_SPEED);
                    Vector2 frameAcc = Vector2Scale(ball.acc, dt);
                    ball.velocity = Vector2Add(ball.velocity, frameAcc);
                    ball.velocity = Vector2Scale(ball.velocity, FRICTION);
                    ball.position = Vector2Add(ball.position, Vector2Scale(ball.velocity, dt));
                } else {
                    ball.position = mousePos;
                    ball.velocity = (Vector2){0};
                    ball.acc = (Vector2){0};
                }

                checkEdgeCollision(&ball);
                canDraw = true;
            }
        }

        // if(choice >= 51 && choice <= 63) {
        //     ball.position.x++;
        // }

        // if(choice >= 64 && choice <= 77) {
        //     ball.position.x--;
        // }

        // if(choice >= 78 && choice <= 90) {
        //     ball.position.y++;
        // }

        // if(choice >= 91) {
        //     ball.position.y--;
        // }
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("RED: Vector representing towards mouse", 10, 10, 24, BLACK);
            DrawText("BLUE: Vector representing Velocity of ball", 10, 36, 24, BLACK);
            DrawText("GREEN: Vector representing Acceleration of ball", 10, 62, 24, BLACK);
            DrawCircleV(ball.position, ball.radius+10, BLUE);
            DrawCircleV(ball.position, ball.radius, SKYBLUE);
            if(canDraw) {
                drawArrow(ball.position, dir, .75f, 3, RED);
                drawArrow(ball.position, ball.velocity, .45f, 3, BLUE);
                drawArrow(ball.position, ball.acc, .25f, 3, GREEN);
            }

        EndDrawing();

        //TraceLog(LOG_INFO, TextFormat("%0.2f, %0.2f", mousePos.x, mousePos.y));

    }

    CloseWindow();
}

void setValue(Ball *ball) {
    ball->position.x = GetScreenWidth()/2.0f;
    ball->position.y = GetScreenHeight()/2.0f;

    ball->velocity = (Vector2) {0};
    ball->acc = (Vector2) {0};

    ball->radius = 40.0f;
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

void drawArrow(Vector2 start, Vector2 dir, float scale, float thick, Color color) {
    
    Vector2 scaleEnd = (Vector2) {
        start.x + (dir.x) * scale,
        start.y + (dir.y) * scale
    };

    DrawLineEx(start, scaleEnd, thick, color);

    Vector2 normal = Vector2Normalize(dir);
    Vector2 tangent = (Vector2) {-normal.y, normal.x};

    float headLength = 15.0f;
    float headWidth = 7.0f;

    Vector2 base = (Vector2) {
        scaleEnd.x - normal.x * headLength,
        scaleEnd.y - normal.y * headLength
    };

    Vector2 left = (Vector2) {
        base.x + tangent.x * headWidth,
        base.y + tangent.y * headWidth
    };

    Vector2 right = (Vector2) {
        base.x - tangent.x * headWidth,
        base.y - tangent.y * headWidth
    };

    DrawTriangle(scaleEnd, right, left, color);
}
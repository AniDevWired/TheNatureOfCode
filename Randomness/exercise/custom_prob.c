/* GAUSSIAN WALK - Ex 06 WITH ACCEPT REJECT*/

#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define STEP 10

void checkEdgeCollision(Vector2 *pos);
float accept_reject(void);

int main(void) {

    //window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Gaussian Walk");

    // canvas
    RenderTexture2D canvas = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);
    EndTextureMode();

    // walker
    Vector2 position = {SCREEN_WIDTH/2.0f , SCREEN_HEIGHT/2.0f};

    while(!WindowShouldClose()) {

        float xStep = accept_reject() * STEP;
        float yStep = accept_reject() * STEP;

        int a = GetRandomValue(0, 1);
        if(1 == a) {
            xStep *= -1;
        }
        int b = GetRandomValue(0, 1);
        if(1 == b) {
            yStep *= -1;
        }

        position.x += xStep;
        position.y += yStep;

        checkEdgeCollision(&position);

        BeginTextureMode(canvas);
            DrawPixelV(position, RED);
        EndTextureMode();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureRec(canvas.texture, (Rectangle) {0, 0, (float) canvas.texture.width, -(float)canvas.texture.height}, (Vector2) {0 ,0}, RAYWHITE);
        EndDrawing();
    }

    UnloadRenderTexture(canvas);
    CloseWindow();

    return 0;
}

void checkEdgeCollision(Vector2 *pos) {

    if(pos->x > GetScreenWidth()) {
        pos->x = GetScreenWidth();
    }

    if (pos->x < 0.0f) {
        pos->x = 0.0f;
    }

    if (pos->y > GetScreenHeight()) {
        pos->y = GetScreenHeight();
    }

    if (pos->y < 0.0f) {
        pos->y = 0.0f;
    }
}

float accept_reject() {
    while (true) {
        float a = GetRandomValue(1, 100);
        float prob = a;
        float b = GetRandomValue(1, 100);

        if(b < prob) {
            return a/100.0f;
        }
    }
}
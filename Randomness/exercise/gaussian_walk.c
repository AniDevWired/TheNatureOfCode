/* GAUSSIAN WALK - Ex 05*/

#include "raylib.h"
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

float normal_distribution(float mean, float sd);
void checkEdgeCollision(Vector2 *pos);

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

        float xStep = normal_distribution(0, 4);
        float yStep = normal_distribution(0, 4);

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

float normal_distribution(float mean, float sd) {
    float u1 = (GetRandomValue(1, 1000000) / 1000001.0f);
    float u2 = (GetRandomValue(1, 1000000) / 1000001.0f);

    float z = sqrtf(-2.0 * logf(u1)) * cosf(2.0f * PI * u2);

    return mean + z*sd;
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
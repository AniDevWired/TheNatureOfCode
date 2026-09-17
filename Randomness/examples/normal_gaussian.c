/* A GAUSSIAN DISTRIBUTION */

#include "raylib.h"
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

float normal_distribution(float mean, float sd);

int main(void) {

    // window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "A GAUSSIAN DISTRIBUTION");
    SetTargetFPS(60);

    RenderTexture2D canvas = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);
    EndTextureMode();

    int height = SCREEN_HEIGHT/2;

    while(!WindowShouldClose()) {

        float x = normal_distribution(400.0f, 80.0f);

        BeginTextureMode(canvas);
            DrawCircleV((Vector2) {x, height},8, (Color) {0, 0, 0, 10});
        EndTextureMode();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureRec(canvas.texture, (Rectangle) {0, 0, (float) canvas.texture.width, -(float)canvas.texture.height}, (Vector2) {0 ,0}, BLACK);
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
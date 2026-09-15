#include "raylib.h"

#define MAX_RANDOM_COUNT 100

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 700

float accept_reject(void);

int main(void) {

    // window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Random Walker");

    int randomCount[MAX_RANDOM_COUNT];

    for(int i = 0; i < MAX_RANDOM_COUNT; i++) {
        randomCount[i] = 0;
    }

    int width = GetScreenWidth() / MAX_RANDOM_COUNT;

    while (!WindowShouldClose()) {

        float cal = accept_reject() * MAX_RANDOM_COUNT;

        int idx = (int)cal;
        randomCount[idx]++;
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            for(int i = 0; i < MAX_RANDOM_COUNT; i++) {
                DrawRectangle(i * width, GetScreenHeight() - randomCount[i], width-1, randomCount[i], SKYBLUE);
            }

        EndDrawing();

        TraceLog(LOG_INFO, TextFormat("%d", idx));

    }

    CloseWindow();
}

float accept_reject(void) {
    while (true) {
        float a = GetRandomValue(1, 100);
        float prob = a;
        float b = GetRandomValue(1, 100);

        if(b < prob) {
            return a/100.0f;
        }
    }
}
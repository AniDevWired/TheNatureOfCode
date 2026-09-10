#include "raylib.h"

#define MAX_RANDOM_COUNT 20

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 700;

int main(void) {

    // window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Random Walker");

    int randomCount[MAX_RANDOM_COUNT];

    for(int i = 0; i < MAX_RANDOM_COUNT; i++) {
        randomCount[i] = 0;
    }

    int width = GetScreenWidth() / MAX_RANDOM_COUNT;

    while (!WindowShouldClose()) {

        int idx = GetRandomValue(0, MAX_RANDOM_COUNT - 1);
        randomCount[idx]++;
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            for(int i = 0; i < MAX_RANDOM_COUNT; i++) {
                DrawRectangle(i * width, GetScreenHeight() - randomCount[i], width-1, randomCount[i], SKYBLUE);
            }

        EndDrawing();

    }

    CloseWindow();
}
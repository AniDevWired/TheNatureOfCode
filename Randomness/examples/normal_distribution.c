/* Normal Distribution - Bell curve */

/* 

    Formula I have taken from this: https://en.wikipedia.org/wiki/Normal_distribution

*/

#include "raylib.h"
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define sample_space 10000

float PDF(float x, float mu, float var);

int main(void) {

    //window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bell Curve");

    int heights[sample_space];
    int min = 100;
    int max = 500;

    for(int i = 0; i < sample_space; i++) {
        heights[i] = GetRandomValue(min, max);
    }

    double mean = 0;
    for(int i = 0; i < sample_space; i++) {
        mean += heights[i];
    }

    mean /= sample_space;

    double var = 0;

    for (int i = 0; i < sample_space; i++) {
        var += powf((heights[i] - mean), 2.0f);
    }

    var /= sample_space;

    // for graph
    int padX = 100;
    int graphEndX = WINDOW_WIDTH-padX;
    int graphWidth = WINDOW_WIDTH-padX*2;
    int graphBottom = WINDOW_HEIGHT-100;

    float scale = 100000.0f; // since y-axis value is small so I have to scale it up

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            DrawLineEx((Vector2) {padX, graphBottom}, (Vector2) {graphEndX, graphBottom}, 7, BLACK);

            Vector2 prevPoint = {0};

            for (int pixelX = padX; pixelX <= graphEndX; pixelX++) {
                
                float pct = (float) (pixelX - padX) / graphWidth;
                float currentHeightSample = min + pct * (max - min);

                float pointY = PDF(currentHeightSample, (float) mean, (float)var);

                float pointYScale = graphBottom - (pointY * scale);

                Vector2 currentPoint = {(float) pixelX, pointYScale};

                if(pixelX > padX)
                    DrawLineEx(prevPoint, currentPoint, 4, GREEN);

                prevPoint=currentPoint;
            }   
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

// probability distribution formula
float PDF(float x, float mu, float var) {
    float d = sqrtf(2.0f*PI*var); // denomitaor
    float n = 1.0f/d; // numerator
    float exp = -(powf((x - mu), 2.0f) / (2.0f * var)); // exponent

    float expression = n * expf(exp);

    return expression;
}
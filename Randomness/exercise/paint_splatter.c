/* EX - 04 PAINT SPLATTER */

#include "raylib.h"
#include <math.h>

#define RAYGUI_IMPLEMENTATION
#include "../../lib/raygui.h"

#define SCREEN_DIM 800

float normal_distribution(float mean, float sd);

int main(void) {

    // window
    InitWindow(SCREEN_DIM, SCREEN_DIM, "COLOUR SPLATTER");
    SetTargetFPS(30);

    RenderTexture2D canvas = LoadRenderTexture(SCREEN_DIM, SCREEN_DIM); // canvas

    BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);
    EndTextureMode();

    // Controls
    float spreadSlider = 80.0f;
    float sizeSlider = 8.0f;
    float sizespSlider = 5.0f;
    float baseHueSlider = 30.0f;
    float huespSlider = 30.0f;
    float alphaSlider = 100.0f;

    while(!WindowShouldClose()) {

        float x = normal_distribution(400.0f, spreadSlider);
        float y = normal_distribution(400.0f, spreadSlider);

        float paintHue = normal_distribution(baseHueSlider, huespSlider);
        float paintSat = normal_distribution(80, 20);
        float paintBright = normal_distribution(80, 20);

        float size = normal_distribution(sizeSlider, sizespSlider);

        if(size <= 0.0f) {
            size = 0.001f;
        }

        Color splatterColor = ColorFromHSV(paintHue, paintSat/100.0f, paintBright/100.0f);
        splatterColor.a = alphaSlider;

        BeginTextureMode(canvas);
            DrawCircleV((Vector2) {x, y},size, splatterColor);
        EndTextureMode();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureRec(canvas.texture, (Rectangle) {0, 0, (float) canvas.texture.width, -(float)canvas.texture.height}, (Vector2) {0 ,0}, RAYWHITE);
            //slider
            GuiSlider((Rectangle){ 60, 40, 200, 20 }, "Spread", TextFormat("%0.2f", spreadSlider), &spreadSlider, 10, 200);
            GuiSlider((Rectangle){ 60, 80, 200, 20 }, "Size", TextFormat("%0.2f", sizeSlider), &sizeSlider, 2, 50);
            GuiSlider((Rectangle){ 70, 120, 200, 20 }, "Size spread", TextFormat("%0.2f", sizespSlider), &sizespSlider, 1, 10);
            GuiSlider((Rectangle){ SCREEN_DIM - 240, 40, 200, 20 }, "Base Hue", TextFormat("%0.2f", baseHueSlider), &baseHueSlider, 0, 360);
            GuiSlider((Rectangle){ SCREEN_DIM - 240, 80, 200, 20 }, "Hue spread", TextFormat("%0.2f", huespSlider), &huespSlider, 0, 180);
            GuiSlider((Rectangle){ SCREEN_DIM - 240, 120, 200, 20 }, "Alpha", TextFormat("%0.2f", alphaSlider), &alphaSlider, 5, 255);
            if (GuiButton((Rectangle){ SCREEN_DIM/2.0f - 50, SCREEN_DIM - 40, 100, 25 }, "Clear Canvas")) {
                BeginTextureMode(canvas);
                    ClearBackground(RAYWHITE);
                EndTextureMode();
            }

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
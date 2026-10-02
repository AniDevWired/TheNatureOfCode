/* 2D NOISE && EX-08 09 */

#include <math.h>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "../../lib/raygui.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

float interpolate(float a, float b, float t);
float getRandom(float x);
float perlinNoise(float x, int octaves); // Keep your 1D perlin declaration
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);

int main(void) {

    //window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2D NOISE");
    SetTargetFPS(60);

    RenderTexture2D canvas = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    float xOff = 0.0f;
	float xStep = 0.0f;
	float yStep = 0.0f;
    float octaves = 4;

    while (!WindowShouldClose()) {

		if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
			BeginTextureMode(canvas);
				ClearBackground(RAYWHITE);
				xOff = xStep;
				for(int i = 0; i < WINDOW_WIDTH; i++) {
					float yOff = yStep;
					for(int j = 0; j < WINDOW_HEIGHT; j++) {
						float hue = map(perlinNoise(xOff + yOff, octaves), -0.5f, 0.5f, 0, 360);
						float saturation = map(perlinNoise(xOff + yOff, octaves), -0.5f, 0.5f, 0, 180);
						float value = map(perlinNoise(xOff + yOff, octaves), -0.5f, 0.5f, 0, 180);
						Color color = ColorFromHSV(hue, saturation/100.0f, value/100.0f);
						color.a = 140;
						DrawPixelV((Vector2) {i, j}, color);
						yOff += 0.01f;
					}
					xOff += 0.01f;
				}
			EndTextureMode();
		}

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureRec(canvas.texture, (Rectangle){ 0, 0, (float)canvas.texture.width, (float)-canvas.texture.height }, (Vector2){ 0, 0 }, WHITE);
			GuiSlider((Rectangle) {50, WINDOW_HEIGHT - 20 - 30, 70, 20}, "Octaves", TextFormat("%d", (int) octaves), (float *)&octaves, 1, 10);
			GuiSlider((Rectangle) {50, WINDOW_HEIGHT - 20 - 60, 70, 20}, "xStep", TextFormat("%0.2f", xStep), &xStep, 0, 10);
			GuiSlider((Rectangle) {50, WINDOW_HEIGHT - 20 - 90, 70, 20}, "yStep", TextFormat("%0.2f", yStep), &yStep, 0, 10);
			DrawText("Right-click to refresh noise", 10, 10, 24, BLUE);
        EndDrawing();
    }

    UnloadRenderTexture(canvas);
    CloseWindow();
    return 0;
}


//### FOR 1D PERLIN NOISE ###//

float interpolate(float a, float b, float t) {
	// if (0.0 > t)
	// 	return a;
	// if (1.0 < t)
	// 	return b;

	// This is linear interpolation. It does not provide smooth appearance.
	//return a + t * (b - a);

	// Use this cubic interpolation instead, for a smooth appearance:
	return a + t * t * (3.0 - 2.0 * t) * (b - a);

	// Use this for an even smoother result with a second derivative equal to zero on boundaries:
	//return a + t * t * t * (t * (6.0 * t - 15.0) + 10.0) * (b - a);
}
float getRandom(float x) {
	// No precomputed gradients mean this works for any number of grid coordinates
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2; // rotation width
	unsigned a = x;
	a *= 3284157443u;
	a ^= a << s | a >> (w - s);
	a *= 1911520717u;
	a ^= a << s | a >> (w - s);
	a *= 2048419325u;

	// Scale the random value to [-0.5, 0.5]
	float random = (float)(a) / (float)(~(0u)) -0.5f;

	return random;
}

float map(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
 	// Ensure the input value is within the current range
    value = fminf(fmaxf(value, fromLow), fromHigh);

    // Map the value to the target range
    return toLow + (toHigh - toLow) * ((value - fromLow) / (fromHigh - fromLow));
}

float perlinNoise(float x, int octaves) {
	float frequency = 1.0f;
	float amplitude = 1.0f;
	float total = 0;

	for (int i = 0; i < octaves; i++) {
		x *= frequency;
		float x0 = (float)floor(x);
		float x1 = x0 + 1;

		float gX0 = map(getRandom(x0), -0.5f, 0.5f, -amplitude/2, amplitude/2);
		float gX1 = map(getRandom(x1), -0.5f, 0.5f, -amplitude/2, amplitude/2);

		float t = x - x0;

		total += interpolate(gX0, gX1, t);

		frequency *= 2.0f;
		amplitude *= 0.5f;
	}

	return total;
}

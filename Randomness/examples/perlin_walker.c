/* PERLIN NOISE WALKER */

#include <math.h>
#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

float interpolate(float a, float b, float t);
float getRandom(float x);
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);
float perlinNoise(float x, int octaves);

void checkEdgeCollision(Vector2 *pos);

int main(void) {

    //window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Perlin Walker");
	SetTargetFPS(60);

    float tx = 0.0f;
    float ty = 10000.0f;

    Vector2 pos = {WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f};

    RenderTexture2D canvas = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

    BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);
    EndTextureMode();

    while (!WindowShouldClose()) {

        float x = perlinNoise(tx, 1) * WINDOW_WIDTH * 0.8f + WINDOW_WIDTH/2.0f;
        float y = perlinNoise(ty, 1) * WINDOW_HEIGHT * 0.8f + WINDOW_HEIGHT/2.0f;
        pos = (Vector2) {x, y};
        checkEdgeCollision(&pos);

        BeginTextureMode(canvas);
            DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, (Color){ 245, 245, 245, 1 });
            DrawCircleV(pos, 50, SKYBLUE);
            DrawCircleLinesV(pos, 50, BLUE);
        EndTextureMode();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureRec(canvas.texture, (Rectangle) {0, 0, (float) canvas.texture.width, -(float)canvas.texture.height}, (Vector2) {0 ,0}, RAYWHITE);

            DrawCircleV(pos, 50, SKYBLUE);
            DrawCircleLinesV(pos, 50, BLUE);
        EndDrawing();

		tx += 0.005;
        ty += 0.005;
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
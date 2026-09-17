/* PERLIN NOISE */

#include <math.h>
#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

float interpolate(float a, float b, float t);
float getRandom(float x);
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);
float perlinNoise(float x, int octaves);

int main(void) {

    //window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Perlin Noise");
	SetTargetFPS(60);

    float time = 0.0f;

    while (!WindowShouldClose()) {

        float xOff = time;

		Vector2 prevPos = {0};

        BeginDrawing();
            ClearBackground(RAYWHITE);
            for(int i = 0; i < WINDOW_WIDTH; i++) {
                float y = perlinNoise(xOff, 4) * WINDOW_HEIGHT * 0.5f + WINDOW_HEIGHT/2.0f;
                xOff += 0.01;
				Vector2 currentPos = (Vector2) {i, y};
                DrawLineEx(prevPos, currentPos, 1, SKYBLUE);
				prevPos = currentPos;
            }
        EndDrawing();
		time += 0.01;
    }

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

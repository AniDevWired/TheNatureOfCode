#include "raylib.h"
#include "math.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    float angle = 0;
    float radius = 20.0f;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        float dt = GetFrameTime();

        // Update
        //----------------------------------------------------------------------------------
        if(IsKeyDown(KEY_W)) {
            cubePosition.z -= 0.01*dt*50;
        }
        if(IsKeyDown(KEY_S)) {
            cubePosition.z += 0.01*dt*50;
        }
        if(IsKeyDown(KEY_A)) {
            cubePosition.x -= 0.01*dt*50;
        }
        if(IsKeyDown(KEY_D)) {
            cubePosition.x += 0.01*dt*50;
        }
        if(IsKeyDown(KEY_SPACE)) {
            cubePosition.y += 0.01*dt*50;
        }
        if(IsKeyDown(KEY_LEFT_SHIFT)) {
            cubePosition.y -= 0.01*dt*50;
        }

        angle += 0.001f;

        camera.position.x = camera.target.x + sinf(angle*dt*50) * radius;
        camera.position.z = camera.target.z + cosf(angle*dt*50) * radius;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                DrawGrid(10000, 1.0f);

            EndMode3D();

            DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
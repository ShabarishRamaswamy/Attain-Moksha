#include "raylib.h"
#include <math.h>

int main() {
    // 1. Initialize the Window
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Attain Moksha");

    // 2. Setup the First-Person Camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 0.0f }; // Player eye level
    camera.target = (Vector3){ 0.0f, 2.0f, 1.0f };   // Looking forward
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       // Which way is 'up'
    camera.fovy = 60.0f;                             // Field of view
    camera.projection = CAMERA_PERSPECTIVE;

    // Lock the cursor inside the window for proper FPS camera movement
    // DisableCursor();
    SetTargetFPS(60);

    // Time and Sun
    // Future idea: Daylight Savings.
    float timeOfDay = 0.0f;
    const float DAY_DURATION = 720.0f; // 12 Minutes
    const float NIGHT_DURATION = 720.0f; // 12 Minutes
    const float FULL_CYCLE = DAY_DURATION + NIGHT_DURATION;

    // 3. Main Game Loop
    while (!WindowShouldClose()) {
        
        // --- UPDATE ---
        // Raylib handles the WASD and Mouse math automatically here!
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        timeOfDay += GetFrameTime();
        if (timeOfDay > FULL_CYCLE) {
            timeOfDay = 0.0f;
        }

        float angle = (timeOfDay / FULL_CYCLE) * 2.0f * PI;
        float orbitRadius = 300.0f;

        Vector3 sunPos = {
            cosf(angle) * orbitRadius,
            sinf(angle) * orbitRadius,
            150.0f
        };

        Color currentSkyColor = BLACK;
        if (sunPos.y > 0) {
            float sunIntensity = sunPos.y / orbitRadius;

            currentSkyColor.r = (unsigned char)(SKYBLUE.r * sunIntensity);
            currentSkyColor.g = (unsigned char)(SKYBLUE.g * sunIntensity);
            currentSkyColor.b = (unsigned char)(SKYBLUE.b * sunIntensity + 50 * (1.0f - sunIntensity));
            currentSkyColor.a = 255;
        }

        // --- DRAW ---
        BeginDrawing();
            
            // Clear the screen with a basic sky color (we'll animate this later)
            ClearBackground(SKYBLUE); 

            // Draw 3D Elements
            BeginMode3D(camera);
                float shading = (sunPos.y > 0) ? (sunPos.y / 300.0f): 0.0f;

                Color cubeColor = {
                    (unsigned char)(180 * shading),
                    (unsigned char)(120 * shading),
                    (unsigned char)(60 * shading),
                    255
                };
                // Draw a solid cube at the center of the world (X:0, Y:1, Z:0) with size 2.0
                DrawCube((Vector3){ 3.0f, 1.0f, 3.0f }, 2.0f, 2.0f, 2.0f, cubeColor);
                DrawCubeWires((Vector3){ 3.0f, 1.0f, 3.0f }, 2.0f, 2.0f, 2.0f, DARKGRAY);

                // A temporary grid so you can feel the movement
                DrawGrid(100, 1.0f); 

                if (sunPos.y > -20.0f) {
                    DrawSphere(sunPos, 15.0f, YELLOW);
                }
            EndMode3D();

            // Draw 2D UI Elements (Overlays on top of 3D)
            // This is your center marker / crosshair
            int centerX = screenWidth / 2;
            int centerY = screenHeight / 2;
            DrawLine(centerX - 10, centerY, centerX + 10, centerY, DARKGRAY);
            DrawLine(centerX, centerY - 10, centerX, centerY + 10, DARKGRAY);

            DrawText(TextFormat("Time: %.1f / %.1f sec", timeOfDay, FULL_CYCLE), 10, 10, 20, LIGHTGRAY);

        EndDrawing();
    }

    // 4. Clean Up
    CloseWindow();
    return 0;
}
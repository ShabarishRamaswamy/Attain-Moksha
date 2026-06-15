#include "raylib.h"

int main() {
    // 1. Initialize the Window
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Procedural 3D World");

    // 2. Setup the First-Person Camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 0.0f }; // Player eye level
    camera.target = (Vector3){ 0.0f, 2.0f, 1.0f };   // Looking forward
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       // Which way is 'up'
    camera.fovy = 60.0f;                             // Field of view
    camera.projection = CAMERA_PERSPECTIVE;

    // Lock the cursor inside the window for proper FPS camera movement
    DisableCursor(); 
    
    // Target 60 frames per second
    SetTargetFPS(60);

    // 3. Main Game Loop
    while (!WindowShouldClose()) {
        
        // --- UPDATE ---
        // Raylib handles the WASD and Mouse math automatically here!
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // --- DRAW ---
        BeginDrawing();
            
            // Clear the screen with a basic sky color (we'll animate this later)
            ClearBackground(SKYBLUE); 

            // Draw 3D Elements
            BeginMode3D(camera);
                // A temporary grid so you can feel the movement
                DrawGrid(100, 1.0f); 
            EndMode3D();

            // Draw 2D UI Elements (Overlays on top of 3D)
            // This is your center marker / crosshair
            int centerX = screenWidth / 2;
            int centerY = screenHeight / 2;
            DrawLine(centerX - 10, centerY, centerX + 10, centerY, DARKGRAY);
            DrawLine(centerX, centerY - 10, centerX, centerY + 10, DARKGRAY);

        EndDrawing();
    }

    // 4. Clean Up
    CloseWindow();
    return 0;
}
#include <raylib.h>
#define RSPLINES_IMPLEMENTATION
#define RSPLINES_1D
#define RSPLINES_3D
#include <rsplines.h>

int main()
{
    InitWindow(640, 480, "Spline Test Suite");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Confirm linking succeeds
        float point = GetSplinePointBezierCubic1D(0.0f, 0.25f, 0.75f, 1.0f, 0.5f);

        BeginDrawing();
        ClearBackground(BLACK);

        // Should be a dot in about the center of the window
        DrawPixelV((Vector2){ 320.0f + point, 240.0f }, WHITE);

        EndDrawing();
    }

    CloseWindow();
}

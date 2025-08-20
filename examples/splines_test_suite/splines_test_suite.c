#include <raylib.h>
#define RSPLINES_IMPLEMENTATION
#define RSPLINES_1D
#define RSPLINES_3D
#include <rsplines.h>

int main()
{
    InitWindow(640, 480, "Spline Test Suite");

    SetTargetFPS(60);

    Vector2 startPos = { 160.0f, 120.0f };
    Vector2 endPos = { 480.0f, 360.0f };

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_ONE)) startPos = GetMousePosition();
        if (IsKeyDown(KEY_TWO)) endPos = GetMousePosition();

        float length = GetSplineLengthLinear2D(startPos, endPos);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawLineV((Vector2){ 10.0f, 10.0f }, (Vector2) { 10.0f + length, 10.0f }, BLUE);
        DrawSplineSegmentLinear(startPos, endPos, 1.0f, WHITE);

        EndDrawing();
    }

    CloseWindow();
}

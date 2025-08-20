#include <raylib.h>
#include <raymath.h>
#define RSPLINES_IMPLEMENTATION
#define RSPLINES_1D
#define RSPLINES_3D
#include <rsplines.h>

enum Degree {
    SPLINE_LINEAR,
    SPLINE_QUAD,
    SPLINE_CUBIC,
};

int main()
{
    InitWindow(640, 480, "Spline Test Suite");

    SetTargetFPS(0);

    int degree = SPLINE_LINEAR;
    Vector2 startPos = { 160.0f, 120.0f };
    Vector2 controlPos1 = { 320.0f, 120.0f };
    Vector2 controlPos2 = { 320.0f, 360.0f };
    Vector2 endPos = { 480.0f, 360.0f };
    const Vector2 extentSize = { 2.0f, 2.0f };
    const Vector2 boxSize = { extentSize.x*2, extentSize.y*2 };
    const float dotSeparation = 8.0f;

    Vector2 *draggingPoint = NULL;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ONE)) degree = SPLINE_LINEAR;
        if (IsKeyPressed(KEY_TWO)) degree = SPLINE_QUAD;
        if (IsKeyPressed(KEY_THREE)) degree = SPLINE_CUBIC;
        
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) draggingPoint = NULL;

        if (draggingPoint == NULL && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            float shortestDistSqr = INFINITY;
            Vector2 mousePos = GetMousePosition();
            int pointCount = degree + 2;
            for (int i = 0; i < pointCount; ++i)
            {
                Vector2 *point = NULL;
                switch (i)
                {
                case 0: point = &startPos; break;
                case 1: point = &endPos; break;
                case 2: point = &controlPos1; break;
                case 3: point = &controlPos2; break;
                default: break;
                }
                if (point == NULL) continue;
                float distSqr = Vector2DistanceSqr(*point, mousePos);
                if ((distSqr <= 25.0f) && (distSqr < shortestDistSqr))
                {
                    shortestDistSqr = distSqr;
                    draggingPoint = point;
                }
            }
        }

        if (draggingPoint != NULL) *draggingPoint = GetMousePosition();

        BeginDrawing();
        ClearBackground(BLACK);

        if (degree == SPLINE_LINEAR)
        {
            DrawSplineSegmentLinear(startPos, endPos, 10.0f, GRAY);
            Vector2 normal = GetSplineNormalLinear2D(startPos, endPos);
            float length = (GetSplineLengthLinear2D(startPos, endPos)/dotSeparation);
            for (int i = 0; i <= (int)length; ++i)
            {
                float t = (float)i/length;

                Vector2 point = GetSplinePointLinear2D(startPos, endPos, t);
                DrawRectangleV(Vector2Subtract(point, extentSize), boxSize, GREEN);

                Vector2 outlinePointAbove = Vector2Add(GetSplinePointLinear2D(startPos, endPos, t), Vector2Scale(normal, 5.0f));
                DrawRectangleV(Vector2Subtract(outlinePointAbove, extentSize), boxSize, RED);

                Vector2 outlinePointBelow = Vector2Add(GetSplinePointLinear2D(startPos, endPos, t), Vector2Scale(normal, -5.0f));
                DrawRectangleV(Vector2Subtract(outlinePointBelow, extentSize), boxSize, BLUE);
            }
        }
        else if (degree == SPLINE_QUAD)
        {
            DrawSplineSegmentBezierQuadratic(startPos, controlPos1, endPos, 10.0f, GRAY);
            float length = 40.0f;
            for (int i = 0; i <= (int)length; ++i)
            {
                float t = (float)i/length;

                Vector2 normal = GetSplineNormalBezierQuad2D(startPos, controlPos1, endPos, t);

                Vector2 point = GetSplinePointBezierQuad2D(startPos, controlPos1, endPos, t);
                DrawRectangleV(Vector2Subtract(point, extentSize), boxSize, GREEN);

                Vector2 outlinePointAbove = Vector2Add(GetSplinePointBezierQuad2D(startPos, controlPos1, endPos, t), Vector2Scale(normal, 5.0f));
                DrawRectangleV(Vector2Subtract(outlinePointAbove, extentSize), boxSize, RED);

                Vector2 outlinePointBelow = Vector2Add(GetSplinePointBezierQuad2D(startPos, controlPos1, endPos, t), Vector2Scale(normal, -5.0f));
                DrawRectangleV(Vector2Subtract(outlinePointBelow, extentSize), boxSize, BLUE);
            }
        }
        else if (degree == SPLINE_CUBIC)
        {
            DrawSplineSegmentBezierCubic(startPos, controlPos1, controlPos2, endPos, 10.0f, GRAY);
            float length = 40.0f;
            for (int i = 0; i <= (int)length; ++i)
            {
                float t = (float)i/length;

                Vector2 normal = GetSplineNormalBezierCubic2D(startPos, controlPos1, controlPos2, endPos, t);

                Vector2 point = GetSplinePointBezierCubic2D(startPos, controlPos1, controlPos2, endPos, t);
                DrawRectangleV(Vector2Subtract(point, extentSize), boxSize, GREEN);

                Vector2 outlinePointAbove = Vector2Add(GetSplinePointBezierCubic2D(startPos, controlPos1, controlPos2, endPos, t), Vector2Scale(normal, 5.0f));
                DrawRectangleV(Vector2Subtract(outlinePointAbove, extentSize), boxSize, RED);

                Vector2 outlinePointBelow = Vector2Add(GetSplinePointBezierCubic2D(startPos, controlPos1, controlPos2, endPos, t), Vector2Scale(normal, -5.0f));
                DrawRectangleV(Vector2Subtract(outlinePointBelow, extentSize), boxSize, BLUE);
            }
        }

        DrawCircleLinesV(startPos, 5.0f, MAGENTA);
        DrawCircleLinesV(endPos, 5.0f, MAGENTA);
        if (degree == SPLINE_LINEAR)
        {
            DrawLineV(startPos, endPos, MAGENTA);
        }
        if (degree == SPLINE_QUAD)
        {
            DrawLineV(startPos, controlPos1, MAGENTA);
            DrawLineV(endPos, controlPos1, MAGENTA);
            DrawCircleLinesV(controlPos1, 5.0f, MAGENTA);
        }
        else if (degree == SPLINE_CUBIC)
        {
            DrawLineV(startPos, controlPos1, MAGENTA);
            DrawLineV(endPos, controlPos2, MAGENTA);
            DrawCircleLinesV(controlPos2, 5.0f, MAGENTA);
            DrawCircleLinesV(controlPos1, 5.0f, MAGENTA);
        }

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();
}

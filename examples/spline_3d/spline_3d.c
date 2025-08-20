#include <raylib.h>
#include <raymath.h>
#define RSPLINES_IMPLEMENTATION
#define RSPLINES_3D
#include <rsplines.h>

int main()
{
    InitWindow(640, 480, "Spline Test Suite");

    DisableCursor();
    SetTargetFPS(0);

    Camera3D camera = {
        { 5, 5, 5 },
        { 0, 0, 0 },
        { 0, 1, 0 },
        45.0f,
        CAMERA_PERSPECTIVE
    };

    Vector3 points[] = {
        { 0, 0, 0 },
        { -1, 5, 0 },
        { 5, 1, -8 },
        { 5, 3, 0 },
    };

    float draggingDistance = INFINITY;
    Vector3 *draggingPoint = NULL;

    while (!WindowShouldClose())
    {
        Vector2 screenCenter = { GetRenderWidth()/2.0f, GetRenderHeight()/2.0f };
        Ray mouseRay = GetScreenToWorldRay(screenCenter, camera);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) draggingPoint = NULL;

        if (draggingPoint == NULL && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            draggingDistance = INFINITY;
            for (int i = 0; i < 4; ++i)
            {
                RayCollision collision = GetRayCollisionSphere(mouseRay, points[i], 0.1f);
                if (collision.hit && collision.distance < draggingDistance)
                {
                    draggingDistance = collision.distance;
                    draggingPoint = &points[i];
                }
            }
        }

        if (draggingPoint != NULL)
        {
            *draggingPoint = Vector3Add(mouseRay.position, Vector3Scale(mouseRay.direction, draggingDistance));
        }

        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(10, 1);

                Vector3 pointPrev = { 0 };
                Vector3 point1Prev = { 0 };
                Vector3 point2Prev = { 0 };
                Vector3 point3Prev = { 0 };
                Vector3 point4Prev = { 0 };
                for (int i = 0; i <= 100; ++i)
                {
                    float t = (float)i/100;
                    Vector3 point = GetSplinePointBezierCubic3D(points[0], points[1], points[2], points[3], t);
                    Vector3 tangent = GetSplineTangentBezierCubic3D(points[0], points[1], points[2], points[3], t);
                    Vector3 normalH = Vector3Normalize(Vector3CrossProduct(tangent, (Vector3){ 0, 1, 0 }));
                    Vector3 normalV = Vector3Normalize(Vector3CrossProduct(normalH, tangent));
                    Vector3 point1 = Vector3Add(pointPrev, Vector3Scale(normalH, 0.1f));
                    Vector3 point2 = Vector3Add(pointPrev, Vector3Scale(normalH, -0.1f));
                    Vector3 point3 = Vector3Add(pointPrev, Vector3Scale(normalV, 0.1f));
                    Vector3 point4 = Vector3Add(pointPrev, Vector3Scale(normalV, -0.1f));
                    if (i > 0)
                    {
                        DrawLine3D(pointPrev, point, GRAY);
                        DrawLine3D(point1Prev, point1, RED);
                        DrawLine3D(point2Prev, point2, ORANGE);
                        DrawLine3D(point3Prev, point3, GREEN);
                        DrawLine3D(point4Prev, point4, LIME);
                    }
                    pointPrev = point;
                    point1Prev = point1;
                    point2Prev = point2;
                    point3Prev = point3;
                    point4Prev = point4;
                }
                for (int i = 0; i < 4; ++i)
                {
                    DrawSphereWires(points[i], 0.1f, 2, 6, ((&points[i] == draggingPoint)? YELLOW : MAGENTA));
                }
                DrawLine3D(points[0], points[1], MAGENTA);
                DrawLine3D(points[3], points[2], MAGENTA);

            EndMode3D();

            DrawCircleLinesV(screenCenter, 2.0f, BLUE);

            DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();
}

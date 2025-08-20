#include <raylib.h>
#include <raymath.h>
#define RSPLINES_IMPLEMENTATION
#define RSPLINES_1D
#define RSPLINES_3D
#include <rsplines.h>

int main()
{
    InitWindow(640, 480, "Spline 3D");

    DisableCursor();
    SetTargetFPS(0);

    Camera3D camera = {
        { 10, 10, 10 },
        { 0, 0, 0 },
        { 0, 1, 0 },
        45.0f,
        CAMERA_PERSPECTIVE
    };

    float thicks[] = { 0.0f, 1.0f, -0.675f, 0.5f };

    Vector3 points[] = {
        { 0.0f, 1.0f, -2.0f },
        { -1.0f, 3.0f, 1.0f },
        { 1.0f, 1.0f, 3.0f },
        { -1.0f, 5.0f, 5.0f },
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
                Vector3 ctrl1, ctrl2;
                GetSplineControlBezierCubic3D(points[0], points[1], points[2], points[3], &ctrl1, &ctrl2);
                for (int i = 0; i <= 100; ++i)
                {
                    float t = (float)i/100;
                    float thick = GetSplinePointBezierCubic1D(thicks[0], thicks[1], thicks[2], thicks[3], t); // Variable thickness
                    Vector3 point = GetSplinePointBezierCubic3D(points[0], ctrl1, ctrl2, points[3], t);
                    Vector3 tangent = GetSplineTangentBezierCubic3D(points[0], ctrl1, ctrl2, points[3], t);
                    Vector3 normalH = Vector3Normalize(Vector3CrossProduct(tangent, (Vector3){ 0, 1, 0 }));
                    Vector3 normalV = Vector3Normalize(Vector3CrossProduct(normalH, tangent));
                    Vector3 point1 = Vector3Add(point, Vector3Scale(normalH, thick));
                    Vector3 point2 = Vector3Add(point, Vector3Scale(normalH, -thick));
                    Vector3 point3 = Vector3Add(point, Vector3Scale(normalV, thick));
                    Vector3 point4 = Vector3Add(point, Vector3Scale(normalV, -thick));
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
                //DrawLine3D(points[0], ctrl1, MAGENTA);
                //DrawLine3D(points[3], ctrl2, MAGENTA);

            EndMode3D();

            DrawCircleLinesV(screenCenter, 2.0f, BLUE);

            DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();
}

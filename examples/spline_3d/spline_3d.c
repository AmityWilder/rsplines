#include <raylib.h>
#include <raymath.h>
#define RSPLINES_IMPLEMENTATION
#define RSPLINES_1D
#define RSPLINES_2D
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

    SplineSegmentBezierCubic1 thickness = { 0.0f, 1.0f, -0.675f, 0.5f };

    SplineSegmentBezierCubic3 spline = {
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
            Vector3 *splinePoints = (Vector3 *)&spline;
            for (int i = 0; i < 4; ++i)
            {
                RayCollision collision = GetRayCollisionSphere(mouseRay, splinePoints[i], 0.1f);
                if (collision.hit && collision.distance < draggingDistance)
                {
                    draggingDistance = collision.distance;
                    draggingPoint = &splinePoints[i];
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
                SplineSegmentBezierCubic3 spline1 = SplineSegmentBezierCubic3FromPoints(spline.startPos, spline.startControlPos, spline.endControlPos, spline.endPos);
                for (int i = 0; i <= 100; ++i)
                {
                    float t = (float)i/100;
                    float thick = SplineSegmentBezierCubic1Point(thickness, t);
                    Vector3 point = SplineSegmentBezierCubic3Point(spline1, t);
                    Vector3 tangent = SplineSegmentBezierCubic3Tangent(spline1, t);
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
                const Vector3 *splineA = (Vector3 *)&spline;
                for (int i = 0; i < 4; ++i)
                {
                    DrawSphereWires(splineA[i], 0.1f, 2, 6, ((&splineA[i] == draggingPoint)? YELLOW : MAGENTA));
                }

                if (draggingPoint != NULL)
                {
                    Vector3 cubeSize = { 0.05f, 0.05f, 0.05f };
                    Vector3 xy = { draggingPoint->x, draggingPoint->y, 0 };
                    Vector3 xz = { draggingPoint->x, 0, draggingPoint->z };
                    Vector3 yz = { 0, draggingPoint->y, draggingPoint->z };
                    DrawLine3D(yz, *draggingPoint, RED);
                    DrawLine3D(xz, *draggingPoint, GREEN);
                    DrawLine3D(xy, *draggingPoint, BLUE);
                    DrawCubeV(yz, cubeSize, RED);
                    DrawCubeV(xz, cubeSize, GREEN);
                    DrawCubeV(xy, cubeSize, BLUE);
                }

            EndMode3D();

            DrawCircleLinesV(screenCenter, 2.0f, BLUE);

            DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();
}

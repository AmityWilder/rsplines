/*******************************************************************************************
*
*   rsplines v0.1 - A spline math library
*
*   DESCRIPTION:
*       rsplines is an extended spline library based on raylib
*
*   FEATURES:
*       - Spline math
*
*   LIMITATIONS:
*       - Curvature is not currently supported for any number of dimensions except for 2
*       - Majority of support is currently limited to Bezier curves
*       - "GetSplineSegmentNearestT...()" and "GetSplineSegmentLength...()" functions currently only available for
*         Linear splines due to no closed definition existing for higher spline degree
*       - 3D spline normal requires knowing what angle around the tangent to take the normal at
*
*   CONFIGURATION:
*       #define RSPLINES_IMPLEMENTATION
*           Generates the implementation of the library into the included file
*           If not defined, the library is in header only mode and can be included in other headers
*           or source files without problems. But only ONE file should hold the implementation
*
*       #define RSPLINES_1D
*           Includes 1D spline features
*
*       #define RSPLINES_2D
*           Includes 2D spline features
*
*       #define RSPLINES_3D
*           Includes 3D spline features
*
*   VERSIONS HISTORY:
*       0.1 (20-Aug-2025) Initial release. Implemented by Amy Wilder
*
*   DEPENDENCIES:
*       raylib 5.0  - Types
*
*   CONTRIBUTORS:
*       Amy Wilder:   Initial implementation of basic components (2025)
*
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2025 Amy Wilder (@AmityWilder)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#ifndef RSPLINES_H
#define RSPLINES_H

#define RSPLINES_VERSION_MAJOR 0
#define RSPLINES_VERSION_MINOR 1
#define RSPLINES_VERSION_PATCH 0
#define RSPLINES_VERSION  "0.1.0"

// Function specifiers in case library is build/used as a shared library (Windows)
// NOTE: Microsoft specifiers to tell compiler that symbols are imported/exported from a .dll
#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #define RSPLAPI __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define RSPLAPI __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
    #endif
#endif

// Function specifiers definition
#ifndef RSPLAPI
    #define RSPLAPI       // Functions defined as 'extern' by default (implicit specifiers)
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

#if defined(RSPLINES_1D)
    // 1D bounds (range)
    typedef struct BoundingBox1 {
        float min;
        float max;
    } BoundingBox1;

    // 1D linear spline
    typedef struct SplineSegmentLinear1 {
        float startPos;
        float endPos;
    } SplineSegmentLinear1;

    // 1D b-spline
    typedef struct SplineSegmentBasis1 {
        float p1;
        float p2;
        float p3;
        float p4;
    } SplineSegmentBasis1;

    // 1D Catmull-Rom spline
    typedef struct SplineSegmentCatmullRom1 {
        float p1;
        float p2;
        float p3;
        float p4;
    } SplineSegmentCatmullRom1;

    // 1D quadratic (degree 2) Bezier spline
    typedef struct SplineSegmentBezierQuad1 {
        float startPos;
        float controlPos;
        float endPos;
    } SplineSegmentBezierQuad1;

    // 1D cubic (degree 3) Bezier spline
    typedef struct SplineSegmentBezierCubic1 {
        float startPos;
        float startControlPos;
        float endControlPos;
        float endPos;
    } SplineSegmentBezierCubic1;
#endif // RSPLINES_1D

#if defined(RSPLINES_2D)
    #ifndef RL_VECTOR2_TYPE
    #define RL_VECTOR2_TYPE
    // Vector2, 2 components
    typedef struct Vector2 {
        float x;
        float y;
    } Vector2;
    #endif // RL_VECTOR2_TYPE

    // 2D bounds (rectangle)
    typedef struct BoundingBox2 {
        Vector2 min;
        Vector2 max;
    } BoundingBox2;

    // 2D linear spline
    typedef struct SplineSegmentLinear2 {
        Vector2 startPos;
        Vector2 endPos;
    } SplineSegmentLinear2;

    // 2D b-spline
    typedef struct SplineSegmentBasis2 {
        Vector2 p1;
        Vector2 p2;
        Vector2 p3;
        Vector2 p4;
    } SplineSegmentBasis2;

    // 2D Catmull-Rom spline
    typedef struct SplineSegmentCatmullRom2 {
        Vector2 p1;
        Vector2 p2;
        Vector2 p3;
        Vector2 p4;
    } SplineSegmentCatmullRom2;

    // 2D quadratic (degree 2) Bezier spline
    typedef struct SplineSegmentBezierQuad2 {
        Vector2 startPos;
        Vector2 controlPos;
        Vector2 endPos;
    } SplineSegmentBezierQuad2;

    // 2D cubic (degree 3) Bezier spline
    typedef struct SplineSegmentBezierCubic2 {
        Vector2 startPos;
        Vector2 startControlPos;
        Vector2 endControlPos;
        Vector2 endPos;
    } SplineSegmentBezierCubic2;
#endif // RSPLINES_2D

#if defined(RSPLINES_3D)
    #ifndef RL_VECTOR3_TYPE
    #define RL_VECTOR3_TYPE
    // Vector3, 3 components
    typedef struct Vector3 {
        float x;
        float y;
        float z;
    } Vector3;
    #endif // RL_VECTOR3_TYPE

    // 3D bounds (box)
    typedef struct BoundingBox3 {
        Vector3 min;
        Vector3 max;
    } BoundingBox3;

    // 3D linear spline
    typedef struct SplineSegmentLinear3 {
        Vector3 startPos;
        Vector3 endPos;
    } SplineSegmentLinear3;

    // 3D b-spline
    typedef struct SplineSegmentBasis3 {
        Vector3 p1;
        Vector3 p2;
        Vector3 p3;
        Vector3 p4;
    } SplineSegmentBasis3;

    // 3D Catmull-Rom spline
    typedef struct SplineSegmentCatmullRom3 {
        Vector3 p1;
        Vector3 p2;
        Vector3 p3;
        Vector3 p4;
    } SplineSegmentCatmullRom3;

    // 3D quadratic (degree 2) Bezier spline
    typedef struct SplineSegmentBezierQuad3 {
        Vector3 startPos;
        Vector3 controlPos;
        Vector3 endPos;
    } SplineSegmentBezierQuad3;

    // 3D cubic (degree 3) Bezier spline
    typedef struct SplineSegmentBezierCubic3 {
        Vector3 startPos;
        Vector3 startControlPos;
        Vector3 endControlPos;
        Vector3 endPos;
    } SplineSegmentBezierCubic3;
#endif // RSPLINES_3D

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

#if defined(RSPLINES_1D)
//------------------------------
// 1D Splines
//------------------------------

// Spline point evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI float SplineLinear1Point(const float *points, int pointCount, float t);                                  // Get (evaluate) spline point: Linear 1D
RSPLAPI float SplineBasis1Point(const float *points, int pointCount, float t);                                   // Get (evaluate) spline point: B-Spline 1D
RSPLAPI float SplineCatmullRom1Point(const float *points, int pointCount, float t);                              // Get (evaluate) spline point: Catmull-Rom 1D
RSPLAPI float SplineBezierQuad1Point(const float *points, int pointCount, float t);                              // Get (evaluate) spline point: Quadratic Bezier 1D
RSPLAPI float SplineBezierCubic1Point(const float *points, int pointCount, float t);                             // Get (evaluate) spline point: Cubic Bezier 1D

// Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI float SplineSegmentLinear1Point(SplineSegmentLinear1 spline, float t);                                   // Get (evaluate) spline point: Linear 1D
RSPLAPI float SplineSegmentBasis1Point(SplineSegmentBasis1 spline, float t);                                     // Get (evaluate) spline point: B-Spline 1D
RSPLAPI float SplineSegmentCatmullRom1Point(SplineSegmentCatmullRom1 spline, float t);                           // Get (evaluate) spline point: Catmull-Rom 1D
RSPLAPI float SplineSegmentBezierQuad1Point(SplineSegmentBezierQuad1 spline, float t);                           // Get (evaluate) spline point: Quadratic Bezier 1D
RSPLAPI float SplineSegmentBezierCubic1Point(SplineSegmentBezierCubic1 spline, float t);                         // Get (evaluate) spline point: Cubic Bezier 1D

// Spline inverse point functions, for evenly-spaced points on the curve
RSPLAPI SplineSegmentBezierQuad1 SplineSegmentBezierQuad1FromPoints(float startPos, float midPos, float endPos); // Get (evaluate) spline control point: Quadratic Bezier 1D
RSPLAPI SplineSegmentBezierCubic1 SplineSegmentBezierCubic1FromPoints(float startPos, float oneThirdsPos, float twoThirdsPos, float endPos); // Get (evaluate) spline control points: Cubic Bezier 1D

// Spline segment slope evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI float SplineSegmentLinear1Velocity(SplineSegmentLinear1 spline);                                         // Get (evaluate) spline velocity: Linear 1D
RSPLAPI float SplineSegmentBezierQuad1Velocity(SplineSegmentBezierQuad1 spline, float t);                        // Get (evaluate) spline velocity: Quadratic Bezier 1D
RSPLAPI float SplineSegmentBezierCubic1Velocity(SplineSegmentBezierCubic1 spline, float t);                      // Get (evaluate) spline velocity: Cubic Bezier 1D
RSPLAPI float SplineSegmentBezierQuad1Acceleration(SplineSegmentBezierQuad1 spline);                             // Get (evaluate) spline acceleration: Quadratic Bezier 1D
RSPLAPI float SplineSegmentBezierCubic1Acceleration(SplineSegmentBezierCubic1 spline, float t);                  // Get (evaluate) spline acceleration: Cubic Bezier 1D
RSPLAPI float SplineSegmentBezierCubic1Jolt(SplineSegmentBezierCubic1 spline);                                   // Get (evaluate) spline jolt: Cubic Bezier 1D

// Spline segment bounds evaluation functions
RSPLAPI BoundingBox1 SplineSegmentLinear1Bounds(SplineSegmentLinear1 spline);                                    // Get (evaluate) spline bounds range: Linear 1D
RSPLAPI BoundingBox1 SplineSegmentBezierQuad1Bounds(SplineSegmentBezierQuad1 spline);                            // Get (evaluate) spline bounds range: Quadratic Bezier 1D
RSPLAPI BoundingBox1 SplineSegmentBezierCubic1Bounds(SplineSegmentBezierCubic1 spline);                          // Get (evaluate) spline bounds range: Cubic Bezier 1D

// Spline segment length evaluation functions
RSPLAPI float SplineSegmentLinear1LengthSqr(SplineSegmentLinear1 spline);                                        // Get (evaluate) squared length of spline: Linear 1D
RSPLAPI float SplineSegmentLinear1Length(SplineSegmentLinear1 spline);                                           // Get (evaluate) length of spline: Linear 1D
RSPLAPI float SplineSegmentLinear1SubLengthSqr(SplineSegmentLinear1 spline, float tStart, float tEnd);           // Get (evaluate) squared length of subspline: Linear 1D
RSPLAPI float SplineSegmentLinear1SubLength(SplineSegmentLinear1 spline, float tStart, float tEnd);              // Get (evaluate) length of subspline: Linear 1D

RSPLAPI float SplineSegmentLinear1NearestT(SplineSegmentLinear1 spline, float point);                            // Get (evaluate) nearest t value to point: Linear 1D

#endif // RSPLINES_1D

#if defined(RSPLINES_2D)
//------------------------------
// 2D Splines
//------------------------------

// Spline point evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI Vector2 SplineLinear2Point(const Vector2 *points, int pointCount, float t);                              // Get (evaluate) spline point: Linear 2D
RSPLAPI Vector2 SplineBasis2Point(const Vector2 *points, int pointCount, float t);                               // Get (evaluate) spline point: B-Spline 2D
RSPLAPI Vector2 SplineCatmullRom2Point(const Vector2 *points, int pointCount, float t);                          // Get (evaluate) spline point: Catmull-Rom 2D
RSPLAPI Vector2 SplineBezierQuad2Point(const Vector2 *points, int pointCount, float t);                          // Get (evaluate) spline point: Quadratic Bezier 2D
RSPLAPI Vector2 SplineBezierCubic2Point(const Vector2 *points, int pointCount, float t);                         // Get (evaluate) spline point: Cubic Bezier 2D

// Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI Vector2 SplineSegmentLinear2Point(SplineSegmentLinear2 spline, float t);                                 // Get (evaluate) spline point: Linear 2D
RSPLAPI Vector2 SplineSegmentBasis2Point(SplineSegmentBasis2 spline, float t);                                   // Get (evaluate) spline point: B-Spline 2D
RSPLAPI Vector2 SplineSegmentCatmullRom2Point(SplineSegmentCatmullRom2 spline, float t);                         // Get (evaluate) spline point: Catmull-Rom 2D
RSPLAPI Vector2 SplineSegmentBezierQuad2Point(SplineSegmentBezierQuad2 spline, float t);                         // Get (evaluate) spline point: Quadratic Bezier 2D
RSPLAPI Vector2 SplineSegmentBezierCubic2Point(SplineSegmentBezierCubic2 spline, float t);                       // Get (evaluate) spline point: Cubic Bezier 2D

// Spline inverse point functions, for evenly-spaced points on the curve
RSPLAPI SplineSegmentBezierQuad2 SplineSegmentBezierQuad2FromPoints(Vector2 startPos, Vector2 midPos, Vector2 endPos); // Get (evaluate) spline control point: Quadratic Bezier 2D
RSPLAPI SplineSegmentBezierCubic2 SplineSegmentBezierCubic2FromPoints(Vector2 startPos, Vector2 oneThirdsPos, Vector2 twoThirdsPos, Vector2 endPos); // Get (evaluate) spline control points: Cubic Bezier 2D

// Spline segment slope evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI Vector2 SplineSegmentLinear2Velocity(SplineSegmentLinear2 spline);                                       // Get (evaluate) spline velocity: Linear 2D
RSPLAPI Vector2 SplineSegmentBezierQuad2Velocity(SplineSegmentBezierQuad2 spline, float t);                      // Get (evaluate) spline velocity: Quadratic Bezier 2D
RSPLAPI Vector2 SplineSegmentBezierCubic2Velocity(SplineSegmentBezierCubic2 spline, float t);                    // Get (evaluate) spline velocity: Cubic Bezier 2D
RSPLAPI Vector2 SplineSegmentLinear2Tangent(SplineSegmentLinear2 spline);                                        // Get (evaluate) spline tangent: Linear 2D
RSPLAPI Vector2 SplineSegmentLinear2Normal(SplineSegmentLinear2 spline);                                         // Get (evaluate) spline normal: Linear 2D
RSPLAPI Vector2 SplineSegmentBezierQuad2Tangent(SplineSegmentBezierQuad2 spline, float t);                       // Get (evaluate) spline tangent: Quadratic Bezier 2D
RSPLAPI Vector2 SplineSegmentBezierQuad2Normal(SplineSegmentBezierQuad2 spline, float t);                        // Get (evaluate) spline normal: Quadratic Bezier 2D
RSPLAPI Vector2 SplineSegmentBezierCubic2Tangent(SplineSegmentBezierCubic2 spline, float t);                     // Get (evaluate) spline tangent: Cubic Bezier 2D
RSPLAPI Vector2 SplineSegmentBezierCubic2Normal(SplineSegmentBezierCubic2 spline, float t);                      // Get (evaluate) spline normal: Cubic Bezier 2D
RSPLAPI Vector2 SplineSegmentBezierQuad2Acceleration(SplineSegmentBezierQuad2 spline);                           // Get (evaluate) spline acceleration: Quadratic Bezier 2D
RSPLAPI Vector2 SplineSegmentBezierCubic2Acceleration(SplineSegmentBezierCubic2 spline, float t);                // Get (evaluate) spline acceleration: Cubic Bezier 2D
RSPLAPI Vector2 SplineSegmentBezierCubic2Jolt(SplineSegmentBezierCubic2 spline);                                 // Get (evaluate) spline jolt: Cubic Bezier 2D

// Spline segment bounds evaluation functions
RSPLAPI BoundingBox2 SplineSegmentLinear2Bounds(SplineSegmentLinear2 spline);                                    // Get (evaluate) spline bounds rectangle: Linear 2D
RSPLAPI BoundingBox2 SplineSegmentBezierQuad2Bounds(SplineSegmentBezierQuad2 spline);                            // Get (evaluate) spline bounds rectangle: Quadratic Bezier 2D
RSPLAPI BoundingBox2 SplineSegmentBezierCubic2Bounds(SplineSegmentBezierCubic2 spline);                          // Get (evaluate) spline bounds rectangle: Cubic Bezier 2D

// Spline segment length evaluation functions
RSPLAPI float SplineSegmentLinear2LengthSqr(SplineSegmentLinear2 spline);                                        // Get (evaluate) squared length of spline: Linear 2D
RSPLAPI float SplineSegmentLinear2Length(SplineSegmentLinear2 spline);                                           // Get (evaluate) length of spline: Linear 2D
RSPLAPI float SplineSegmentLinear2SubLengthSqr(SplineSegmentLinear2 spline, float tStart, float tEnd);           // Get (evaluate) squared length of subspline: Linear 2D
RSPLAPI float SplineSegmentLinear2SubLength(SplineSegmentLinear2 spline, float tStart, float tEnd);              // Get (evaluate) length of subspline: Linear 2D

RSPLAPI float SplineSegmentBezierCubic2Curvature(SplineSegmentBezierCubic2 spline, float t);                     // Get (evaluate) spline curvature: Cubic Bezier 2D
RSPLAPI float SplineSegmentLinear2NearestT(SplineSegmentLinear2 spline, Vector2 point);                          // Get (evaluate) nearest t value to point: Linear 2D

#endif // RSPLINES_2D

#if defined(RSPLINES_3D)
//------------------------------
// 3D Splines
//------------------------------

// Spline point evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI Vector3 SplineLinear3Point(const Vector3 *points, int pointCount, float t);                              // Get (evaluate) spline point: Linear 3D
RSPLAPI Vector3 SplineBasis3Point(const Vector3 *points, int pointCount, float t);                               // Get (evaluate) spline point: B-Spline 3D
RSPLAPI Vector3 SplineCatmullRom3Point(const Vector3 *points, int pointCount, float t);                          // Get (evaluate) spline point: Catmull-Rom 3D
RSPLAPI Vector3 SplineBezierQuad3Point(const Vector3 *points, int pointCount, float t);                          // Get (evaluate) spline point: Quadratic Bezier 3D
RSPLAPI Vector3 SplineBezierCubic3Point(const Vector3 *points, int pointCount, float t);                         // Get (evaluate) spline point: Cubic Bezier 3D

// Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI Vector3 SplineSegmentLinear3Point(SplineSegmentLinear3 spline, float t);                                 // Get (evaluate) spline point: Linear 3D
RSPLAPI Vector3 SplineSegmentBasis3Point(SplineSegmentBasis3 spline, float t);                                   // Get (evaluate) spline point: B-Spline 3D
RSPLAPI Vector3 SplineSegmentCatmullRom3Point(SplineSegmentCatmullRom3 spline, float t);                         // Get (evaluate) spline point: Catmull-Rom 3D
RSPLAPI Vector3 SplineSegmentBezierQuad3Point(SplineSegmentBezierQuad3 spline, float t);                         // Get (evaluate) spline point: Quadratic Bezier 3D
RSPLAPI Vector3 SplineSegmentBezierCubic3Point(SplineSegmentBezierCubic3 spline, float t);                       // Get (evaluate) spline point: Cubic Bezier 3D

// Spline inverse point functions, for evenly-spaced points on the curve
RSPLAPI SplineSegmentBezierQuad3 SplineSegmentBezierQuad3FromPoints(Vector3 startPos, Vector3 midPos, Vector3 endPos); // Get (evaluate) spline control point: Quadratic Bezier 3D
RSPLAPI SplineSegmentBezierCubic3 SplineSegmentBezierCubic3FromPoints(Vector3 startPos, Vector3 oneThirdsPos, Vector3 twoThirdsPos, Vector3 endPos); // Get (evaluate) spline control points: Cubic Bezier 3D

// Spline segment slope evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI Vector3 SplineSegmentLinear3Velocity(SplineSegmentLinear3 spline);                                       // Get (evaluate) spline velocity: Linear 3D
RSPLAPI Vector3 SplineSegmentLinear3Tangent(SplineSegmentLinear3 spline);                                        // Get (evaluate) spline tangent: Linear 3D
RSPLAPI Vector3 SplineSegmentBezierQuad3Velocity(SplineSegmentBezierQuad3 spline, float t);                      // Get (evaluate) spline velocity: Quadratic Bezier 3D
RSPLAPI Vector3 SplineSegmentBezierQuad3Tangent(SplineSegmentBezierQuad3 spline, float t);                       // Get (evaluate) spline tangent: Quadratic Bezier 3D
RSPLAPI Vector3 SplineSegmentBezierCubic3Velocity(SplineSegmentBezierCubic3 spline, float t);                    // Get (evaluate) spline velocity: Cubic Bezier 3D
RSPLAPI Vector3 SplineSegmentBezierCubic3Tangent(SplineSegmentBezierCubic3 spline, float t);                     // Get (evaluate) spline tangent: Cubic Bezier 3D
RSPLAPI Vector3 SplineSegmentBezierQuad3Acceleration(SplineSegmentBezierQuad3 spline);                           // Get (evaluate) spline acceleration: Quadratic Bezier 3D
RSPLAPI Vector3 SplineSegmentBezierCubic3Acceleration(SplineSegmentBezierCubic3 spline, float t);                // Get (evaluate) spline acceleration: Cubic Bezier 3D
RSPLAPI Vector3 SplineSegmentBezierCubic3Jolt(SplineSegmentBezierCubic3 spline);                                 // Get (evaluate) spline jolt: Cubic Bezier 3D

// Spline segment bounds evaluation functions
RSPLAPI BoundingBox3 SplineSegmentLinear3Bounds(SplineSegmentLinear3 spline);                                    // Get (evaluate) spline bounding box: Linear 3D
RSPLAPI BoundingBox3 SplineSegmentBezierQuad3Bounds(SplineSegmentBezierQuad3 spline);                            // Get (evaluate) spline bounding box: Quadratic Bezier 3D
RSPLAPI BoundingBox3 SplineSegmentBezierCubic3Bounds(SplineSegmentBezierCubic3 spline);                          // Get (evaluate) spline bounding box: Cubic Bezier 3D

// Spline segment length evaluation functions
RSPLAPI float SplineSegmentLinear3LengthSqr(SplineSegmentLinear3 spline);                                        // Get (evaluate) squared length of spline: Linear 3D
RSPLAPI float SplineSegmentLinear3Length(SplineSegmentLinear3 spline);                                           // Get (evaluate) length of spline: Linear 3D
RSPLAPI float SplineSegmentLinear3SubLengthSqr(SplineSegmentLinear3 spline, float tStart, float tEnd);           // Get (evaluate) squared length of subspline: Linear 3D
RSPLAPI float SplineSegmentLinear3SubLength(SplineSegmentLinear3 spline, float tStart, float tEnd);              // Get (evaluate) length of subspline: Linear 3D

RSPLAPI float SplineSegmentLinear3NearestT(SplineSegmentLinear3 spline, Vector3 point);                          // Get (evaluate) nearest t value to point: Linear 3D

#endif // RSPLINES_3D

#if defined(__cplusplus)
}            // Prevents name mangling of functions
#endif

#endif // RSPLINES_H

/***********************************************************************************
*
*   RSPLINES IMPLEMENTATION
*
************************************************************************************/

#if defined(RSPLINES_IMPLEMENTATION)

#include <math.h>               // Required for: powf(), sqrtf()

#if defined(RSPLINES_1D)

// Get (evaluate) spline point: Linear 1D
// NOTE: Minimum 2 points
float SplineLinear1Point(const float *points, int pointCount, float t)
{
    float point = 0.0f;

    if (pointCount >= 2)
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 2)) tInt = pointCount - 2;
        float tFrac = t - tInt;

        SplineSegmentLinear1 segment = { 0 };
        segment.startPos = points[tInt];
        segment.endPos = points[tInt + 1];

        point = SplineSegmentLinear1Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: B-Spline 1D
// NOTE: Requires 3n+1 points; minimum 4
float SplineBasis1Point(const float *points, int pointCount, float t)
{
    float point = 0.0f;

    if ((pointCount >= 4) && ((pointCount%3) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 4)) tInt = pointCount - 4;
        float tFrac = t - tInt;

        SplineSegmentBasis1 segment = { 0 };
        segment.p1 = points[3*tInt];
        segment.p2 = points[3*tInt + 1];
        segment.p3 = points[3*tInt + 2];
        segment.p4 = points[3*tInt + 3];

        point = SplineSegmentBasis1Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: Catmull-Rom 1D
// NOTE: Requires 3n+1 points; minimum 4
float SplineCatmullRom1Point(const float *points, int pointCount, float t)
{
    float point = 0.0f;

    if ((pointCount >= 4) && ((pointCount%3) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 4)) tInt = pointCount - 4;
        float tFrac = t - tInt;

        SplineSegmentCatmullRom1 segment = { 0 };
        segment.p1 = points[3*tInt];
        segment.p2 = points[3*tInt + 1];
        segment.p3 = points[3*tInt + 2];
        segment.p4 = points[3*tInt + 3];

        point = SplineSegmentCatmullRom1Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: Quadratic Bezier 1D
// NOTE: Requires 2n+1 points; minimum 3
float SplineBezierQuad1Point(const float *points, int pointCount, float t)
{
    float point = 0.0f;

    if ((pointCount >= 3) && ((pointCount%2) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 3)) tInt = pointCount - 3;
        float tFrac = t - tInt;

        SplineSegmentBezierQuad1 segment = { 0 };
        segment.startPos = points[2*tInt];
        segment.controlPos = points[2*tInt + 1];
        segment.endPos = points[2*tInt + 2];

        point = SplineSegmentBezierQuad1Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: Cubic Bezier 1D
// NOTE: Requires 3n+1 points; minimum 4
float SplineBezierCubic1Point(const float *points, int pointCount, float t)
{
    float point = 0.0f;

    if ((pointCount >= 4) && ((pointCount%3) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 4)) tInt = pointCount - 4;
        float tFrac = t - tInt;

        SplineSegmentBezierCubic1 segment = { 0 };
        segment.startPos = points[3*tInt];
        segment.startControlPos = points[3*tInt + 1];
        segment.endControlPos = points[3*tInt + 1];
        segment.endPos = points[3*tInt + 2];

        point = SplineSegmentBezierCubic1Point(segment, tFrac);
    }

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Linear
float SplineSegmentLinear1Point(SplineSegmentLinear1 spline, float t)
{
    float point = 0.0f;

    point = spline.startPos*(1.0f - t) + spline.endPos*t;

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], B-Spline
float SplineSegmentBasis1Point(SplineSegmentBasis1 spline, float t)
{
    float point = 0.0f;

    float a0 = (-spline.p1 + 3*spline.p2 - 3*spline.p3 + spline.p4)/6.0f;
    float a1 = (3*spline.p1 - 6*spline.p2 + 3*spline.p3)/6.0f;
    float a2 = (-3*spline.p1 + 3*spline.p3)/6.0f;
    float a3 = (spline.p1 + 4*spline.p2 + spline.p3)/6.0f;

    point = a3 + t*(a2 + t*(a1 + t*a0));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Catmull-Rom
float SplineSegmentCatmullRom1Point(SplineSegmentCatmullRom1 spline, float t)
{
    float point = 0.0f;

    float q0 = (-1*t*t*t) + (2*t*t) + (-1*t);
    float q1 = (3*t*t*t) + (-5*t*t) + 2;
    float q2 = (-3*t*t*t) + (4*t*t) + t;
    float q3 = t*t*t - t*t;

    point = 0.5f*((spline.p1*q0) + (spline.p2*q1) + (spline.p3*q2) + (spline.p4*q3));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Quadratic Bezier
float SplineSegmentBezierQuad1Point(SplineSegmentBezierQuad1 spline, float t)
{
    float point = 0.0f;

    float a = powf(1.0f - t, 2);
    float b = 2.0f*(1.0f - t)*t;
    float c = powf(t, 2);

    point = a*spline.startPos + b*spline.controlPos + c*spline.endPos;

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Cubic Bezier
float SplineSegmentBezierCubic1Point(SplineSegmentBezierCubic1 spline, float t)
{
    float point = 0.0f;

    float a = powf(1.0f - t, 3);
    float b = 3.0f*powf(1.0f - t, 2)*t;
    float c = 3.0f*(1.0f - t)*powf(t, 2);
    float d = powf(t, 3);

    point = a*spline.startPos + b*spline.startControlPos + c*spline.endControlPos + d*spline.endPos;

    return point;
}

// Get spline control point given evenly-spaced points on that curve, Quadratic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
SplineSegmentBezierQuad1 SplineSegmentBezierQuad1FromPoints(float startPos, float midPos, float endPos)
{
    SplineSegmentBezierQuad1 spline = { 0 };

    spline.startPos = startPos;
    spline.endPos = endPos;
    spline.controlPos = 2.0f*midPos - 0.5f*(startPos + endPos);

    return spline;
}

// Get spline control points given evenly-spaced points on that curve, Cubic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
SplineSegmentBezierCubic1 SplineSegmentBezierCubic1FromPoints(float startPos, float oneThirdsPos, float twoThirdsPos, float endPos)
{
    SplineSegmentBezierCubic1 spline = { 0 };

    float a = -5.0f/6.0f;
    float b = 3.0f;
    float c = -3.0f/2.0f;
    float d = 1.0f/3.0f;

    spline.startPos = startPos;
    spline.endPos = endPos;
    spline.startControlPos = a*startPos + b*oneThirdsPos + c*twoThirdsPos + d*endPos;
    spline.endControlPos = a*endPos + b*twoThirdsPos + c*oneThirdsPos + d*startPos;

    return spline;
}

// Get spline direction and speed, Linear Bezier
//
// Normalize to get the "forward" direction of the curve
float SplineSegmentLinear1Velocity(SplineSegmentLinear1 spline)
{
    float velocity = 0.0f;

    velocity = spline.endPos - spline.startPos;

    return velocity;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Quadratic Bezier
//
// Normalize to get the "forward" direction of the curve at t
float SplineSegmentBezierQuad1Velocity(SplineSegmentBezierQuad1 spline, float t)
{
    float velocity = 0.0f;

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    velocity = a*(spline.controlPos - spline.startPos) + b*(spline.endPos - spline.controlPos);

    return velocity;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Cubic Bezier
//
// Normalize to get the "forward" direction of the curve at t
float SplineSegmentBezierCubic1Velocity(SplineSegmentBezierCubic1 spline, float t)
{
    float velocity = 0.0f;

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    velocity = a*(spline.startControlPos - spline.startPos) + b*(spline.endControlPos - spline.startControlPos) + c*(spline.endPos - spline.endControlPos);

    return velocity;
}

// Get spline rate of change, Quadratic Bezier
float SplineSegmentBezierQuad1Acceleration(SplineSegmentBezierQuad1 spline)
{
    float acceleration = 0.0f;

    acceleration = 2.0f*(spline.endPos - 2.0f*spline.controlPos - spline.startPos);

    return acceleration;
}

// Get spline rate of change for a given t [0.0f .. 1.0f], Cubic Bezier
float SplineSegmentBezierCubic1Acceleration(SplineSegmentBezierCubic1 spline, float t)
{
    float acceleration = 0.0f;

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    acceleration = a*(spline.endControlPos - 2.0f*spline.startControlPos + spline.startPos) + b*(spline.endPos - 2.0f*spline.endControlPos + spline.startControlPos);

    return acceleration;
}

// Get spline rate of acceleration, Cubic Bezier
float SplineSegmentBezierCubic1Jolt(SplineSegmentBezierCubic1 spline)
{
    float jolt = 0.0f;

    jolt = 6.0f*(spline.endPos + 3.0f*(spline.startControlPos - spline.endControlPos) - spline.startPos);

    return jolt;
}

// Compute spline curve bounding rectangle, Linear
BoundingBox1 SplineSegmentLinear1Bounds(SplineSegmentLinear1 spline)
{
    float min;
    float max;

    if (spline.startPos < spline.endPos)
    {
        min = spline.startPos;
        max = spline.endPos;
    }
    else
    {
        min = spline.endPos;
        max = spline.startPos;
    }

    // straight line will never escape bounds

    BoundingBox1 bounds = { min, max };

    return bounds;
}

// Compute spline curve bounding rectangle, Quadratic Bezier
BoundingBox1 SplineSegmentBezierQuad1Bounds(SplineSegmentBezierQuad1 spline)
{
    float min;
    float max;

    if (spline.startPos < spline.endPos)
    {
        min = spline.startPos;
        max = spline.endPos;
    }
    else
    {
        min = spline.endPos;
        max = spline.startPos;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float a = spline.startPos - 2.0f*spline.controlPos + spline.endPos;
    float b = 2.0f*(spline.controlPos - spline.startPos);
    float c = spline.startPos;

    if (a != 0)
    {
        float bSqrMinus4ac = b*b - 4.0f*a*c;
        float t[2] = { 0 };
        int tCount = 0;
        if (bSqrMinus4ac > 0)
        {
            float denominator = 1.0f/(2.0f*a);

            float term0 = -b*denominator;
            float term1 = sqrtf(bSqrMinus4ac)*denominator;

            t[0] = term0 + term1;
            if (0.0f < t[0] && t[0] < 1.0f) ++tCount;

            t[tCount] = term0 - term1;
            if (0.0f < t[tCount] && t[tCount] < 1.0f) ++tCount;
        }
        else if (bSqrMinus4ac == 0)
        {
            t[0] = -b/(2.0f*a);
            if (0.0f < t[0] && t[0] < 1.0f) ++tCount;
        }
        // ignore imaginary solution

        for (int i = 0; i < tCount; ++i)
        {
            float point = SplineSegmentBezierQuad1Point(spline, t[i]);

            if (point < min) min = point;
            if (point > max) max = point;
        }
    }

    BoundingBox1 bounds = { min, max };

    return bounds;
}

// Compute spline curve bounding rectangle, Cubic Bezier
BoundingBox1 SplineSegmentBezierCubic1Bounds(SplineSegmentBezierCubic1 spline)
{
    float min;
    float max;

    if (spline.startPos < spline.endPos)
    {
        min = spline.startPos;
        max = spline.endPos;
    }
    else
    {
        min = spline.endPos;
        max = spline.startPos;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float a = -3.0f*spline.startPos + 9.0f*spline.startControlPos - 9.0f*spline.endControlPos + 3.0f*spline.endPos;
    float b = 6.0f*spline.startPos - 12.0f*spline.startControlPos + 6.0f*spline.endControlPos;
    float c = -3.0f*spline.startPos + 3.0f*spline.startControlPos;

    if (a != 0)
    {
        float bSqrMinus4ac = b*b - 4.0f*a*c;
        float t[2] = { 0 };
        int tCount = 0;
        if (bSqrMinus4ac > 0)
        {
            float denominator = 1.0f/(2.0f*a);

            float term0 = -b*denominator;
            float term1 = sqrtf(bSqrMinus4ac)*denominator;

            t[0] = term0 + term1;
            if (0.0f < t[0] && t[0] < 1.0f) ++tCount;

            t[tCount] = term0 - term1;
            if (0.0f < t[tCount] && t[tCount] < 1.0f) ++tCount;
        }
        else if (bSqrMinus4ac == 0)
        {
            t[0] = -b/(2.0f*a);
            if (0.0f < t[0] && t[0] < 1.0f) ++tCount;
        }
        // ignore imaginary solution

        for (int i = 0; i < tCount; ++i)
        {
            float point = SplineSegmentBezierCubic1Point(spline, t[i]);

            if (point < min) min = point;
            if (point > max) max = point;
        }
    }
    // straight line will never escape bounds

    BoundingBox1 bounds = { min, max };

    return bounds;
}

// Get (evaluate) square of length of spline along a t-value range: Linear 1D
float SplineSegmentLinear1LengthSqr(SplineSegmentLinear1 spline)
{
    float lengthSqr = 0.0f;

    lengthSqr = (spline.endPos - spline.startPos)*(spline.endPos - spline.startPos);

    return lengthSqr;
}

// Get (evaluate) square of length of spline along a t-value range: Linear 1D
float SplineSegmentLinear1Length(SplineSegmentLinear1 spline)
{
    float length = 0.0f;

    float lengthSqr = (spline.endPos - spline.startPos)*(spline.endPos - spline.startPos);

    length = sqrtf(lengthSqr);

    return length;
}

// Get (evaluate) square of length of subspline: Linear 1D
float SplineSegmentLinear1SubLengthSqr(SplineSegmentLinear1 spline, float tStart, float tEnd)
{
    float lengthSqr = 0.0f;

    float dx = (tStart - tEnd)*spline.startPos + (tEnd - tStart)*spline.endPos;

    lengthSqr = dx*dx;

    return lengthSqr;
}

// Get (evaluate) length of subspline: Linear 1D
float SplineSegmentLinear1SubLength(SplineSegmentLinear1 spline, float tStart, float tEnd)
{
    float length = 0.0f;

    float dx = spline.startPos*(tStart - tEnd) + spline.endPos*(tEnd - tStart);

    length = sqrtf(dx*dx);

    return length;
}

// Get value of t (unbounded) for the point on the line closest to a given position
// NOTE 1: If the return is less than 0.0f or greater than 1.0f, the nearest point may be in a different segment
// NOTE 2: Return can be clamped [0.0f .. 1.0f] to snap the point to the start/end of the spline
float SplineSegmentLinear1NearestT(SplineSegmentLinear1 spline, float point)
{
    float t = 0.0f;

    t = (point - spline.startPos)/(spline.endPos - spline.startPos);

    return t;
}

#endif // RSPLINES_1D

#if defined(RSPLINES_2D)

// Get (evaluate) spline point: Linear 2D
// NOTE: Minimum 2 points
Vector2 SplineLinear2Point(const Vector2 *points, int pointCount, float t)
{
    Vector2 point = { 0 };

    if (pointCount >= 2)
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 2)) tInt = pointCount - 2;
        float tFrac = t - tInt;

        SplineSegmentLinear2 segment = { 0 };
        segment.startPos = points[tInt];
        segment.endPos = points[tInt + 1];

        point = SplineSegmentLinear2Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: B-Spline 2D
// NOTE: Requires 3n+1 points; minimum 4
Vector2 SplineBasis2Point(const Vector2 *points, int pointCount, float t)
{
    Vector2 point = { 0 };

    if ((pointCount >= 4) && ((pointCount%3) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 4)) tInt = pointCount - 4;
        float tFrac = t - tInt;

        SplineSegmentBasis2 segment = { 0 };
        segment.p1 = points[3*tInt];
        segment.p2 = points[3*tInt + 1];
        segment.p3 = points[3*tInt + 2];
        segment.p4 = points[3*tInt + 3];

        point = SplineSegmentBasis2Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: Catmull-Rom 2D
// NOTE: Requires 3n+1 points; minimum 4
Vector2 SplineCatmullRom2Point(const Vector2 *points, int pointCount, float t)
{
    Vector2 point = { 0 };

    if ((pointCount >= 4) && ((pointCount%3) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 4)) tInt = pointCount - 4;
        float tFrac = t - tInt;

        SplineSegmentCatmullRom2 segment = { 0 };
        segment.p1 = points[3*tInt];
        segment.p2 = points[3*tInt + 1];
        segment.p3 = points[3*tInt + 2];
        segment.p4 = points[3*tInt + 3];

        point = SplineSegmentCatmullRom2Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: Quadratic Bezier 2D
// NOTE: Requires 2n+1 points; minimum 3
Vector2 SplineBezierQuad2Point(const Vector2 *points, int pointCount, float t)
{
    Vector2 point = { 0 };

    if ((pointCount >= 3) && ((pointCount%2) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 3)) tInt = pointCount - 3;
        float tFrac = t - tInt;

        SplineSegmentBezierQuad2 segment = { 0 };
        segment.startPos = points[2*tInt];
        segment.controlPos = points[2*tInt + 1];
        segment.endPos = points[2*tInt + 2];

        point = SplineSegmentBezierQuad2Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: Cubic Bezier 2D
// NOTE: Requires 3n+1 points; minimum 4
Vector2 SplineBezierCubic2Point(const Vector2 *points, int pointCount, float t)
{
    Vector2 point = { 0 };

    if ((pointCount >= 4) && ((pointCount%3) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 4)) tInt = pointCount - 4;
        float tFrac = t - tInt;

        SplineSegmentBezierCubic2 segment = { 0 };
        segment.startPos = points[3*tInt];
        segment.startControlPos = points[3*tInt + 1];
        segment.endControlPos = points[3*tInt + 1];
        segment.endPos = points[3*tInt + 2];

        point = SplineSegmentBezierCubic2Point(segment, tFrac);
    }

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Linear
Vector2 SplineSegmentLinear2Point(SplineSegmentLinear2 spline, float t)
{
    Vector2 point = { 0 };

    point.x = spline.startPos.x*(1.0f - t) + spline.endPos.x*t;
    point.y = spline.startPos.y*(1.0f - t) + spline.endPos.y*t;

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], B-Spline
Vector2 SplineSegmentBasis2Point(SplineSegmentBasis2 spline, float t)
{
    Vector2 point = { 0 };

    float a0 = (-spline.p1.x + 3*spline.p2.x - 3*spline.p3.x + spline.p4.x)/6.0f;
    float a1 = (3*spline.p1.x - 6*spline.p2.x + 3*spline.p3.x)/6.0f;
    float a2 = (-3*spline.p1.x + 3*spline.p3.x)/6.0f;
    float a3 = (spline.p1.x + 4*spline.p2.x + spline.p3.x)/6.0f;

    float b0 = (-spline.p1.y + 3*spline.p2.y - 3*spline.p3.y + spline.p4.y)/6.0f;
    float b1 = (3*spline.p1.y - 6*spline.p2.y + 3*spline.p3.y)/6.0f;
    float b2 = (-3*spline.p1.y + 3*spline.p3.y)/6.0f;
    float b3 = (spline.p1.y + 4*spline.p2.y + spline.p3.y)/6.0f;

    point.x = a3 + t*(a2 + t*(a1 + t*a0));
    point.y = b3 + t*(b2 + t*(b1 + t*b0));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Catmull-Rom
Vector2 SplineSegmentCatmullRom2Point(SplineSegmentCatmullRom2 spline, float t)
{
    Vector2 point = { 0 };

    float q0 = (-1*t*t*t) + (2*t*t) + (-1*t);
    float q1 = (3*t*t*t) + (-5*t*t) + 2;
    float q2 = (-3*t*t*t) + (4*t*t) + t;
    float q3 = t*t*t - t*t;

    point.x = 0.5f*((spline.p1.x*q0) + (spline.p2.x*q1) + (spline.p3.x*q2) + (spline.p4.x*q3));
    point.y = 0.5f*((spline.p1.y*q0) + (spline.p2.y*q1) + (spline.p3.y*q2) + (spline.p4.y*q3));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Quadratic Bezier
Vector2 SplineSegmentBezierQuad2Point(SplineSegmentBezierQuad2 spline, float t)
{
    Vector2 point = { 0 };

    float a = powf(1.0f - t, 2);
    float b = 2.0f*(1.0f - t)*t;
    float c = powf(t, 2);

    point.y = a*spline.startPos.y + b*spline.controlPos.y + c*spline.endPos.y;
    point.x = a*spline.startPos.x + b*spline.controlPos.x + c*spline.endPos.x;

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Cubic Bezier
Vector2 SplineSegmentBezierCubic2Point(SplineSegmentBezierCubic2 spline, float t)
{
    Vector2 point = { 0 };

    float a = powf(1.0f - t, 3);
    float b = 3.0f*powf(1.0f - t, 2)*t;
    float c = 3.0f*(1.0f - t)*powf(t, 2);
    float d = powf(t, 3);

    point.y = a*spline.startPos.y + b*spline.startControlPos.y + c*spline.endControlPos.y + d*spline.endPos.y;
    point.x = a*spline.startPos.x + b*spline.startControlPos.x + c*spline.endControlPos.x + d*spline.endPos.x;

    return point;
}

// Get spline control point given evenly-spaced points on that curve, Quadratic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
SplineSegmentBezierQuad2 SplineSegmentBezierQuad2FromPoints(Vector2 startPos, Vector2 midPos, Vector2 endPos)
{
    SplineSegmentBezierQuad2 spline = { 0 };

    spline.startPos = startPos;
    spline.endPos = endPos;
    spline.controlPos.y = 2.0f*midPos.y - 0.5f*(startPos.y + endPos.y);
    spline.controlPos.x = 2.0f*midPos.x - 0.5f*(startPos.x + endPos.x);

    return spline;
}

// Get spline control points given evenly-spaced points on that curve, Cubic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
SplineSegmentBezierCubic2 SplineSegmentBezierCubic2FromPoints(Vector2 startPos, Vector2 oneThirdsPos, Vector2 twoThirdsPos, Vector2 endPos)
{
    SplineSegmentBezierCubic2 spline = { 0 };

    float a = -5.0f/6.0f;
    float b = 3.0f;
    float c = -3.0f/2.0f;
    float d = 1.0f/3.0f;

    spline.startPos = startPos;
    spline.endPos = endPos;

    spline.startControlPos.x = a*startPos.x + b*oneThirdsPos.x + c*twoThirdsPos.x + d*endPos.x;
    spline.startControlPos.y = a*startPos.y + b*oneThirdsPos.y + c*twoThirdsPos.y + d*endPos.y;

    spline.endControlPos.x = a*endPos.x + b*twoThirdsPos.x + c*oneThirdsPos.x + d*startPos.x;
    spline.endControlPos.y = a*endPos.y + b*twoThirdsPos.y + c*oneThirdsPos.y + d*startPos.y;
}

// Get spline direction and speed, Linear Bezier
//
// Normalize to get the "forward" direction of the curve
Vector2 SplineSegmentLinear2Velocity(SplineSegmentLinear2 spline)
{
    Vector2 velocity = { 0 };

    velocity.x = spline.endPos.x - spline.startPos.x;
    velocity.y = spline.endPos.y - spline.startPos.y;

    return velocity;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Quadratic Bezier
//
// Normalize to get the "forward" direction of the curve at t
Vector2 SplineSegmentBezierQuad2Velocity(SplineSegmentBezierQuad2 spline, float t)
{
    Vector2 velocity = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    velocity.x = a*(spline.controlPos.x - spline.startPos.x) + b*(spline.endPos.x - spline.controlPos.x);
    velocity.y = a*(spline.controlPos.y - spline.startPos.y) + b*(spline.endPos.y - spline.controlPos.y);

    return velocity;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Cubic Bezier
//
// Normalize to get the "forward" direction of the curve at t
Vector2 SplineSegmentBezierCubic2Velocity(SplineSegmentBezierCubic2 spline, float t)
{
    Vector2 velocity = { 0 };

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    velocity.x = a*(spline.startControlPos.x - spline.startPos.x) + b*(spline.endControlPos.x - spline.startControlPos.x) + c*(spline.endPos.x - spline.endControlPos.x);
    velocity.y = a*(spline.startControlPos.y - spline.startPos.y) + b*(spline.endControlPos.y - spline.startControlPos.y) + c*(spline.endPos.y - spline.endControlPos.y);

    return velocity;
}

// Get (evaluate) spline tangent: Linear 2D
Vector2 SplineSegmentLinear2Tangent(SplineSegmentLinear2 spline)
{
    Vector2 tangent = { 0 };

    tangent.x = spline.endPos.x - spline.startPos.x;
    tangent.y = spline.endPos.y - spline.startPos.y;

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    return tangent;
}

// Get (evaluate) spline normal: Linear 2D
Vector2 SplineSegmentLinear2Normal(SplineSegmentLinear2 spline)
{
    Vector2 normal = { 0 };
    Vector2 tangent = { 0 };

    tangent.x = spline.endPos.x - spline.startPos.x;
    tangent.y = spline.endPos.y - spline.startPos.y;

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    normal.x = tangent.y;
    normal.y = -tangent.x;

    return normal;
}

// Get (evaluate) spline tangent: Quadratic Bezier 2D
Vector2 SplineSegmentBezierQuad2Tangent(SplineSegmentBezierQuad2 spline, float t)
{
    Vector2 tangent = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    tangent.x = a*(spline.controlPos.x - spline.startPos.x) + b*(spline.endPos.x - spline.controlPos.x);
    tangent.y = a*(spline.controlPos.y - spline.startPos.y) + b*(spline.endPos.y - spline.controlPos.y);

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    return tangent;
}

// Get (evaluate) spline normal: Quadratic Bezier 2D
Vector2 SplineSegmentBezierQuad2Normal(SplineSegmentBezierQuad2 spline, float t)
{
    Vector2 normal = { 0 };
    Vector2 tangent = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    tangent.x = a*(spline.controlPos.x - spline.startPos.x) + b*(spline.endPos.x - spline.controlPos.x);
    tangent.y = a*(spline.controlPos.y - spline.startPos.y) + b*(spline.endPos.y - spline.controlPos.y);

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    normal.x = tangent.y;
    normal.y = -tangent.x;

    return normal;
}

// Get (evaluate) spline tangent: Cubic Bezier 2D
Vector2 SplineSegmentBezierCubic2Tangent(SplineSegmentBezierCubic2 spline, float t)
{
    Vector2 tangent = { 0 };

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    tangent.x = a*(spline.startControlPos.x - spline.startPos.x) + b*(spline.endControlPos.x - spline.startControlPos.x) + c*(spline.endPos.x - spline.endControlPos.x);
    tangent.y = a*(spline.startControlPos.y - spline.startPos.y) + b*(spline.endControlPos.y - spline.startControlPos.y) + c*(spline.endPos.y - spline.endControlPos.y);

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    return tangent;
}

// Get (evaluate) spline normal: Cubic Bezier 2D
Vector2 SplineSegmentBezierCubic2Normal(SplineSegmentBezierCubic2 spline, float t)
{
    Vector2 tangent = { 0 };
    Vector2 normal = { 0 };

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    tangent.x = a*(spline.startControlPos.x - spline.startPos.x) + b*(spline.endControlPos.x - spline.startControlPos.x) + c*(spline.endPos.x - spline.endControlPos.x);
    tangent.y = a*(spline.startControlPos.y - spline.startPos.y) + b*(spline.endControlPos.y - spline.startControlPos.y) + c*(spline.endPos.y - spline.endControlPos.y);

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    normal.x = tangent.y;
    normal.y = -tangent.x;

    return normal;
}

// Get spline rate of change, Quadratic Bezier
Vector2 SplineSegmentBezierQuad2Acceleration(SplineSegmentBezierQuad2 spline)
{
    Vector2 acceleration = { 0 };

    acceleration.x = 2.0f*(spline.endPos.x - 2.0f*spline.controlPos.x - spline.startPos.x);
    acceleration.y = 2.0f*(spline.endPos.y - 2.0f*spline.controlPos.y - spline.startPos.y);

    return acceleration;
}

// Get spline rate of change for a given t [0.0f .. 1.0f], Cubic Bezier
Vector2 SplineSegmentBezierCubic2Acceleration(SplineSegmentBezierCubic2 spline, float t)
{
    Vector2 acceleration = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    acceleration.x = a*(spline.endControlPos.x - 2.0f*spline.startControlPos.x + spline.startPos.x) + b*(spline.endPos.x - 2.0f*spline.endControlPos.x + spline.startControlPos.x);
    acceleration.y = a*(spline.endControlPos.y - 2.0f*spline.startControlPos.y + spline.startPos.y) + b*(spline.endPos.y - 2.0f*spline.endControlPos.y + spline.startControlPos.y);

    return acceleration;
}

// Get spline rate of acceleration, Cubic Bezier
Vector2 SplineSegmentBezierCubic2Jolt(SplineSegmentBezierCubic2 spline)
{
    Vector2 jolt = { 0 };

    jolt.x = 6.0f*(spline.endPos.x + 3.0f*(spline.startControlPos.x - spline.endControlPos.x) - spline.startPos.x);
    jolt.y = 6.0f*(spline.endPos.y + 3.0f*(spline.startControlPos.y - spline.endControlPos.y) - spline.startPos.y);

    return jolt;
}

// Compute spline curve bounding rectangle, Linear Bezier
BoundingBox2 SplineSegmentLinear2Bounds(SplineSegmentLinear2 spline)
{
    float xMin, yMin;
    float xMax, yMax;

    if (spline.startPos.x < spline.endPos.x)
    {
        xMin = spline.startPos.x;
        xMax = spline.endPos.x;
    }
    else
    {
        xMin = spline.endPos.x;
        xMax = spline.startPos.x;
    }

    if (spline.startPos.y < spline.endPos.y)
    {
        yMin = spline.startPos.y;
        yMax = spline.endPos.y;
    }
    else
    {
        yMin = spline.endPos.y;
        yMax = spline.startPos.y;
    }

    // straight line will never escape bounds

    BoundingBox2 bounds = { { xMin, yMin }, { xMax, yMax } };

    return bounds;
}

// Compute spline curve bounding rectangle, Quadratic Bezier
BoundingBox2 SplineSegmentBezierQuad2Bounds(SplineSegmentBezierQuad2 spline)
{
    float xMin, yMin;
    float xMax, yMax;

    if (spline.startPos.x < spline.endPos.x)
    {
        xMin = spline.startPos.x;
        xMax = spline.endPos.x;
    }
    else
    {
        xMin = spline.endPos.x;
        xMax = spline.startPos.x;
    }

    if (spline.startPos.y < spline.endPos.y)
    {
        yMin = spline.startPos.y;
        yMax = spline.endPos.y;
    }
    else
    {
        yMin = spline.endPos.y;
        yMax = spline.startPos.y;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float startPosA[] = { spline.startPos.x, spline.startPos.y };
    float controlPosA[] = { spline.controlPos.x, spline.controlPos.y };
    float endPosA[] = { spline.endPos.x, spline.endPos.y };

    for (int i = 0; i < 2; ++i)
    {
        float a = startPosA[i] - 2.0f*controlPosA[i] + endPosA[i];
        float b = 2.0f*(controlPosA[i] - startPosA[i]);
        float c = startPosA[i];

        if (a != 0)
        {
            float bSqrMinus4ac = b*b - 4.0f*a*c;
            float t[2] = { 0 };
            int tCount = 0;
            if (bSqrMinus4ac > 0)
            {
                float denominator = 1.0f/(2.0f*a);

                float term0 = -b*denominator;
                float term1 = sqrtf(bSqrMinus4ac)*denominator;

                t[0] = term0 + term1;
                if (0.0f < t[0] && t[0] < 1.0f) ++tCount;

                t[tCount] = term0 - term1;
                if (0.0f < t[tCount] && t[tCount] < 1.0f) ++tCount;
            }
            else if (bSqrMinus4ac == 0)
            {
                t[0] = -b/(2.0f*a);
                if (0.0f < t[0] && t[0] < 1.0f) ++tCount;
            }
            else; // ignore imaginary solution

            for (int j = 0; j < tCount; ++j)
            {
                Vector2 point = SplineSegmentBezierQuad2Point(spline, t[j]);

                if (point.x < xMin) xMin = point.x;
                if (point.x > xMax) xMax = point.x;
                if (point.y < yMin) yMin = point.y;
                if (point.y > yMax) yMax = point.y;
            }
        }
        else; // straight line will never escape bounds
    }

    BoundingBox2 bounds = { { xMin, yMin }, { xMax, yMax } };

    return bounds;
}

// Compute spline curve bounding rectangle, Cubic Bezier
BoundingBox2 SplineSegmentBezierCubic2Bounds(SplineSegmentBezierCubic2 spline)
{
    float xMin, yMin;
    float xMax, yMax;

    if (spline.startPos.x < spline.endPos.x)
    {
        xMin = spline.startPos.x;
        xMax = spline.endPos.x;
    }
    else
    {
        xMin = spline.endPos.x;
        xMax = spline.startPos.x;
    }

    if (spline.startPos.y < spline.endPos.y)
    {
        yMin = spline.startPos.y;
        yMax = spline.endPos.y;
    }
    else
    {
        yMin = spline.endPos.y;
        yMax = spline.startPos.y;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float startPosA[] = { spline.startPos.x, spline.startPos.y };
    float startControlPosA[] = { spline.startControlPos.x, spline.startControlPos.y };
    float endControlPosA[] = { spline.endControlPos.x, spline.endControlPos.y };
    float endPosA[] = { spline.endPos.x, spline.endPos.y };

    for (int i = 0; i < 2; ++i)
    {
        float a = -3.0f*startPosA[i] + 9.0f*startControlPosA[i] - 9.0f*endControlPosA[i] + 3.0f*endPosA[i];
        float b = 6.0f*startPosA[i] - 12.0f*startControlPosA[i] + 6.0f*endControlPosA[i];
        float c = -3.0f*startPosA[i] + 3.0f*startControlPosA[i];

        if (a != 0)
        {
            float bSqrMinus4ac = b*b - 4.0f*a*c;
            float t[2] = { 0 };
            int tCount = 0;
            if (bSqrMinus4ac > 0)
            {
                float denominator = 1.0f/(2.0f*a);

                float term0 = -b*denominator;
                float term1 = sqrtf(bSqrMinus4ac)*denominator;

                t[0] = term0 + term1;
                if (0.0f < t[0] && t[0] < 1.0f) ++tCount;

                t[tCount] = term0 - term1;
                if (0.0f < t[tCount] && t[tCount] < 1.0f) ++tCount;
            }
            else if (bSqrMinus4ac == 0)
            {
                t[0] = -b/(2.0f*a);
                if (0.0f < t[0] && t[0] < 1.0f) ++tCount;
            }
            else; // ignore imaginary solution

            for (int j = 0; j < tCount; ++j)
            {
                Vector2 point = SplineSegmentBezierCubic2Point(spline, t[j]);

                if (point.x < xMin) xMin = point.x;
                if (point.x > xMax) xMax = point.x;
                if (point.y < yMin) yMin = point.y;
                if (point.y > yMax) yMax = point.y;
            }
        }
        else; // straight line will never escape bounds
    }

    BoundingBox2 bounds = { { xMin, yMin }, { xMax, yMax }  };

    return bounds;
}

// Get (evaluate) squared length of spline: Linear 2D
float SplineSegmentLinear2LengthSqr(SplineSegmentLinear2 spline)
{
    float lengthSqr = 0.0f;

    float dx = spline.endPos.x - spline.startPos.x;
    float dy = spline.endPos.y - spline.startPos.y;

    lengthSqr = dx*dx + dy*dy;

    return lengthSqr;
}

// Get (evaluate) length of spline: Linear 2D
float SplineSegmentLinear2Length(SplineSegmentLinear2 spline)
{
    float length = 0.0f;

    float dx = spline.endPos.x - spline.startPos.x;
    float dy = spline.endPos.y - spline.startPos.y;

    length = sqrtf(dx*dx + dy*dy);

    return length;
}

// Get (evaluate) squared length of subspline: Linear 2D
float SplineSegmentLinear2SubLengthSqr(SplineSegmentLinear2 spline, float tStart, float tEnd)
{
    float lengthSqr = 0.0f;

    float a = tStart - tEnd;
    float b = tEnd - tStart;

    float dx = a*spline.startPos.x + b*spline.endPos.x;
    float dy = a*spline.startPos.y + b*spline.endPos.y;

    lengthSqr = dx*dx + dy*dy;

    return lengthSqr;
}

// Get (evaluate) length of subspline: Linear 2D
float SplineSegmentLinear2SubLength(SplineSegmentLinear2 spline, float tStart, float tEnd)
{
    float length = 0.0f;

    float a = tStart - tEnd;
    float b = tEnd - tStart;

    float dx = a*spline.startPos.x + b*spline.endPos.x;
    float dy = a*spline.startPos.y + b*spline.endPos.y;

    length = sqrtf(dx*dx + dy*dy);

    return length;
}

// Reciprocal radius (or "radians per meter") for a given t [0.0f .. 1.0f], Cubic Bezier
float SplineSegmentBezierCubic2Curvature(SplineSegmentBezierCubic2 spline, float t)
{
    float curvature = 0.0f;

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    Vector2 velocity = { 0 };

    velocity.x = a*(spline.startControlPos.x - spline.startPos.x) + b*(spline.endControlPos.x - spline.startControlPos.x) + c*(spline.endPos.x - spline.endControlPos.x);
    velocity.y = a*(spline.startControlPos.y - spline.startPos.y) + b*(spline.endControlPos.y - spline.startControlPos.y) + c*(spline.endPos.y - spline.endControlPos.y);

    a = 2.0f*(1.0f - t);
    b = 2.0f*t;

    Vector2 acceleration = { 0 };

    acceleration.x = a*(spline.endControlPos.x - 2.0f*spline.startControlPos.x + spline.startPos.x) + b*(spline.endPos.x - 2.0f*spline.endControlPos.x + spline.startControlPos.x);
    acceleration.y = a*(spline.endControlPos.y - 2.0f*spline.startControlPos.y + spline.startPos.y) + b*(spline.endPos.y - 2.0f*spline.endControlPos.y + spline.startControlPos.y);

    curvature = (velocity.x*acceleration.y - velocity.y*acceleration.x)/powf(sqrtf(velocity.x*velocity.x + velocity.y*velocity.y), 3);

    return curvature;
}

// Get value of t (unbounded) for the point on the line closest to a given position
// NOTE 1: If the return is less than 0.0f or greater than 1.0f, the nearest point may be in a different segment
// NOTE 2: Return can be clamped [0.0f .. 1.0f] to snap the point to the start/end of the spline
float SplineSegmentLinear2NearestT(SplineSegmentLinear2 spline, Vector2 point)
{
    Vector2 edge = { 0 };
    edge.x = spline.endPos.x - spline.startPos.x;
    edge.y = spline.endPos.y - spline.startPos.y;

    Vector2 diff = { 0 };
    diff.x = point.x - spline.startPos.x;
    diff.y = point.y - spline.startPos.y;

    float t = (edge.x*diff.x + edge.y*diff.y)/(edge.x*edge.x + edge.y*edge.y);

    return t;
}

#endif // RSPLINES_2D

#if defined(RSPLINES_3D)

// Get (evaluate) spline point: Linear 3D
// NOTE: Minimum 2 points
Vector3 SplineLinear3Point(const Vector3 *points, int pointCount, float t)
{
    Vector3 point = { 0 };

    if (pointCount >= 2)
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 2)) tInt = pointCount - 2;
        float tFrac = t - tInt;

        SplineSegmentLinear3 segment = { 0 };
        segment.startPos = points[tInt];
        segment.endPos = points[tInt + 1];

        point = SplineSegmentLinear3Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: B-Spline 3D
// NOTE: Requires 3n+1 points; minimum 4
Vector3 SplineBasis3Point(const Vector3 *points, int pointCount, float t)
{
    Vector3 point = { 0 };

    if ((pointCount >= 4) && ((pointCount%3) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 4)) tInt = pointCount - 4;
        float tFrac = t - tInt;

        SplineSegmentBasis3 segment = { 0 };
        segment.p1 = points[3*tInt];
        segment.p2 = points[3*tInt + 1];
        segment.p3 = points[3*tInt + 2];
        segment.p4 = points[3*tInt + 3];

        point = SplineSegmentBasis3Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: Catmull-Rom 3D
// NOTE: Requires 3n+1 points; minimum 4
Vector3 SplineCatmullRom3Point(const Vector3 *points, int pointCount, float t)
{
    Vector3 point = { 0 };

    if ((pointCount >= 4) && ((pointCount%3) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 4)) tInt = pointCount - 4;
        float tFrac = t - tInt;

        SplineSegmentCatmullRom3 segment = { 0 };
        segment.p1 = points[3*tInt];
        segment.p2 = points[3*tInt + 1];
        segment.p3 = points[3*tInt + 2];
        segment.p4 = points[3*tInt + 3];

        point = SplineSegmentCatmullRom3Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: Quadratic Bezier 3D
// NOTE: Requires 2n+1 points; minimum 3
Vector3 SplineBezierQuad3Point(const Vector3 *points, int pointCount, float t)
{
    Vector3 point = { 0 };

    if ((pointCount >= 3) && ((pointCount%2) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 3)) tInt = pointCount - 3;
        float tFrac = t - tInt;

        SplineSegmentBezierQuad3 segment = { 0 };
        segment.startPos = points[2*tInt];
        segment.controlPos = points[2*tInt + 1];
        segment.endPos = points[2*tInt + 2];

        point = SplineSegmentBezierQuad3Point(segment, tFrac);
    }

    return point;
}

// Get (evaluate) spline point: Cubic Bezier 3D
// NOTE: Requires 3n+1 points; minimum 4
Vector3 SplineBezierCubic3Point(const Vector3 *points, int pointCount, float t)
{
    Vector3 point = { 0 };

    if ((pointCount >= 4) && ((pointCount%3) == 1))
    {
        int tInt = (int)t;
        if (tInt < 0) tInt = 0;
        if (tInt > (pointCount - 4)) tInt = pointCount - 4;
        float tFrac = t - tInt;

        SplineSegmentBezierCubic3 segment = { 0 };
        segment.startPos = points[3*tInt];
        segment.startControlPos = points[3*tInt + 1];
        segment.endControlPos = points[3*tInt + 1];
        segment.endPos = points[3*tInt + 2];

        point = SplineSegmentBezierCubic3Point(segment, tFrac);
    }

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Linear
Vector3 SplineSegmentLinear3Point(SplineSegmentLinear3 spline, float t)
{
    Vector3 point = { 0 };

    point.x = spline.startPos.x*(1.0f - t) + spline.endPos.x*t;
    point.y = spline.startPos.y*(1.0f - t) + spline.endPos.y*t;
    point.z = spline.startPos.z*(1.0f - t) + spline.endPos.z*t;

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], B-Spline
Vector3 SplineSegmentBasis3Point(SplineSegmentBasis3 spline, float t)
{
    Vector3 point = { 0 };

    float a0 = (-spline.p1.x + 3*spline.p2.x - 3*spline.p3.x + spline.p4.x)/6.0f;
    float a1 = (3*spline.p1.x - 6*spline.p2.x + 3*spline.p3.x)/6.0f;
    float a2 = (-3*spline.p1.x + 3*spline.p3.x)/6.0f;
    float a3 = (spline.p1.x + 4*spline.p2.x + spline.p3.x)/6.0f;

    float b0 = (-spline.p1.y + 3*spline.p2.y - 3*spline.p3.y + spline.p4.y)/6.0f;
    float b1 = (3*spline.p1.y - 6*spline.p2.y + 3*spline.p3.y)/6.0f;
    float b2 = (-3*spline.p1.y + 3*spline.p3.y)/6.0f;
    float b3 = (spline.p1.y + 4*spline.p2.y + spline.p3.y)/6.0f;

    float c0 = (-spline.p1.z + 3*spline.p2.z - 3*spline.p3.z + spline.p4.z)/6.0f;
    float c1 = (3*spline.p1.z - 6*spline.p2.z + 3*spline.p3.z)/6.0f;
    float c2 = (-3*spline.p1.z + 3*spline.p3.z)/6.0f;
    float c3 = (spline.p1.z + 4*spline.p2.z + spline.p3.z)/6.0f;

    point.x = a3 + t*(a2 + t*(a1 + t*a0));
    point.y = b3 + t*(b2 + t*(b1 + t*b0));
    point.z = c3 + t*(c2 + t*(c1 + t*c0));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Catmull-Rom
Vector3 SplineSegmentCatmullRom3Point(SplineSegmentCatmullRom3 spline, float t)
{
    Vector3 point = { 0 };

    float q0 = (-1*t*t*t) + (2*t*t) + (-1*t);
    float q1 = (3*t*t*t) + (-5*t*t) + 2;
    float q2 = (-3*t*t*t) + (4*t*t) + t;
    float q3 = t*t*t - t*t;

    point.x = 0.5f*((spline.p1.x*q0) + (spline.p2.x*q1) + (spline.p3.x*q2) + (spline.p4.x*q3));
    point.y = 0.5f*((spline.p1.y*q0) + (spline.p2.y*q1) + (spline.p3.y*q2) + (spline.p4.y*q3));
    point.z = 0.5f*((spline.p1.z*q0) + (spline.p2.z*q1) + (spline.p3.z*q2) + (spline.p4.z*q3));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Quadratic Bezier
Vector3 SplineSegmentBezierQuad3Point(SplineSegmentBezierQuad3 spline, float t)
{
    Vector3 point = { 0 };

    float a = powf(1.0f - t, 2);
    float b = 2.0f*(1.0f - t)*t;
    float c = powf(t, 2);

    point.x = a*spline.startPos.x + b*spline.controlPos.x + c*spline.endPos.x;
    point.y = a*spline.startPos.y + b*spline.controlPos.y + c*spline.endPos.y;
    point.z = a*spline.startPos.z + b*spline.controlPos.z + c*spline.endPos.z;

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Cubic Bezier
Vector3 SplineSegmentBezierCubic3Point(SplineSegmentBezierCubic3 spline, float t)
{
    Vector3 point = { 0 };

    float a = powf(1.0f - t, 3);
    float b = 3.0f*powf(1.0f - t, 2)*t;
    float c = 3.0f*(1.0f - t)*powf(t, 2);
    float d = powf(t, 3);

    point.x = a*spline.startPos.x + b*spline.startControlPos.x + c*spline.endControlPos.x + d*spline.endPos.x;
    point.y = a*spline.startPos.y + b*spline.startControlPos.y + c*spline.endControlPos.y + d*spline.endPos.y;
    point.z = a*spline.startPos.z + b*spline.startControlPos.z + c*spline.endControlPos.z + d*spline.endPos.z;

    return point;
}

// Get spline control point given evenly-spaced points on that curve, Quadratic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
SplineSegmentBezierQuad3 SplineSegmentBezierQuad3FromPoints(Vector3 startPos, Vector3 midPos, Vector3 endPos)
{
    SplineSegmentBezierQuad3 spline = { 0 };

    spline.startPos = startPos;
    spline.endPos = endPos;

    spline.controlPos.x = 2.0f*midPos.x - 0.5f*(startPos.x + endPos.x);
    spline.controlPos.y = 2.0f*midPos.y - 0.5f*(startPos.y + endPos.y);
    spline.controlPos.z = 2.0f*midPos.z - 0.5f*(startPos.z + endPos.z);

    return spline;
}

// Get spline control points given evenly-spaced points on that curve, Cubic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
SplineSegmentBezierCubic3 SplineSegmentBezierCubic3FromPoints(Vector3 startPos, Vector3 oneThirdsPos, Vector3 twoThirdsPos, Vector3 endPos)
{
    SplineSegmentBezierCubic3 spline = { 0 };

    float a = -5.0f/6.0f;
    float b = 3.0f;
    float c = -3.0f/2.0f;
    float d = 1.0f/3.0f;

    spline.startPos = startPos;
    spline.endPos = endPos;

    spline.startControlPos.x = a*startPos.x + b*oneThirdsPos.x + c*twoThirdsPos.x + d*endPos.x;
    spline.startControlPos.y = a*startPos.y + b*oneThirdsPos.y + c*twoThirdsPos.y + d*endPos.y;
    spline.startControlPos.z = a*startPos.z + b*oneThirdsPos.z + c*twoThirdsPos.z + d*endPos.z;

    spline.endControlPos.x = a*endPos.x + b*twoThirdsPos.x + c*oneThirdsPos.x + d*startPos.x;
    spline.endControlPos.y = a*endPos.y + b*twoThirdsPos.y + c*oneThirdsPos.y + d*startPos.y;
    spline.endControlPos.z = a*endPos.z + b*twoThirdsPos.z + c*oneThirdsPos.z + d*startPos.z;

    return spline;
}

// Get spline direction and speed, Linear Bezier
//
// Normalize to get the "forward" direction of the curve
Vector3 SplineSegmentLinear3Velocity(SplineSegmentLinear3 spline)
{
    Vector3 velocity = { 0 };

    velocity.x = spline.endPos.x - spline.startPos.x;
    velocity.y = spline.endPos.y - spline.startPos.y;
    velocity.z = spline.endPos.z - spline.startPos.z;

    return velocity;
}

// Get (evaluate) spline tangent: Linear 3D
Vector3 SplineSegmentLinear3Tangent(SplineSegmentLinear3 spline)
{
    Vector3 tangent = { 0 };

    tangent.x = spline.endPos.x - spline.startPos.x;
    tangent.y = spline.endPos.y - spline.startPos.y;
    tangent.z = spline.endPos.z - spline.startPos.z;

    float speedInv = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y + tangent.z*tangent.z);

    tangent.x *= speedInv;
    tangent.y *= speedInv;
    tangent.z *= speedInv;

    return tangent;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Quadratic Bezier
//
// Normalize to get the "forward" direction of the curve at t
Vector3 SplineSegmentBezierQuad3Velocity(SplineSegmentBezierQuad3 spline, float t)
{
    Vector3 velocity = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    velocity.x = a*(spline.controlPos.x - spline.startPos.x) + b*(spline.endPos.x - spline.controlPos.x);
    velocity.y = a*(spline.controlPos.y - spline.startPos.y) + b*(spline.endPos.y - spline.controlPos.y);
    velocity.z = a*(spline.controlPos.z - spline.startPos.z) + b*(spline.endPos.z - spline.controlPos.z);

    return velocity;
}

// Get (evaluate) spline tangent: Quadratic Bezier 3D
Vector3 SplineSegmentBezierQuad3Tangent(SplineSegmentBezierQuad3 spline, float t)
{
    Vector3 tangent = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    tangent.x = a*(spline.controlPos.x - spline.startPos.x) + b*(spline.endPos.x - spline.controlPos.x);
    tangent.y = a*(spline.controlPos.y - spline.startPos.y) + b*(spline.endPos.y - spline.controlPos.y);
    tangent.z = a*(spline.controlPos.z - spline.startPos.z) + b*(spline.endPos.z - spline.controlPos.z);

    float speedInv = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y + tangent.z*tangent.z);

    tangent.x *= speedInv;
    tangent.y *= speedInv;
    tangent.z *= speedInv;

    return tangent;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Cubic Bezier
//
// Normalize to get the "forward" direction of the curve at t
Vector3 SplineSegmentBezierCubic3Velocity(SplineSegmentBezierCubic3 spline, float t)
{
    Vector3 velocity = { 0 };

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    velocity.x = a*(spline.startControlPos.x - spline.startPos.x) + b*(spline.endControlPos.x - spline.startControlPos.x) + c*(spline.endPos.x - spline.endControlPos.x);
    velocity.y = a*(spline.startControlPos.y - spline.startPos.y) + b*(spline.endControlPos.y - spline.startControlPos.y) + c*(spline.endPos.y - spline.endControlPos.y);
    velocity.z = a*(spline.startControlPos.z - spline.startPos.z) + b*(spline.endControlPos.z - spline.startControlPos.z) + c*(spline.endPos.z - spline.endControlPos.z);

    return velocity;
}

// Get (evaluate) spline tangent: Cubic Bezier 3D
Vector3 SplineSegmentBezierCubic3Tangent(SplineSegmentBezierCubic3 spline, float t)
{
    Vector3 tangent = { 0 };

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    tangent.x = a*(spline.startControlPos.x - spline.startPos.x) + b*(spline.endControlPos.x - spline.startControlPos.x) + c*(spline.endPos.x - spline.endControlPos.x);
    tangent.y = a*(spline.startControlPos.y - spline.startPos.y) + b*(spline.endControlPos.y - spline.startControlPos.y) + c*(spline.endPos.y - spline.endControlPos.y);
    tangent.z = a*(spline.startControlPos.z - spline.startPos.z) + b*(spline.endControlPos.z - spline.startControlPos.z) + c*(spline.endPos.z - spline.endControlPos.z);

    float speedInv = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y + tangent.z*tangent.z);

    tangent.x *= speedInv;
    tangent.y *= speedInv;
    tangent.z *= speedInv;

    return tangent;
}

// Get spline rate of change, Quadratic Bezier
Vector3 SplineSegmentBezierQuad3Acceleration(SplineSegmentBezierQuad3 spline)
{
    Vector3 acceleration = { 0 };

    acceleration.x = 2.0f*(spline.endPos.x - 2.0f*spline.controlPos.x - spline.startPos.x);
    acceleration.y = 2.0f*(spline.endPos.y - 2.0f*spline.controlPos.y - spline.startPos.y);
    acceleration.z = 2.0f*(spline.endPos.z - 2.0f*spline.controlPos.z - spline.startPos.z);

    return acceleration;
}

// Get spline rate of change for a given t [0.0f .. 1.0f], Cubic Bezier
Vector3 SplineSegmentBezierCubic3Acceleration(SplineSegmentBezierCubic3 spline, float t)
{
    Vector3 acceleration = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    acceleration.x = a*(spline.endControlPos.x - 2.0f*spline.startControlPos.x + spline.startPos.x) + b*(spline.endPos.x - 2.0f*spline.endControlPos.x + spline.startControlPos.x);
    acceleration.y = a*(spline.endControlPos.y - 2.0f*spline.startControlPos.y + spline.startPos.y) + b*(spline.endPos.y - 2.0f*spline.endControlPos.y + spline.startControlPos.y);
    acceleration.z = a*(spline.endControlPos.z - 2.0f*spline.startControlPos.z + spline.startPos.z) + b*(spline.endPos.z - 2.0f*spline.endControlPos.z + spline.startControlPos.z);

    return acceleration;
}

// Get spline rate of acceleration, Cubic Bezier
Vector3 SplineSegmentBezierCubic3Jolt(SplineSegmentBezierCubic3 spline)
{
    Vector3 jolt = { 0 };

    jolt.x = 6.0f*(spline.endPos.x + 3.0f*(spline.startControlPos.x - spline.endControlPos.x) - spline.startPos.x);
    jolt.y = 6.0f*(spline.endPos.y + 3.0f*(spline.startControlPos.y - spline.endControlPos.y) - spline.startPos.y);
    jolt.z = 6.0f*(spline.endPos.z + 3.0f*(spline.startControlPos.z - spline.endControlPos.z) - spline.startPos.z);

    return jolt;
}

// Compute spline curve bounding rectangle, Linear Bezier
BoundingBox3 SplineSegmentLinear3Bounds(SplineSegmentLinear3 spline)
{
    float xMin, yMin, zMin;
    float xMax, yMax, zMax;

    if (spline.startPos.x < spline.endPos.x)
    {
        xMin = spline.startPos.x;
        xMax = spline.endPos.x;
    }
    else
    {
        xMin = spline.endPos.x;
        xMax = spline.startPos.x;
    }

    if (spline.startPos.y < spline.endPos.y)
    {
        yMin = spline.startPos.y;
        yMax = spline.endPos.y;
    }
    else
    {
        yMin = spline.endPos.y;
        yMax = spline.startPos.y;
    }

    if (spline.startPos.z < spline.endPos.z)
    {
        zMin = spline.startPos.z;
        zMax = spline.endPos.z;
    }
    else
    {
        zMin = spline.endPos.z;
        zMax = spline.startPos.z;
    }

    // straight line will never escape bounds

    BoundingBox3 bounds = { { xMin, yMin, zMin }, { xMax, yMax, zMax } };

    return bounds;
}



// Compute spline curve bounding rectangle, Quadratic Bezier
BoundingBox3 SplineSegmentBezierQuad3Bounds(SplineSegmentBezierQuad3 spline)
{
    float xMin, yMin, zMin;
    float xMax, yMax, zMax;

    if (spline.startPos.x < spline.endPos.x)
    {
        xMin = spline.startPos.x;
        xMax = spline.endPos.x;
    }
    else
    {
        xMin = spline.endPos.x;
        xMax = spline.startPos.x;
    }

    if (spline.startPos.y < spline.endPos.y)
    {
        yMin = spline.startPos.y;
        yMax = spline.endPos.y;
    }
    else
    {
        yMin = spline.endPos.y;
        yMax = spline.startPos.y;
    }

    if (spline.startPos.z < spline.endPos.z)
    {
        zMin = spline.startPos.z;
        zMax = spline.endPos.z;
    }
    else
    {
        zMin = spline.endPos.z;
        zMax = spline.startPos.z;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float startPosA[] = { spline.startPos.x, spline.startPos.y, spline.startPos.z };
    float controlPosA[] = { spline.controlPos.x, spline.controlPos.y, spline.controlPos.z };
    float endPosA[] = { spline.endPos.x, spline.endPos.y, spline.endPos.z };

    for (int i = 0; i < 3; ++i)
    {
        float a = startPosA[i] - 2.0f*controlPosA[i] + endPosA[i];
        float b = 2.0f*(controlPosA[i] - startPosA[i]);
        float c = startPosA[i];

        if (a != 0)
        {
            float bSqrMinus4ac = b*b - 4.0f*a*c;
            float t[2] = { 0 };
            int tCount = 0;
            if (bSqrMinus4ac > 0)
            {
                float denominator = 1.0f/(2.0f*a);

                float term0 = -b*denominator;
                float term1 = sqrtf(bSqrMinus4ac)*denominator;

                t[0] = term0 + term1;
                if (0.0f < t[0] && t[0] < 1.0f) ++tCount;

                t[tCount] = term0 - term1;
                if (0.0f < t[tCount] && t[tCount] < 1.0f) ++tCount;
            }
            else if (bSqrMinus4ac == 0)
            {
                t[0] = -b/(2.0f*a);
                if (0.0f < t[0] && t[0] < 1.0f) ++tCount;
            }
            else; // ignore imaginary solution

            for (int j = 0; j < tCount; ++j)
            {
                Vector3 point = SplineSegmentBezierQuad3Point(spline, t[j]);

                if (point.x < xMin) xMin = point.x;
                if (point.x > xMax) xMax = point.x;
                if (point.y < yMin) yMin = point.y;
                if (point.y > yMax) yMax = point.y;
                if (point.z < zMin) zMin = point.z;
                if (point.z > zMax) zMax = point.z;
            }
        }
        else; // straight line will never escape bounds
    }

    BoundingBox3 bounds = { { xMin, yMin, zMin }, { xMax, yMax, zMax } };

    return bounds;
}

// Compute spline curve bounding rectangle, Cubic Bezier
BoundingBox3 SplineSegmentBezierCubic3Bounds(SplineSegmentBezierCubic3 spline)
{
    float xMin, yMin, zMin;
    float xMax, yMax, zMax;

    if (spline.startPos.x < spline.endPos.x)
    {
        xMin = spline.startPos.x;
        xMax = spline.endPos.x;
    }
    else
    {
        xMin = spline.endPos.x;
        xMax = spline.startPos.x;
    }

    if (spline.startPos.y < spline.endPos.y)
    {
        yMin = spline.startPos.y;
        yMax = spline.endPos.y;
    }
    else
    {
        yMin = spline.endPos.y;
        yMax = spline.startPos.y;
    }

    if (spline.startPos.z < spline.endPos.z)
    {
        zMin = spline.startPos.z;
        zMax = spline.endPos.z;
    }
    else
    {
        zMin = spline.endPos.z;
        zMax = spline.startPos.z;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float startPosA[] = { spline.startPos.x, spline.startPos.y, spline.startPos.z };
    float startControlPosA[] = { spline.startControlPos.x, spline.startControlPos.y, spline.startControlPos.z };
    float endControlPosA[] = { spline.endControlPos.x, spline.endControlPos.y, spline.endControlPos.z };
    float endPosA[] = { spline.endPos.x, spline.endPos.y, spline.endPos.z };

    for (int i = 0; i < 3; ++i)
    {
        float a = -3.0f*startPosA[i] + 9.0f*startControlPosA[i] - 9.0f*endControlPosA[i] + 3.0f*endPosA[i];
        float b = 6.0f*startPosA[i] - 12.0f*startControlPosA[i] + 6.0f*endControlPosA[i];
        float c = -3.0f*startPosA[i] + 3.0f*startControlPosA[i];

        if (a != 0)
        {
            float bSqrMinus4ac = b*b - 4.0f*a*c;
            float t[2] = { 0 };
            int tCount = 0;
            if (bSqrMinus4ac > 0)
            {
                float denominator = 1.0f/(2.0f*a);

                float term0 = -b*denominator;
                float term1 = sqrtf(bSqrMinus4ac)*denominator;

                t[0] = term0 + term1;
                if (0.0f < t[0] && t[0] < 1.0f) ++tCount;

                t[tCount] = term0 - term1;
                if (0.0f < t[tCount] && t[tCount] < 1.0f) ++tCount;
            }
            else if (bSqrMinus4ac == 0)
            {
                t[0] = -b/(2.0f*a);
                if (0.0f < t[0] && t[0] < 1.0f) ++tCount;
            }
            else; // ignore imaginary solution

            for (int j = 0; j < tCount; ++j)
            {
                Vector3 point = SplineSegmentBezierCubic3Point(spline, t[j]);

                if (point.x < xMin) xMin = point.x;
                if (point.x > xMax) xMax = point.x;
                if (point.y < yMin) yMin = point.y;
                if (point.y > yMax) yMax = point.y;
                if (point.z < zMin) zMin = point.z;
                if (point.z > zMax) zMax = point.z;
            }
        }
        else; // straight line will never escape bounds
    }

    BoundingBox3 bounds = { { xMin, yMin, zMin }, { xMax, yMax, zMax }  };

    return bounds;
}

// Get (evaluate) squared length of spline: Linear 3D
float SplineSegmentLinear3LengthSqr(SplineSegmentLinear3 spline)
{
    float lengthSqr = 0.0f;

    float dx = spline.endPos.x - spline.startPos.x;
    float dy = spline.endPos.y - spline.startPos.y;
    float dz = spline.endPos.z - spline.startPos.z;

    lengthSqr = dx*dx + dy*dy + dz*dz;

    return lengthSqr;
}

// Get (evaluate) length of spline: Linear 3D
float SplineSegmentLinear3Length(SplineSegmentLinear3 spline)
{
    float length = 0.0f;

    float dx = spline.endPos.x - spline.startPos.x;
    float dy = spline.endPos.y - spline.startPos.y;
    float dz = spline.endPos.z - spline.startPos.z;

    length = sqrtf(dx*dx + dy*dy + dz*dz);

    return length;
}

// Get (evaluate) squared length of subspline: Linear 3D
float SplineSegmentLinear3SubLengthSqr(SplineSegmentLinear3 spline, float tStart, float tEnd)
{
    float lengthSqr = 0.0f;

    float a = tStart - tEnd;
    float b = tEnd - tStart;

    float dx = a*spline.startPos.x + b*spline.endPos.x;
    float dy = a*spline.startPos.y + b*spline.endPos.y;
    float dz = a*spline.startPos.z + b*spline.endPos.z;

    lengthSqr = dx*dx + dy*dy + dz*dz;

    return lengthSqr;
}

// Get (evaluate) length of subspline: Linear 3D
float SplineSegmentLinear3SubLength(SplineSegmentLinear3 spline, float tStart, float tEnd)
{
    float length = 0.0f;

    float a = tStart - tEnd;
    float b = tEnd - tStart;

    float dx = a*spline.startPos.x + b*spline.endPos.x;
    float dy = a*spline.startPos.y + b*spline.endPos.y;
    float dz = a*spline.startPos.z + b*spline.endPos.z;

    length = sqrtf(dx*dx + dy*dy + dz*dz);

    return length;
}

// Get value of t (unbounded) for the point on the line closest to a given position
// NOTE 1: If the return is less than 0.0f or greater than 1.0f, the nearest point may be in a different segment
// NOTE 2: Return can be clamped [0.0f .. 1.0f] to snap the point to the start/end of the spline
float SplineSegmentLinear3NearestT(SplineSegmentLinear3 spline, Vector3 point)
{
    Vector3 edge = { 0 };
    edge.x = spline.endPos.x - spline.startPos.x;
    edge.y = spline.endPos.y - spline.startPos.y;
    edge.z = spline.endPos.z - spline.startPos.z;

    Vector3 diff = { 0 };
    diff.x = point.x - spline.startPos.x;
    diff.y = point.y - spline.startPos.y;
    diff.z = point.z - spline.startPos.z;

    float t = (edge.x*diff.x + edge.y*diff.y + edge.z*diff.z)/(edge.x*edge.x + edge.y*edge.y + edge.z*edge.z);

    return t;
}

#endif // RSPLINES_3D

#endif // RSPLINES_IMPLEMENTATION

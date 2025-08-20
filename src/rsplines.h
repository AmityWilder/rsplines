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
*   CONFIGURATION:
*       #define RSPLINES_IMPLEMENTATION
*           Generates the implementation of the library into the included file
*           If not defined, the library is in header only mode and can be included in other headers
*           or source files without problems. But only ONE file should hold the implementation
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

#include "raylib.h"  // Vector2 and Vector3

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

// 1D bounding box
typedef struct Bounds1D {
    float min;
    float max;
} BoundingBox1;

// 2D bounding box
typedef struct Bounds2D {
    Vector2 min;
    Vector2 max;
} BoundingBox2;

// 3D bounding box
typedef struct Bounds3D {
    Vector3 min;
    Vector3 max;
} BoundingBox3;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

//------------------------------
// 1D Splines
//------------------------------

// Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI float GetSplinePointLinear1D(float startPos, float endPos, float t);                           // Get (evaluate) spline point: Linear 1D
RSPLAPI float GetSplinePointBasis1D(float p1, float p2, float p3, float p4, float t);                  // Get (evaluate) spline point: B-Spline 1D
RSPLAPI float GetSplinePointCatmullRom1D(float p1, float p2, float p3, float p4, float t);             // Get (evaluate) spline point: Catmull-Rom 1D
RSPLAPI float GetSplinePointBezierQuad1D(float p1, float c2, float p3, float t);                       // Get (evaluate) spline point: Quadratic Bezier 1D
RSPLAPI float GetSplinePointBezierCubic1D(float p1, float c2, float c3, float p4, float t);            // Get (evaluate) spline point: Cubic Bezier 1D

// Spline inverse point functions, for evenly-spaced points on the curve
RSPLAPI void GetSplineControlBezierQuad1D(float startPos, float midPos, float endPos, float *controlPos); // Get (evaluate) spline control point: Quadratic Bezier 1D
RSPLAPI void GetSplineControlBezierCubic1D(float startPos, float oneThirdsPos, float twoThirdsPos, float endPos, float *startControlPos, float *endControlPos); // Get (evaluate) spline control points: Cubic Bezier 1D

// Spline segment slope evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI float GetSplineVelocityLinear1D(float startPos, float endPos);                                 // Get (evaluate) spline velocity: Linear 1D
RSPLAPI float GetSplineVelocityBezierQuad1D(float startPos, float controlPos, float endPos, float t);  // Get (evaluate) spline velocity: Quadratic Bezier 1D
RSPLAPI float GetSplineVelocityBezierCubic1D(float startPos, float startControlPos, float endControlPos, float endPos, float t); // Get (evaluate) spline velocity: Cubic Bezier 1D
RSPLAPI float GetSplineAccelerationBezierQuad1D(float startPos, float controlPos, float endPos);       // Get (evaluate) spline acceleration: Quadratic Bezier 1D
RSPLAPI float GetSplineAccelerationBezierCubic1D(float startPos, float startControlPos, float endControlPos, float endPos, float t); // Get (evaluate) spline acceleration: Cubic Bezier 1D
RSPLAPI float GetSplineJoltBezierCubic1D(float startPos, float startControlPos, float endControlPos, float endPos); // Get (evaluate) spline jolt: Cubic Bezier 1D

// Spline segment bounds evaluation functions
RSPLAPI BoundingBox1 GetSplineBoundsBezierLinear1D(float startPos, float endPos);                      // Get (evaluate) spline bounds range: Linear 1D
RSPLAPI BoundingBox1 GetSplineBoundsBezierQuad1D(float startPos, float controlPos, float endPos);      // Get (evaluate) spline bounds range: Quadratic Bezier 1D
RSPLAPI BoundingBox1 GetSplineBoundsBezierCubic1D(float startPos, float startControlPos, float endControlPos, float endPos); // Get (evaluate) spline bounds range: Cubic Bezier 1D

RSPLAPI float GetSplineNearestTLinear1D(float startPos, float endPos, float point);                    // Get (evaluate) nearest t value to point: Linear 1D

//------------------------------
// 2D Splines
//------------------------------

// Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI Vector2 GetSplinePointLinear2D(Vector2 startPos, Vector2 endPos, float t);                     // Get (evaluate) spline point: Linear 2D
RSPLAPI Vector2 GetSplinePointBasis2D(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t);        // Get (evaluate) spline point: B-Spline 2D
RSPLAPI Vector2 GetSplinePointCatmullRom2D(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t);   // Get (evaluate) spline point: Catmull-Rom 2D
RSPLAPI Vector2 GetSplinePointBezierQuad2D(Vector2 p1, Vector2 c2, Vector2 p3, float t);               // Get (evaluate) spline point: Quadratic Bezier 2D
RSPLAPI Vector2 GetSplinePointBezierCubic2D(Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float t);  // Get (evaluate) spline point: Cubic Bezier 2D

// Spline inverse point functions, for evenly-spaced points on the curve
RSPLAPI void GetSplineControlBezierQuad2D(Vector2 startPos, Vector2 midPos, Vector2 endPos, Vector2 *controlPos); // Get (evaluate) spline control point: Quadratic Bezier 2D
RSPLAPI void GetSplineControlBezierCubic2D(Vector2 startPos, Vector2 oneThirdsPos, Vector2 twoThirdsPos, Vector2 endPos, Vector2 *startControlPos, Vector2 *endControlPos); // Get (evaluate) spline control points: Cubic Bezier 2D

// Spline segment slope evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI Vector2 GetSplineVelocityLinear2D(Vector2 startPos, Vector2 endPos);                           // Get (evaluate) spline velocity: Linear 2D
RSPLAPI Vector2 GetSplineVelocityBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos, float t); // Get (evaluate) spline velocity: Quadratic Bezier 2D
RSPLAPI Vector2 GetSplineVelocityBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t); // Get (evaluate) spline velocity: Cubic Bezier 2D
RSPLAPI Vector2 GetSplineAccelerationBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos); // Get (evaluate) spline acceleration: Quadratic Bezier 2D
RSPLAPI Vector2 GetSplineAccelerationBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t); // Get (evaluate) spline acceleration: Cubic Bezier 2D
RSPLAPI Vector2 GetSplineJoltBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos); // Get (evaluate) spline jolt: Cubic Bezier 2D

// Spline segment bounds evaluation functions
RSPLAPI BoundingBox2 GetSplineBoundsBezierLinear2D(Vector2 startPos, Vector2 endPos);                  // Get (evaluate) spline bounds rectangle: Linear 2D
RSPLAPI BoundingBox2 GetSplineBoundsBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos); // Get (evaluate) spline bounds rectangle: Quadratic Bezier 2D
RSPLAPI BoundingBox2 GetSplineBoundsBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos); // Get (evaluate) spline bounds rectangle: Cubic Bezier 2D

RSPLAPI float GetSplineCurvatureBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t); // Get (evaluate) spline curvature: Cubic Bezier 2D
RSPLAPI float GetSplineNearestTLinear2D(Vector2 startPos, Vector2 endPos, Vector2 point);              // Get (evaluate) nearest t value to point: Linear 2D

//------------------------------
// 3D Splines
//------------------------------

// Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI Vector3 GetSplinePointLinear3D(Vector3 startPos, Vector3 endPos, float t);                     // Get (evaluate) spline point: Linear 3D
RSPLAPI Vector3 GetSplinePointBasis3D(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, float t);        // Get (evaluate) spline point: B-Spline 3D
RSPLAPI Vector3 GetSplinePointCatmullRom3D(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, float t);   // Get (evaluate) spline point: Catmull-Rom 3D
RSPLAPI Vector3 GetSplinePointBezierQuad3D(Vector3 p1, Vector3 c2, Vector3 p3, float t);               // Get (evaluate) spline point: Quadratic Bezier 3D
RSPLAPI Vector3 GetSplinePointBezierCubic3D(Vector3 p1, Vector3 c2, Vector3 c3, Vector3 p4, float t);  // Get (evaluate) spline point: Cubic Bezier 3D

// Spline inverse point functions, for evenly-spaced points on the curve
RSPLAPI void GetSplineControlBezierQuad3D(Vector3 startPos, Vector3 midPos, Vector3 endPos, Vector3 *controlPos); // Get (evaluate) spline control point: Quadratic Bezier 3D
RSPLAPI void GetSplineControlBezierCubic3D(Vector3 startPos, Vector3 oneThirdsPos, Vector3 twoThirdsPos, Vector3 endPos, Vector3 *startControlPos, Vector3 *endControlPos); // Get (evaluate) spline control points: Cubic Bezier 3D

// Spline segment slope evaluation functions, for a given t [0.0f .. 1.0f]
RSPLAPI Vector3 GetSplineVelocityLinear3D(Vector3 startPos, Vector3 endPos);                           // Get (evaluate) spline velocity: Linear 3D
RSPLAPI Vector3 GetSplineVelocityBezierQuad3D(Vector3 startPos, Vector3 controlPos, Vector3 endPos, float t); // Get (evaluate) spline velocity: Quadratic Bezier 3D
RSPLAPI Vector3 GetSplineVelocityBezierCubic3D(Vector3 startPos, Vector3 startControlPos, Vector3 endControlPos, Vector3 endPos, float t); // Get (evaluate) spline velocity: Cubic Bezier 3D
RSPLAPI Vector3 GetSplineAccelerationBezierQuad3D(Vector3 startPos, Vector3 controlPos, Vector3 endPos); // Get (evaluate) spline acceleration: Quadratic Bezier 3D
RSPLAPI Vector3 GetSplineAccelerationBezierCubic3D(Vector3 startPos, Vector3 startControlPos, Vector3 endControlPos, Vector3 endPos, float t); // Get (evaluate) spline acceleration: Cubic Bezier 3D
RSPLAPI Vector3 GetSplineJoltBezierCubic3D(Vector3 startPos, Vector3 startControlPos, Vector3 endControlPos, Vector3 endPos); // Get (evaluate) spline jolt: Cubic Bezier 3D

// Spline segment bounds evaluation functions
RSPLAPI BoundingBox3 GetSplineBoundsBezierLinear3D(Vector3 startPos, Vector3 endPos);                  // Get (evaluate) spline bounding box: Linear 3D
RSPLAPI BoundingBox3 GetSplineBoundsBezierQuad3D(Vector3 startPos, Vector3 controlPos, Vector3 endPos); // Get (evaluate) spline bounding box: Quadratic Bezier 3D
RSPLAPI BoundingBox3 GetSplineBoundsBezierCubic3D(Vector3 startPos, Vector3 startControlPos, Vector3 endControlPos, Vector3 endPos); // Get (evaluate) spline bounding box: Cubic Bezier 3D

RSPLAPI float GetSplineCurvatureBezierCubic3D(Vector3 startPos, Vector3 startControlPos, Vector3 endControlPos, Vector3 endPos, float t); // Get (evaluate) spline curvature: Cubic Bezier 3D
RSPLAPI float GetSplineNearestTLinear3D(Vector3 startPos, Vector3 endPos, Vector3 point);              // Get (evaluate) nearest t value to point: Linear 3D

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

// Get spline point for a given t [0.0f .. 1.0f], Linear
float GetSplinePointLinear1D(float startPos, float endPos, float t)
{
    float point = 0.0f;

    point = startPos*(1.0f - t) + endPos*t;

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], B-Spline
float GetSplinePointBasis1D(float p1, float p2, float p3, float p4, float t)
{
    float point = 0.0f;

    float a0 = (-p1 + 3*p2 - 3*p3 + p4)/6.0f;
    float a1 = (3*p1 - 6*p2 + 3*p3)/6.0f;
    float a2 = (-3*p1 + 3*p3)/6.0f;
    float a3 = (p1 + 4*p2 + p3)/6.0f;

    point = a3 + t*(a2 + t*(a1 + t*a0));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Catmull-Rom
float GetSplinePointCatmullRom1D(float p1, float p2, float p3, float p4, float t)
{
    float point = 0.0f;

    float q0 = (-1*t*t*t) + (2*t*t) + (-1*t);
    float q1 = (3*t*t*t) + (-5*t*t) + 2;
    float q2 = (-3*t*t*t) + (4*t*t) + t;
    float q3 = t*t*t - t*t;

    point = 0.5f*((p1*q0) + (p2*q1) + (p3*q2) + (p4*q3));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Quadratic Bezier
float GetSplinePointBezierQuad1D(float startPos, float controlPos, float endPos, float t)
{
    float point = 0.0f;

    float a = powf(1.0f - t, 2);
    float b = 2.0f*(1.0f - t)*t;
    float c = powf(t, 2);

    point = a*startPos + b*controlPos + c*endPos;

    return point;
}

// Get spline control point given evenly-spaced points on that curve, Quadratic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
void GetSplineControlBezierQuad1D(float startPos, float midPos, float endPos, float *controlPos)
{
    *controlPos = 2.0f*midPos - 0.5f*(startPos + endPos);
}

// Get spline point for a given t [0.0f .. 1.0f], Cubic Bezier
float GetSplinePointBezierCubic1D(float startPos, float startControlPos, float endControlPos, float endPos, float t)
{
    float point = 0.0f;

    float a = powf(1.0f - t, 3);
    float b = 3.0f*powf(1.0f - t, 2)*t;
    float c = 3.0f*(1.0f - t)*powf(t, 2);
    float d = powf(t, 3);

    point = a*startPos + b*startControlPos + c*endControlPos + d*endPos;

    return point;
}

// Get spline control points given evenly-spaced points on that curve, Cubic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
void GetSplineControlBezierCubic1D(float startPos, float oneThirdsPos, float twoThirdsPos, float endPos, float *startControlPos, float *endControlPos)
{
    float a = -5.0f/6.0f;
    float b = 3.0f;
    float c = -3.0f/2.0f;
    float d = 1.0f/3.0f;

    *startControlPos = a*startPos + b*oneThirdsPos + c*twoThirdsPos + d*endPos;

    *endControlPos = a*endPos + b*twoThirdsPos + c*oneThirdsPos + d*startPos;
}

// Get spline direction and speed, Linear Bezier
//
// Normalize to get the "forward" direction of the curve
float GetSplineVelocityLinear1D(float startPos, float endPos)
{
    float velocity = 0.0f;

    velocity = endPos - startPos;

    return velocity;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Quadratic Bezier
//
// Normalize to get the "forward" direction of the curve at t
float GetSplineVelocityBezierQuad1D(float startPos, float controlPos, float endPos, float t)
{
    float velocity = 0.0f;

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    velocity = a*(controlPos - startPos) + b*(endPos - controlPos);

    return velocity;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Cubic Bezier
//
// Normalize to get the "forward" direction of the curve at t
float GetSplineVelocityBezierCubic1D(float startPos, float startControlPos, float endControlPos, float endPos, float t)
{
    float velocity = 0.0f;

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    velocity = a*(startControlPos - startPos) + b*(endControlPos - startControlPos) + c*(endPos - endControlPos);

    return velocity;
}

// Get spline rate of change, Quadratic Bezier
float GetSplineAccelerationBezierQuad1D(float startPos, float controlPos, float endPos)
{
    float acceleration = 0.0f;

    acceleration = 2.0f*(endPos - 2.0f*controlPos - startPos);

    return acceleration;
}

// Get spline rate of change for a given t [0.0f .. 1.0f], Cubic Bezier
float GetSplineAccelerationBezierCubic1D(float startPos, float startControlPos, float endControlPos, float endPos, float t)
{
    float acceleration = 0.0f;

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    acceleration = a*(endControlPos - 2.0f*startControlPos + startPos) + b*(endPos - 2.0f*endControlPos + startControlPos);

    return acceleration;
}

// Get spline rate of acceleration, Cubic Bezier
float GetSplineJoltBezierCubic1D(float startPos, float startControlPos, float endControlPos, float endPos)
{
    float jolt = 0.0f;

    jolt = 6.0f*(endPos + 3.0f*(startControlPos - endControlPos) - startPos);

    return jolt;
}

// Compute spline curve bounding rectangle, Linear Bezier
BoundingBox1 GetSplineBoundsBezierLinear1D(float startPos, float endPos)
{
    float min;
    float max;

    if (startPos < endPos)
    {
        min = startPos;
        max = endPos;
    }
    else
    {
        min = endPos;
        max = startPos;
    }

    // straight line will never escape bounds

    BoundingBox1 bounds = { min, max };

    return bounds;
}

// Compute spline curve bounding rectangle, Quadratic Bezier
BoundingBox1 GetSplineBoundsBezierQuad1D(float startPos, float controlPos, float endPos)
{
    float min;
    float max;

    if (startPos < endPos)
    {
        min = startPos;
        max = endPos;
    }
    else
    {
        min = endPos;
        max = startPos;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float a = startPos - 2.0f*controlPos + endPos;
    float b = 2.0f*(controlPos - startPos);
    float c = startPos;

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
            float point = GetSplinePointBezierQuad1D(startPos, controlPos, endPos, t[i]);

            if (point < min) min = point;
            if (point > max) max = point;
        }
    }

    BoundingBox1 bounds = { min, max };

    return bounds;
}

// Compute spline curve bounding rectangle, Cubic Bezier
BoundingBox1 GetSplineBoundsBezierCubic1D(float startPos, float startControlPos, float endControlPos, float endPos)
{
    float min;
    float max;

    if (startPos < endPos)
    {
        min = startPos;
        max = endPos;
    }
    else
    {
        min = endPos;
        max = startPos;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float a = -3.0f*startPos + 9.0f*startControlPos - 9.0f*endControlPos + 3.0f*endPos;
    float b = 6.0f*startPos - 12.0f*startControlPos + 6.0f*endControlPos;
    float c = -3.0f*startPos + 3.0f*startControlPos;

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
            float point = GetSplinePointBezierCubic1D(startPos, startControlPos, endControlPos, endPos, t[i]);

            if (point < min) min = point;
            if (point > max) max = point;
        }
    }
    // straight line will never escape bounds

    BoundingBox1 bounds = { min, max };

    return bounds;
}

// Get value of t (unbounded) for the point on the line closest to a given position
float GetSplineNearestTLinear1D(float startPos, float endPos, float point)
{
    float edge = 0.0f;
    edge = endPos - startPos;

    float diff = 0.0f;
    diff = point - startPos;

    float t = (edge*diff)/(edge*edge);

    return t;
}

#endif // RSPLINES_IMPLEMENTATION

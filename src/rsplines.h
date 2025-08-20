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
*       - "GetSplineNearestT...()" and "GetSplineLength...()" functions currently only available for
*         Linear splines due to no closed definition existing for higher spline degree
*
*   CONFIGURATION:
*       #define RSPLINES_IMPLEMENTATION
*           Generates the implementation of the library into the included file
*           If not defined, the library is in header only mode and can be included in other headers
*           or source files without problems. But only ONE file should hold the implementation
*
*       #define RSPLINES_1D
*           Includes 1D spline functions
*
*       #define RSPLINES_3D
*           Includes 3D spline functions
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

#include "raylib.h"  // Vector2, Vector3

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

#ifndef RL_VECTOR2_TYPE
#define RL_VECTOR2_TYPE
// Vector2, 2 components
typedef struct Vector2 {
    float x;
    float y;
} Vector2;
#endif // RL_VECTOR2_TYPE

#ifndef RL_VECTOR3_TYPE
#define RL_VECTOR3_TYPE
// Vector3, 3 components
typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;
#endif // RL_VECTOR3_TYPE

// 1D bounds (range)
typedef struct BoundingBox1 {
    float min;
    float max;
} BoundingBox1;

// 2D bounds (rectangle)
typedef struct BoundingBox2 {
    Vector2 min;
    Vector2 max;
} BoundingBox2;

// 3D bounds (box)
typedef struct BoundingBox3 {
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

#if defined(RSPLINES_1D)
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

// Spline segment length evaluation functions
RSPLAPI float GetSplineLengthSqrLinear1D(float startPos, float endPos);                                // Get (evaluate) squared length of spline: Linear 1D
RSPLAPI float GetSplineLengthLinear1D(float startPos, float endPos);                                   // Get (evaluate) length of spline: Linear 1D
RSPLAPI float GetSubSplineLengthSqrLinear1D(float startPos, float endPos, float t0, float t1);         // Get (evaluate) squared length of subspline: Linear 1D
RSPLAPI float GetSubSplineLengthLinear1D(float startPos, float endPos, float t0, float t1);            // Get (evaluate) length of subspline: Linear 1D

RSPLAPI float GetSplineNearestTLinear1D(float startPos, float endPos, float point);                    // Get (evaluate) nearest t value to point: Linear 1D

#endif // RSPLINES_1D

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
RSPLAPI Vector2 GetSplineTangentLinear2D(Vector2 startPos, Vector2 endPos);                            // Get (evaluate) spline tangent: Linear 2D
RSPLAPI Vector2 GetSplineNormalLinear2D(Vector2 startPos, Vector2 endPos);                             // Get (evaluate) spline normal: Linear 2D
RSPLAPI Vector2 GetSplineTangentBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos, float t); // Get (evaluate) spline tangent: Quadratic Bezier 2D
RSPLAPI Vector2 GetSplineNormalBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos, float t); // Get (evaluate) spline normal: Quadratic Bezier 2D
RSPLAPI Vector2 GetSplineTangentBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t); // Get (evaluate) spline tangent: Cubic Bezier 2D
RSPLAPI Vector2 GetSplineNormalBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t); // Get (evaluate) spline normal: Cubic Bezier 2D
RSPLAPI Vector2 GetSplineAccelerationBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos); // Get (evaluate) spline acceleration: Quadratic Bezier 2D
RSPLAPI Vector2 GetSplineAccelerationBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t); // Get (evaluate) spline acceleration: Cubic Bezier 2D
RSPLAPI Vector2 GetSplineJoltBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos); // Get (evaluate) spline jolt: Cubic Bezier 2D

// Spline segment bounds evaluation functions
RSPLAPI BoundingBox2 GetSplineBoundsBezierLinear2D(Vector2 startPos, Vector2 endPos);                  // Get (evaluate) spline bounds rectangle: Linear 2D
RSPLAPI BoundingBox2 GetSplineBoundsBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos); // Get (evaluate) spline bounds rectangle: Quadratic Bezier 2D
RSPLAPI BoundingBox2 GetSplineBoundsBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos); // Get (evaluate) spline bounds rectangle: Cubic Bezier 2D

// Spline segment length evaluation functions
RSPLAPI float GetSplineLengthSqrLinear2D(Vector2 startPos, Vector2 endPos);                            // Get (evaluate) squared length of spline: Linear 2D
RSPLAPI float GetSplineLengthLinear2D(Vector2 startPos, Vector2 endPos);                               // Get (evaluate) length of spline: Linear 2D
RSPLAPI float GetSubSplineLengthSqrLinear2D(Vector2 startPos, Vector2 endPos, float t0, float t1);     // Get (evaluate) squared length of subspline: Linear 2D
RSPLAPI float GetSubSplineLengthLinear2D(Vector2 startPos, Vector2 endPos, float t0, float t1);        // Get (evaluate) length of subspline: Linear 2D

RSPLAPI float GetSplineCurvatureBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t); // Get (evaluate) spline curvature: Cubic Bezier 2D
RSPLAPI float GetSplineNearestTLinear2D(Vector2 startPos, Vector2 endPos, Vector2 point);              // Get (evaluate) nearest t value to point: Linear 2D

#if defined(RSPLINES_3D)
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

// Spline segment length evaluation functions
RSPLAPI float GetSplineLengthSqrLinear3D(Vector3 startPos, Vector3 endPos);                            // Get (evaluate) squared length of spline: Linear 3D
RSPLAPI float GetSplineLengthLinear3D(Vector3 startPos, Vector3 endPos);                               // Get (evaluate) length of spline: Linear 3D
RSPLAPI float GetSubSplineLengthSqrLinear3D(Vector3 startPos, Vector3 endPos, float t0, float t1);     // Get (evaluate) squared length of subspline: Linear 3D
RSPLAPI float GetSubSplineLengthLinear3D(Vector3 startPos, Vector3 endPos, float t0, float t1);        // Get (evaluate) length of subspline: Linear 3D

RSPLAPI float GetSplineNearestTLinear3D(Vector3 startPos, Vector3 endPos, Vector3 point);              // Get (evaluate) nearest t value to point: Linear 3D

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

// Get (evaluate) square of length of spline along a t-value range: Linear 1D
float GetSplineLengthSqrLinear1D(float startPos, float endPos)
{
    float lengthSqr = 0.0f;

    lengthSqr = (endPos - startPos)*(endPos - startPos);

    return lengthSqr;
}

// Get (evaluate) square of length of spline along a t-value range: Linear 1D
float GetSplineLengthLinear1D(float startPos, float endPos)
{
    float length = 0.0f;

    float lengthSqr = (endPos - startPos)*(endPos - startPos);

    length = sqrtf(lengthSqr);

    return length;
}

// Get (evaluate) square of length of subspline: Linear 1D
float GetSubSplineLengthSqrLinear1D(float startPos, float endPos, float t0, float t1)
{
    float lengthSqr = 0.0f;

    float dx = (t0 - t1)*startPos + (t1 - t0)*endPos;

    lengthSqr = dx*dx;

    return lengthSqr;
}

// Get (evaluate) length of subspline: Linear 1D
float GetSubSplineLengthLinear1D(float startPos, float endPos, float t0, float t1)
{
    float length = 0.0f;

    float dx = startPos*(t0 - t1) + endPos*(t1 - t0);

    length = sqrtf(dx*dx);

    return length;
}

// Get value of t (unbounded) for the point on the line closest to a given position
// NOTE 1: If the return is less than 0.0f or greater than 1.0f, the nearest point may be in a different segment
// NOTE 2: Return can be clamped [0.0f .. 1.0f] to snap the point to the start/end of the spline
float GetSplineNearestTLinear1D(float startPos, float endPos, float point)
{
    float t = 0.0f;

    t = (point - startPos)/(endPos - startPos);

    return t;
}

#endif // RSPLINES_1D

// Get spline point for a given t [0.0f .. 1.0f], Linear
Vector2 GetSplinePointLinear2D(Vector2 startPos, Vector2 endPos, float t)
{
    Vector2 point = { 0 };

    point.x = startPos.x*(1.0f - t) + endPos.x*t;
    point.y = startPos.y*(1.0f - t) + endPos.y*t;

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], B-Spline
Vector2 GetSplinePointBasis2D(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t)
{
    Vector2 point = { 0 };

    float a0 = (-p1.x + 3*p2.x - 3*p3.x + p4.x)/6.0f;
    float a1 = (3*p1.x - 6*p2.x + 3*p3.x)/6.0f;
    float a2 = (-3*p1.x + 3*p3.x)/6.0f;
    float a3 = (p1.x + 4*p2.x + p3.x)/6.0f;

    float b0 = (-p1.y + 3*p2.y - 3*p3.y + p4.y)/6.0f;
    float b1 = (3*p1.y - 6*p2.y + 3*p3.y)/6.0f;
    float b2 = (-3*p1.y + 3*p3.y)/6.0f;
    float b3 = (p1.y + 4*p2.y + p3.y)/6.0f;

    point.x = a3 + t*(a2 + t*(a1 + t*a0));
    point.y = b3 + t*(b2 + t*(b1 + t*b0));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Catmull-Rom
Vector2 GetSplinePointCatmullRom2D(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t)
{
    Vector2 point = { 0 };

    float q0 = (-1*t*t*t) + (2*t*t) + (-1*t);
    float q1 = (3*t*t*t) + (-5*t*t) + 2;
    float q2 = (-3*t*t*t) + (4*t*t) + t;
    float q3 = t*t*t - t*t;

    point.x = 0.5f*((p1.x*q0) + (p2.x*q1) + (p3.x*q2) + (p4.x*q3));
    point.y = 0.5f*((p1.y*q0) + (p2.y*q1) + (p3.y*q2) + (p4.y*q3));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Quadratic Bezier
Vector2 GetSplinePointBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos, float t)
{
    Vector2 point = { 0 };

    float a = powf(1.0f - t, 2);
    float b = 2.0f*(1.0f - t)*t;
    float c = powf(t, 2);

    point.y = a*startPos.y + b*controlPos.y + c*endPos.y;
    point.x = a*startPos.x + b*controlPos.x + c*endPos.x;

    return point;
}

// Get spline control point given evenly-spaced points on that curve, Quadratic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
void GetSplineControlBezierQuad2D(Vector2 startPos, Vector2 midPos, Vector2 endPos, Vector2 *controlPos)
{
    controlPos->y = 2.0f*midPos.y - 0.5f*(startPos.y + endPos.y);
    controlPos->x = 2.0f*midPos.x - 0.5f*(startPos.x + endPos.x);
}

// Get spline point for a given t [0.0f .. 1.0f], Cubic Bezier
Vector2 GetSplinePointBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t)
{
    Vector2 point = { 0 };

    float a = powf(1.0f - t, 3);
    float b = 3.0f*powf(1.0f - t, 2)*t;
    float c = 3.0f*(1.0f - t)*powf(t, 2);
    float d = powf(t, 3);

    point.y = a*startPos.y + b*startControlPos.y + c*endControlPos.y + d*endPos.y;
    point.x = a*startPos.x + b*startControlPos.x + c*endControlPos.x + d*endPos.x;

    return point;
}

// Get spline control points given evenly-spaced points on that curve, Cubic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
void GetSplineControlBezierCubic2D(Vector2 startPos, Vector2 oneThirdsPos, Vector2 twoThirdsPos, Vector2 endPos, Vector2 *startControlPos, Vector2 *endControlPos)
{
    float a = -5.0f/6.0f;
    float b = 3.0f;
    float c = -3.0f/2.0f;
    float d = 1.0f/3.0f;

    startControlPos->x = a*startPos.x + b*oneThirdsPos.x + c*twoThirdsPos.x + d*endPos.x;
    startControlPos->y = a*startPos.y + b*oneThirdsPos.y + c*twoThirdsPos.y + d*endPos.y;

    endControlPos->x = a*endPos.x + b*twoThirdsPos.x + c*oneThirdsPos.x + d*startPos.x;
    endControlPos->y = a*endPos.y + b*twoThirdsPos.y + c*oneThirdsPos.y + d*startPos.y;
}

// Get spline direction and speed, Linear Bezier
//
// Normalize to get the "forward" direction of the curve
Vector2 GetSplineVelocityLinear2D(Vector2 startPos, Vector2 endPos)
{
    Vector2 velocity = { 0 };

    velocity.x = endPos.x - startPos.x;
    velocity.y = endPos.y - startPos.y;

    return velocity;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Quadratic Bezier
//
// Normalize to get the "forward" direction of the curve at t
Vector2 GetSplineVelocityBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos, float t)
{
    Vector2 velocity = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    velocity.x = a*(controlPos.x - startPos.x) + b*(endPos.x - controlPos.x);
    velocity.y = a*(controlPos.y - startPos.y) + b*(endPos.y - controlPos.y);

    return velocity;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Cubic Bezier
//
// Normalize to get the "forward" direction of the curve at t
Vector2 GetSplineVelocityBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t)
{
    Vector2 velocity = { 0 };

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    velocity.x = a*(startControlPos.x - startPos.x) + b*(endControlPos.x - startControlPos.x) + c*(endPos.x - endControlPos.x);
    velocity.y = a*(startControlPos.y - startPos.y) + b*(endControlPos.y - startControlPos.y) + c*(endPos.y - endControlPos.y);

    return velocity;
}

// Get (evaluate) spline tangent: Linear 2D
Vector2 GetSplineTangentLinear2D(Vector2 startPos, Vector2 endPos)
{
    Vector2 tangent = { 0 };

    tangent.x = endPos.x - startPos.x;
    tangent.y = endPos.y - startPos.y;

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    return tangent;
}

// Get (evaluate) spline normal: Linear 2D
Vector2 GetSplineNormalLinear2D(Vector2 startPos, Vector2 endPos)
{
    Vector2 normal = { 0 };
    Vector2 tangent = { 0 };

    tangent.x = endPos.x - startPos.x;
    tangent.y = endPos.y - startPos.y;

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    normal.x = tangent.y;
    normal.y = -tangent.x;

    return normal;
}

// Get (evaluate) spline tangent: Quadratic Bezier 2D
Vector2 GetSplineTangentBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos, float t)
{
    Vector2 tangent = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    tangent.x = a*(controlPos.x - startPos.x) + b*(endPos.x - controlPos.x);
    tangent.y = a*(controlPos.y - startPos.y) + b*(endPos.y - controlPos.y);

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    return tangent;
}

// Get (evaluate) spline normal: Quadratic Bezier 2D
Vector2 GetSplineNormalBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos, float t)
{
    Vector2 normal = { 0 };
    Vector2 tangent = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    tangent.x = a*(controlPos.x - startPos.x) + b*(endPos.x - controlPos.x);
    tangent.y = a*(controlPos.y - startPos.y) + b*(endPos.y - controlPos.y);

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    normal.x = tangent.y;
    normal.y = -tangent.x;

    return normal;
}

// Get (evaluate) spline tangent: Cubic Bezier 2D
Vector2 GetSplineTangentBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t)
{
    Vector2 tangent = { 0 };

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    tangent.x = a*(startControlPos.x - startPos.x) + b*(endControlPos.x - startControlPos.x) + c*(endPos.x - endControlPos.x);
    tangent.y = a*(startControlPos.y - startPos.y) + b*(endControlPos.y - startControlPos.y) + c*(endPos.y - endControlPos.y);

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    return tangent;
}

// Get (evaluate) spline normal: Cubic Bezier 2D
Vector2 GetSplineNormalBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t)
{
    Vector2 tangent = { 0 };
    Vector2 normal = { 0 };

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    tangent.x = a*(startControlPos.x - startPos.x) + b*(endControlPos.x - startControlPos.x) + c*(endPos.x - endControlPos.x);
    tangent.y = a*(startControlPos.y - startPos.y) + b*(endControlPos.y - startControlPos.y) + c*(endPos.y - endControlPos.y);

    float invSpeed = 1.0f/sqrtf(tangent.x*tangent.x + tangent.y*tangent.y);

    tangent.x *= invSpeed;
    tangent.y *= invSpeed;

    normal.x = tangent.y;
    normal.y = -tangent.x;

    return normal;
}

// Get spline rate of change, Quadratic Bezier
Vector2 GetSplineAccelerationBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos)
{
    Vector2 acceleration = { 0 };

    acceleration.x = 2.0f*(endPos.x - 2.0f*controlPos.x - startPos.x);
    acceleration.y = 2.0f*(endPos.y - 2.0f*controlPos.y - startPos.y);

    return acceleration;
}

// Get spline rate of change for a given t [0.0f .. 1.0f], Cubic Bezier
Vector2 GetSplineAccelerationBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t)
{
    Vector2 acceleration = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    acceleration.x = a*(endControlPos.x - 2.0f*startControlPos.x + startPos.x) + b*(endPos.x - 2.0f*endControlPos.x + startControlPos.x);
    acceleration.y = a*(endControlPos.y - 2.0f*startControlPos.y + startPos.y) + b*(endPos.y - 2.0f*endControlPos.y + startControlPos.y);

    return acceleration;
}

// Get spline rate of acceleration, Cubic Bezier
Vector2 GetSplineJoltBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos)
{
    Vector2 jolt = { 0 };

    jolt.x = 6.0f*(endPos.x + 3.0f*(startControlPos.x - endControlPos.x) - startPos.x);
    jolt.y = 6.0f*(endPos.y + 3.0f*(startControlPos.y - endControlPos.y) - startPos.y);

    return jolt;
}

// Compute spline curve bounding rectangle, Linear Bezier
BoundingBox2 GetSplineBoundsBezierLinear2D(Vector2 startPos, Vector2 endPos)
{
    float xMin;
    float yMin;
    float xMax;
    float yMax;

    if (startPos.x < endPos.x)
    {
        xMin = startPos.x;
        xMax = endPos.x;
    }
    else
    {
        xMin = endPos.x;
        xMax = startPos.x;
    }

    if (startPos.y < endPos.y)
    {
        yMin = startPos.y;
        yMax = endPos.y;
    }
    else
    {
        yMin = endPos.y;
        yMax = startPos.y;
    }

    // straight line will never escape bounds

    BoundingBox2 bounds = { { xMin, yMin }, { xMax, yMax } };

    return bounds;
}

// Compute spline curve bounding rectangle, Quadratic Bezier
BoundingBox2 GetSplineBoundsBezierQuad2D(Vector2 startPos, Vector2 controlPos, Vector2 endPos)
{
    float xMin;
    float yMin;
    float xMax;
    float yMax;

    if (startPos.x < endPos.x)
    {
        xMin = startPos.x;
        xMax = endPos.x;
    }
    else
    {
        xMin = endPos.x;
        xMax = startPos.x;
    }

    if (startPos.y < endPos.y)
    {
        yMin = startPos.y;
        yMax = endPos.y;
    }
    else
    {
        yMin = endPos.y;
        yMax = startPos.y;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float startPosA[] = { startPos.x, startPos.y };
    float controlPosA[] = { controlPos.x, controlPos.y };
    float endPosA[] = { endPos.x, endPos.y };

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
                Vector2 point = GetSplinePointBezierQuad2D(startPos, controlPos, endPos, t[j]);

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
BoundingBox2 GetSplineBoundsBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos)
{
    float xMin;
    float yMin;
    float xMax;
    float yMax;

    if (startPos.x < endPos.x)
    {
        xMin = startPos.x;
        xMax = endPos.x;
    }
    else
    {
        xMin = endPos.x;
        xMax = startPos.x;
    }

    if (startPos.y < endPos.y)
    {
        yMin = startPos.y;
        yMax = endPos.y;
    }
    else
    {
        yMin = endPos.y;
        yMax = startPos.y;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float startPosA[] = { startPos.x, startPos.y };
    float startControlPosA[] = { startControlPos.x, startControlPos.y };
    float endControlPosA[] = { endControlPos.x, endControlPos.y };
    float endPosA[] = { endPos.x, endPos.y };

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
                Vector2 point = GetSplinePointBezierCubic2D(startPos, startControlPos, endControlPos, endPos, t[j]);

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
float GetSplineLengthSqrLinear2D(Vector2 startPos, Vector2 endPos)
{
    float lengthSqr = 0.0f;

    float dx = endPos.x - startPos.x;
    float dy = endPos.y - startPos.y;

    lengthSqr = dx*dx + dy*dy;

    return lengthSqr;
}

// Get (evaluate) length of spline: Linear 2D
float GetSplineLengthLinear2D(Vector2 startPos, Vector2 endPos)
{
    float length = 0.0f;

    float dx = endPos.x - startPos.x;
    float dy = endPos.y - startPos.y;

    length = sqrtf(dx*dx + dy*dy);

    return length;
}

// Get (evaluate) squared length of subspline: Linear 2D
float GetSubSplineLengthSqrLinear2D(Vector2 startPos, Vector2 endPos, float t0, float t1)
{
    float lengthSqr = 0.0f;

    float a = t0 - t1;
    float b = t1 - t0;

    float dx = a*startPos.x + b*endPos.x;
    float dy = a*startPos.y + b*endPos.y;

    lengthSqr = dx*dx + dy*dy;

    return lengthSqr;
}

// Get (evaluate) length of subspline: Linear 2D
float GetSubSplineLengthLinear2D(Vector2 startPos, Vector2 endPos, float t0, float t1)
{
    float length = 0.0f;

    float a = t0 - t1;
    float b = t1 - t0;

    float dx = a*startPos.x + b*endPos.x;
    float dy = a*startPos.y + b*endPos.y;

    length = sqrtf(dx*dx + dy*dy);

    return length;
}

// Reciprocal radius (or "radians per meter") for a given t [0.0f .. 1.0f], Cubic Bezier
float GetSplineCurvatureBezierCubic2D(Vector2 startPos, Vector2 startControlPos, Vector2 endControlPos, Vector2 endPos, float t)
{
    float curvature = 0.0f;

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    Vector2 velocity = { 0 };

    velocity.x = a*(startControlPos.x - startPos.x) + b*(endControlPos.x - startControlPos.x) + c*(endPos.x - endControlPos.x);
    velocity.y = a*(startControlPos.y - startPos.y) + b*(endControlPos.y - startControlPos.y) + c*(endPos.y - endControlPos.y);

    a = 2.0f*(1.0f - t);
    b = 2.0f*t;

    Vector2 acceleration = { 0 };

    acceleration.x = a*(endControlPos.x - 2.0f*startControlPos.x + startPos.x) + b*(endPos.x - 2.0f*endControlPos.x + startControlPos.x);
    acceleration.y = a*(endControlPos.y - 2.0f*startControlPos.y + startPos.y) + b*(endPos.y - 2.0f*endControlPos.y + startControlPos.y);

    curvature = (velocity.x*acceleration.y - velocity.y*acceleration.x)/powf(sqrtf(velocity.x*velocity.x + velocity.y*velocity.y), 3);

    return curvature;
}

// Get value of t (unbounded) for the point on the line closest to a given position
// NOTE 1: If the return is less than 0.0f or greater than 1.0f, the nearest point may be in a different segment
// NOTE 2: Return can be clamped [0.0f .. 1.0f] to snap the point to the start/end of the spline
float GetSplineNearestTLinear2D(Vector2 startPos, Vector2 endPos, Vector2 point)
{
    Vector2 edge = { 0 };
    edge.x = endPos.x - startPos.x;
    edge.y = endPos.y - startPos.y;

    Vector2 diff = { 0 };
    diff.x = point.x - startPos.x;
    diff.y = point.y - startPos.y;

    float t = (edge.x*diff.x + edge.y*diff.y)/(edge.x*edge.x + edge.y*edge.y);

    return t;
}

#if defined(RSPLINES_3D)

// Get spline point for a given t [0.0f .. 1.0f], Linear
Vector3 GetSplinePointLinear3D(Vector3 startPos, Vector3 endPos, float t)
{
    Vector3 point = { 0 };

    point.x = startPos.x*(1.0f - t) + endPos.x*t;
    point.y = startPos.y*(1.0f - t) + endPos.y*t;
    point.z = startPos.z*(1.0f - t) + endPos.z*t;

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], B-Spline
Vector3 GetSplinePointBasis3D(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, float t)
{
    Vector3 point = { 0 };

    float a0 = (-p1.x + 3*p2.x - 3*p3.x + p4.x)/6.0f;
    float a1 = (3*p1.x - 6*p2.x + 3*p3.x)/6.0f;
    float a2 = (-3*p1.x + 3*p3.x)/6.0f;
    float a3 = (p1.x + 4*p2.x + p3.x)/6.0f;

    float b0 = (-p1.y + 3*p2.y - 3*p3.y + p4.y)/6.0f;
    float b1 = (3*p1.y - 6*p2.y + 3*p3.y)/6.0f;
    float b2 = (-3*p1.y + 3*p3.y)/6.0f;
    float b3 = (p1.y + 4*p2.y + p3.y)/6.0f;

    float c0 = (-p1.z + 3*p2.z - 3*p3.z + p4.z)/6.0f;
    float c1 = (3*p1.z - 6*p2.z + 3*p3.z)/6.0f;
    float c2 = (-3*p1.z + 3*p3.z)/6.0f;
    float c3 = (p1.z + 4*p2.z + p3.z)/6.0f;

    point.x = a3 + t*(a2 + t*(a1 + t*a0));
    point.y = b3 + t*(b2 + t*(b1 + t*b0));
    point.z = c3 + t*(c2 + t*(c1 + t*c0));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Catmull-Rom
Vector3 GetSplinePointCatmullRom3D(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, float t)
{
    Vector3 point = { 0 };

    float q0 = (-1*t*t*t) + (2*t*t) + (-1*t);
    float q1 = (3*t*t*t) + (-5*t*t) + 2;
    float q2 = (-3*t*t*t) + (4*t*t) + t;
    float q3 = t*t*t - t*t;

    point.x = 0.5f*((p1.x*q0) + (p2.x*q1) + (p3.x*q2) + (p4.x*q3));
    point.y = 0.5f*((p1.y*q0) + (p2.y*q1) + (p3.y*q2) + (p4.y*q3));
    point.z = 0.5f*((p1.z*q0) + (p2.z*q1) + (p3.z*q2) + (p4.z*q3));

    return point;
}

// Get spline point for a given t [0.0f .. 1.0f], Quadratic Bezier
Vector3 GetSplinePointBezierQuad3D(Vector3 startPos, Vector3 controlPos, Vector3 endPos, float t)
{
    Vector3 point = { 0 };

    float a = powf(1.0f - t, 2);
    float b = 2.0f*(1.0f - t)*t;
    float c = powf(t, 2);

    point.x = a*startPos.x + b*controlPos.x + c*endPos.x;
    point.y = a*startPos.y + b*controlPos.y + c*endPos.y;
    point.z = a*startPos.z + b*controlPos.z + c*endPos.z;

    return point;
}

// Get spline control point given evenly-spaced points on that curve, Quadratic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
void GetSplineControlBezierQuad3D(Vector3 startPos, Vector3 midPos, Vector3 endPos, Vector3 *controlPos)
{
    controlPos->x = 2.0f*midPos.x - 0.5f*(startPos.x + endPos.x);
    controlPos->y = 2.0f*midPos.y - 0.5f*(startPos.y + endPos.y);
    controlPos->z = 2.0f*midPos.z - 0.5f*(startPos.z + endPos.z);
}

// Get spline point for a given t [0.0f .. 1.0f], Cubic Bezier
Vector3 GetSplinePointBezierCubic3D(Vector3 startPos, Vector3 startControlPos, Vector3 endControlPos, Vector3 endPos, float t)
{
    Vector3 point = { 0 };

    float a = powf(1.0f - t, 3);
    float b = 3.0f*powf(1.0f - t, 2)*t;
    float c = 3.0f*(1.0f - t)*powf(t, 2);
    float d = powf(t, 3);

    point.x = a*startPos.x + b*startControlPos.x + c*endControlPos.x + d*endPos.x;
    point.y = a*startPos.y + b*startControlPos.y + c*endControlPos.y + d*endPos.y;
    point.z = a*startPos.z + b*startControlPos.z + c*endControlPos.z + d*endPos.z;

    return point;
}

// Get spline control points given evenly-spaced points on that curve, Cubic Bezier
// NOTE: Assumes startPos has 0 entry velocity and endPos has 0 exit velocity
void GetSplineControlBezierCubic3D(Vector3 startPos, Vector3 oneThirdsPos, Vector3 twoThirdsPos, Vector3 endPos, Vector3 *startControlPos, Vector3 *endControlPos)
{
    float a = -5.0f/6.0f;
    float b = 3.0f;
    float c = -3.0f/2.0f;
    float d = 1.0f/3.0f;

    startControlPos->x = a*startPos.x + b*oneThirdsPos.x + c*twoThirdsPos.x + d*endPos.x;
    startControlPos->y = a*startPos.y + b*oneThirdsPos.y + c*twoThirdsPos.y + d*endPos.y;
    startControlPos->z = a*startPos.z + b*oneThirdsPos.z + c*twoThirdsPos.z + d*endPos.z;

    endControlPos->x = a*endPos.x + b*twoThirdsPos.x + c*oneThirdsPos.x + d*startPos.x;
    endControlPos->y = a*endPos.y + b*twoThirdsPos.y + c*oneThirdsPos.y + d*startPos.y;
    endControlPos->z = a*endPos.z + b*twoThirdsPos.z + c*oneThirdsPos.z + d*startPos.z;
}

// Get spline direction and speed, Linear Bezier
//
// Normalize to get the "forward" direction of the curve
Vector3 GetSplineVelocityLinear3D(Vector3 startPos, Vector3 endPos)
{
    Vector3 velocity = { 0 };

    velocity.x = endPos.x - startPos.x;
    velocity.y = endPos.y - startPos.y;
    velocity.z = endPos.z - startPos.z;

    return velocity;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Quadratic Bezier
//
// Normalize to get the "forward" direction of the curve at t
Vector3 GetSplineVelocityBezierQuad3D(Vector3 startPos, Vector3 controlPos, Vector3 endPos, float t)
{
    Vector3 velocity = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    velocity.x = a*(controlPos.x - startPos.x) + b*(endPos.x - controlPos.x);
    velocity.y = a*(controlPos.y - startPos.y) + b*(endPos.y - controlPos.y);
    velocity.z = a*(controlPos.z - startPos.z) + b*(endPos.z - controlPos.z);

    return velocity;
}

// Get spline direction and speed for a given t [0.0f .. 1.0f], Cubic Bezier
//
// Normalize to get the "forward" direction of the curve at t
Vector3 GetSplineVelocityBezierCubic3D(Vector3 startPos, Vector3 startControlPos, Vector3 endControlPos, Vector3 endPos, float t)
{
    Vector3 velocity = { 0 };

    float a = 3.0f*powf(1.0f - t, 2);
    float b = 6.0f*(1.0f - t)*t;
    float c = 3.0f*t*t;

    velocity.x = a*(startControlPos.x - startPos.x) + b*(endControlPos.x - startControlPos.x) + c*(endPos.x - endControlPos.x);
    velocity.y = a*(startControlPos.y - startPos.y) + b*(endControlPos.y - startControlPos.y) + c*(endPos.y - endControlPos.y);
    velocity.z = a*(startControlPos.z - startPos.z) + b*(endControlPos.z - startControlPos.z) + c*(endPos.z - endControlPos.z);

    return velocity;
}

// Get spline rate of change, Quadratic Bezier
Vector3 GetSplineAccelerationBezierQuad3D(Vector3 startPos, Vector3 controlPos, Vector3 endPos)
{
    Vector3 acceleration = { 0 };

    acceleration.x = 2.0f*(endPos.x - 2.0f*controlPos.x - startPos.x);
    acceleration.y = 2.0f*(endPos.y - 2.0f*controlPos.y - startPos.y);
    acceleration.z = 2.0f*(endPos.z - 2.0f*controlPos.z - startPos.z);

    return acceleration;
}

// Get spline rate of change for a given t [0.0f .. 1.0f], Cubic Bezier
Vector3 GetSplineAccelerationBezierCubic3D(Vector3 startPos, Vector3 startControlPos, Vector3 endControlPos, Vector3 endPos, float t)
{
    Vector3 acceleration = { 0 };

    float a = 2.0f*(1.0f - t);
    float b = 2.0f*t;

    acceleration.x = a*(endControlPos.x - 2.0f*startControlPos.x + startPos.x) + b*(endPos.x - 2.0f*endControlPos.x + startControlPos.x);
    acceleration.y = a*(endControlPos.y - 2.0f*startControlPos.y + startPos.y) + b*(endPos.y - 2.0f*endControlPos.y + startControlPos.y);
    acceleration.z = a*(endControlPos.z - 2.0f*startControlPos.z + startPos.z) + b*(endPos.z - 2.0f*endControlPos.z + startControlPos.z);

    return acceleration;
}

// Get spline rate of acceleration, Cubic Bezier
Vector3 GetSplineJoltBezierCubic3D(Vector3 startPos, Vector3 startControlPos, Vector3 endControlPos, Vector3 endPos)
{
    Vector3 jolt = { 0 };

    jolt.x = 6.0f*(endPos.x + 3.0f*(startControlPos.x - endControlPos.x) - startPos.x);
    jolt.y = 6.0f*(endPos.y + 3.0f*(startControlPos.y - endControlPos.y) - startPos.y);
    jolt.z = 6.0f*(endPos.z + 3.0f*(startControlPos.z - endControlPos.z) - startPos.z);

    return jolt;
}

// Compute spline curve bounding rectangle, Linear Bezier
BoundingBox3 GetSplineBoundsBezierLinear3D(Vector3 startPos, Vector3 endPos)
{
    float xMin, yMin, zMin;
    float xMax, yMax, zMax;

    if (startPos.x < endPos.x)
    {
        xMin = startPos.x;
        xMax = endPos.x;
    }
    else
    {
        xMin = endPos.x;
        xMax = startPos.x;
    }

    if (startPos.y < endPos.y)
    {
        yMin = startPos.y;
        yMax = endPos.y;
    }
    else
    {
        yMin = endPos.y;
        yMax = startPos.y;
    }

    if (startPos.z < endPos.z)
    {
        zMin = startPos.z;
        zMax = endPos.z;
    }
    else
    {
        zMin = endPos.z;
        zMax = startPos.z;
    }

    // straight line will never escape bounds

    BoundingBox3 bounds = { { xMin, yMin, zMin }, { xMax, yMax, zMax } };

    return bounds;
}



// Compute spline curve bounding rectangle, Quadratic Bezier
BoundingBox3 GetSplineBoundsBezierQuad3D(Vector3 startPos, Vector3 controlPos, Vector3 endPos)
{
    float xMin, yMin, zMin;
    float xMax, yMax, zMax;

    if (startPos.x < endPos.x)
    {
        xMin = startPos.x;
        xMax = endPos.x;
    }
    else
    {
        xMin = endPos.x;
        xMax = startPos.x;
    }

    if (startPos.y < endPos.y)
    {
        yMin = startPos.y;
        yMax = endPos.y;
    }
    else
    {
        yMin = endPos.y;
        yMax = startPos.y;
    }

    if (startPos.z < endPos.z)
    {
        zMin = startPos.z;
        zMax = endPos.z;
    }
    else
    {
        zMin = endPos.z;
        zMax = startPos.z;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float startPosA[] = { startPos.x, startPos.y, startPos.z };
    float controlPosA[] = { controlPos.x, controlPos.y, controlPos.z };
    float endPosA[] = { endPos.x, endPos.y, endPos.z };

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
                Vector3 point = GetSplinePointBezierQuad3D(startPos, controlPos, endPos, t[j]);

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
BoundingBox3 GetSplineBoundsBezierCubic3D(Vector3 startPos, Vector3 startControlPos, Vector3 endControlPos, Vector3 endPos)
{
    float xMin;
    float yMin;
    float zMin;
    float xMax;
    float yMax;
    float zMax;

    if (startPos.x < endPos.x)
    {
        xMin = startPos.x;
        xMax = endPos.x;
    }
    else
    {
        xMin = endPos.x;
        xMax = startPos.x;
    }

    if (startPos.y < endPos.y)
    {
        yMin = startPos.y;
        yMax = endPos.y;
    }
    else
    {
        yMin = endPos.y;
        yMax = startPos.y;
    }

    if (startPos.z < endPos.z)
    {
        zMin = startPos.z;
        zMax = endPos.z;
    }
    else
    {
        zMin = endPos.z;
        zMax = startPos.z;
    }

    // curve velocity, rearranged to solve for t
    // at^2 + bt + c
    // local min/max occur where derivative (velocity) is zero,
    // so we use quadratic formula to find values of t at zeros

    float startPosA[] = { startPos.x, startPos.y, startPos.z };
    float startControlPosA[] = { startControlPos.x, startControlPos.y, startControlPos.z };
    float endControlPosA[] = { endControlPos.x, endControlPos.y, endControlPos.z };
    float endPosA[] = { endPos.x, endPos.y, endPos.z };

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
                Vector3 point = GetSplinePointBezierCubic3D(startPos, startControlPos, endControlPos, endPos, t[j]);

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
float GetSplineLengthSqrLinear3D(Vector3 startPos, Vector3 endPos)
{
    float lengthSqr = 0.0f;

    float dx = endPos.x - startPos.x;
    float dy = endPos.y - startPos.y;
    float dz = endPos.z - startPos.z;

    lengthSqr = dx*dx + dy*dy + dz*dz;

    return lengthSqr;
}

// Get (evaluate) length of spline: Linear 3D
float GetSplineLengthLinear3D(Vector3 startPos, Vector3 endPos)
{
    float length = 0.0f;

    float dx = endPos.x - startPos.x;
    float dy = endPos.y - startPos.y;
    float dz = endPos.z - startPos.z;

    length = sqrtf(dx*dx + dy*dy + dz*dz);

    return length;
}

// Get (evaluate) squared length of subspline: Linear 3D
float GetSubSplineLengthSqrLinear3D(Vector3 startPos, Vector3 endPos, float t0, float t1)
{
    float lengthSqr = 0.0f;

    float a = t0 - t1;
    float b = t1 - t0;

    float dx = a*startPos.x + b*endPos.x;
    float dy = a*startPos.y + b*endPos.y;
    float dz = a*startPos.z + b*endPos.z;

    lengthSqr = dx*dx + dy*dy + dz*dz;

    return lengthSqr;
}

// Get (evaluate) length of subspline: Linear 3D
float GetSubSplineLengthLinear3D(Vector3 startPos, Vector3 endPos, float t0, float t1)
{
    float length = 0.0f;

    float a = t0 - t1;
    float b = t1 - t0;

    float dx = a*startPos.x + b*endPos.x;
    float dy = a*startPos.y + b*endPos.y;
    float dz = a*startPos.z + b*endPos.z;

    length = sqrtf(dx*dx + dy*dy + dz*dz);

    return length;
}

// Get value of t (unbounded) for the point on the line closest to a given position
// NOTE 1: If the return is less than 0.0f or greater than 1.0f, the nearest point may be in a different segment
// NOTE 2: Return can be clamped [0.0f .. 1.0f] to snap the point to the start/end of the spline
float GetSplineNearestTLinear3D(Vector3 startPos, Vector3 endPos, Vector3 point)
{
    Vector3 edge = { 0 };
    edge.x = endPos.x - startPos.x;
    edge.y = endPos.y - startPos.y;
    edge.z = endPos.z - startPos.z;

    Vector3 diff = { 0 };
    diff.x = point.x - startPos.x;
    diff.y = point.y - startPos.y;
    diff.z = point.z - startPos.z;

    float t = (edge.x*diff.x + edge.y*diff.y + edge.z*diff.z)/(edge.x*edge.x + edge.y*edge.y + edge.z*edge.z);

    return t;
}

#endif // RSPLINES_3D

#endif // RSPLINES_IMPLEMENTATION

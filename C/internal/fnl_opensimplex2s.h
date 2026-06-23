// MIT License
//
// Copyright(c) 2023 Jordan Peck (jordan.me2@gmail.com)
// Copyright(c) 2023 Contributors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef FNL_INTERNAL_OPENSIMPLEX2S_H
#define FNL_INTERNAL_OPENSIMPLEX2S_H

#include "fnl_hashing.h"


static float _fnlSingleOpenSimplex2S2D(int seed, FNLfloat x, FNLfloat y)
{
    // 2D OpenSimplex2S case is a modified 2D simplex noise.

    const FNLfloat SQRT3 = (FNLfloat)1.7320508075688772935274463415059;
    const FNLfloat G2 = (3 - SQRT3) / 6;

    /*
     * --- Skew moved to TransformNoiseCoordinate method ---
     * const FNLfloat F2 = 0.5f * (SQRT3 - 1);
     * FNLfloat s = (x + y) * F2;
     * x += s; y += s;
    */

    int i = _fnlFastFloor(x);
    int j = _fnlFastFloor(y);
    float xi = (float)(x - i);
    float yi = (float)(y - j);

    i *= PRIME_X;
    j *= PRIME_Y;
    int i1 = i + PRIME_X;
    int j1 = j + PRIME_Y;

    float t = (xi + yi) * (float)G2;
    float x0 = xi - t;
    float y0 = yi - t;

    float a0 = (2.0f / 3.0f) - x0 * x0 - y0 * y0;
    float value = (a0 * a0) * (a0 * a0) * _fnlGradCoord2D(seed, i, j, x0, y0);

    float a1 = (float)(2 * (1 - 2 * G2) * (1 / G2 - 2)) * t + ((float)(-2 * (1 - 2 * G2) * (1 - 2 * G2)) + a0);
    float x1 = x0 - (float)(1 - 2 * G2);
    float y1 = y0 - (float)(1 - 2 * G2);
    value += (a1 * a1) * (a1 * a1) * _fnlGradCoord2D(seed, i1, j1, x1, y1);

    // Nested conditionals were faster than compact bit logic/arithmetic.
    float xmyi = xi - yi;
    if (t > G2)
    {
        if (xi + xmyi > 1)
        {
            float x2 = x0 + (float)(3 * G2 - 2);
            float y2 = y0 + (float)(3 * G2 - 1);
            float a2 = (2.0f / 3.0f) - x2 * x2 - y2 * y2;
            if (a2 > 0)
            {
                value += (a2 * a2) * (a2 * a2) * _fnlGradCoord2D(seed, i + (PRIME_X << 1), j + PRIME_Y, x2, y2);
            }
        }
        else
        {
            float x2 = x0 + (float)G2;
            float y2 = y0 + (float)(G2 - 1);
            float a2 = (2.0f / 3.0f) - x2 * x2 - y2 * y2;
            if (a2 > 0)
            {
                value += (a2 * a2) * (a2 * a2) * _fnlGradCoord2D(seed, i, j + PRIME_Y, x2, y2);
            }
        }

        if (yi - xmyi > 1)
        {
            float x3 = x0 + (float)(3 * G2 - 1);
            float y3 = y0 + (float)(3 * G2 - 2);
            float a3 = (2.0f / 3.0f) - x3 * x3 - y3 * y3;
            if (a3 > 0)
            {
                value += (a3 * a3) * (a3 * a3) * _fnlGradCoord2D(seed, i + PRIME_X, j + (PRIME_Y << 1), x3, y3);
            }
        }
        else
        {
            float x3 = x0 + (float)(G2 - 1);
            float y3 = y0 + (float)G2;
            float a3 = (2.0f / 3.0f) - x3 * x3 - y3 * y3;
            if (a3 > 0)
            {
                value += (a3 * a3) * (a3 * a3) * _fnlGradCoord2D(seed, i + PRIME_X, j, x3, y3);
            }
        }
    }
    else
    {
        if (xi + xmyi < 0)
        {
            float x2 = x0 + (float)(1 - G2);
            float y2 = y0 - (float)G2;
            float a2 = (2.0f / 3.0f) - x2 * x2 - y2 * y2;
            if (a2 > 0)
            {
                value += (a2 * a2) * (a2 * a2) * _fnlGradCoord2D(seed, i - PRIME_X, j, x2, y2);
            }
        }
        else
        {
            float x2 = x0 + (float)(G2 - 1);
            float y2 = y0 + (float)G2;
            float a2 = (2.0f / 3.0f) - x2 * x2 - y2 * y2;
            if (a2 > 0)
            {
                value += (a2 * a2) * (a2 * a2) * _fnlGradCoord2D(seed, i + PRIME_X, j, x2, y2);
            }
        }

        if (yi < xmyi)
        {
            float x2 = x0 - (float)G2;
            float y2 = y0 - (float)(G2 - 1);
            float a2 = (2.0f / 3.0f) - x2 * x2 - y2 * y2;
            if (a2 > 0)
            {
                value += (a2 * a2) * (a2 * a2) * _fnlGradCoord2D(seed, i, j - PRIME_Y, x2, y2);
            }
        }
        else
        {
            float x2 = x0 + (float)G2;
            float y2 = y0 + (float)(G2 - 1);
            float a2 = (2.0f / 3.0f) - x2 * x2 - y2 * y2;
            if (a2 > 0)
            {
                value += (a2 * a2) * (a2 * a2) * _fnlGradCoord2D(seed, i, j + PRIME_Y, x2, y2);
            }
        }
    }

    return value * 18.24196194486065f;
}

static float _fnlSingleOpenSimplex2S3D(int seed, FNLfloat x, FNLfloat y, FNLfloat z)
{
    // 3D OpenSimplex2S case uses two offset rotated cube grids.

    /*
     * --- Rotation moved to TransformNoiseCoordinate method ---
     * const FNLfloat R3 = (FNLfloat)(2.0 / 3.0);
     * FNLfloat r = (x + y + z) * R3; // Rotation, not skew
     * x = r - x; y = r - y; z = r - z;
     */

    int i = _fnlFastFloor(x);
    int j = _fnlFastFloor(y);
    int k = _fnlFastFloor(z);
    float xi = (float)(x - i);
    float yi = (float)(y - j);
    float zi = (float)(z - k);

    i *= PRIME_X;
    j *= PRIME_Y;
    k *= PRIME_Z;
    int seed2 = seed + 1293373;

    int xNMask = (int)(-0.5f - xi);
    int yNMask = (int)(-0.5f - yi);
    int zNMask = (int)(-0.5f - zi);

    float x0 = xi + xNMask;
    float y0 = yi + yNMask;
    float z0 = zi + zNMask;
    float a0 = 0.75f - x0 * x0 - y0 * y0 - z0 * z0;
    float value = (a0 * a0) * (a0 * a0) * _fnlGradCoord3D(seed,
                                                          i + (xNMask & PRIME_X), j + (yNMask & PRIME_Y), k + (zNMask & PRIME_Z), x0, y0, z0);

    float x1 = xi - 0.5f;
    float y1 = yi - 0.5f;
    float z1 = zi - 0.5f;
    float a1 = 0.75f - x1 * x1 - y1 * y1 - z1 * z1;
    value += (a1 * a1) * (a1 * a1) * _fnlGradCoord3D(seed2,
                                                     i + PRIME_X, j + PRIME_Y, k + PRIME_Z, x1, y1, z1);

    float xAFlipMask0 = ((xNMask | 1) << 1) * x1;
    float yAFlipMask0 = ((yNMask | 1) << 1) * y1;
    float zAFlipMask0 = ((zNMask | 1) << 1) * z1;
    float xAFlipMask1 = (-2 - (xNMask << 2)) * x1 - 1.0f;
    float yAFlipMask1 = (-2 - (yNMask << 2)) * y1 - 1.0f;
    float zAFlipMask1 = (-2 - (zNMask << 2)) * z1 - 1.0f;

    bool skip5 = false;
    float a2 = xAFlipMask0 + a0;
    if (a2 > 0)
    {
        float x2 = x0 - (xNMask | 1);
        float y2 = y0;
        float z2 = z0;
        value += (a2 * a2) * (a2 * a2) * _fnlGradCoord3D(seed,
                                                         i + (~xNMask & PRIME_X), j + (yNMask & PRIME_Y), k + (zNMask & PRIME_Z), x2, y2, z2);
    }
    else
    {
        float a3 = yAFlipMask0 + zAFlipMask0 + a0;
        if (a3 > 0)
        {
            float x3 = x0;
            float y3 = y0 - (yNMask | 1);
            float z3 = z0 - (zNMask | 1);
            value += (a3 * a3) * (a3 * a3) * _fnlGradCoord3D(seed,
                                                             i + (xNMask & PRIME_X), j + (~yNMask & PRIME_Y), k + (~zNMask & PRIME_Z), x3, y3, z3);
        }

        float a4 = xAFlipMask1 + a1;
        if (a4 > 0)
        {
            float x4 = (xNMask | 1) + x1;
            float y4 = y1;
            float z4 = z1;
            value += (a4 * a4) * (a4 * a4) * _fnlGradCoord3D(seed2,
                                                             i + (xNMask & (PRIME_X * 2)), j + PRIME_Y, k + PRIME_Z, x4, y4, z4);
            skip5 = true;
        }
    }

    bool skip9 = false;
    float a6 = yAFlipMask0 + a0;
    if (a6 > 0)
    {
        float x6 = x0;
        float y6 = y0 - (yNMask | 1);
        float z6 = z0;
        value += (a6 * a6) * (a6 * a6) * _fnlGradCoord3D(seed,
                                                         i + (xNMask & PRIME_X), j + (~yNMask & PRIME_Y), k + (zNMask & PRIME_Z), x6, y6, z6);
    }
    else
    {
        float a7 = xAFlipMask0 + zAFlipMask0 + a0;
        if (a7 > 0)
        {
            float x7 = x0 - (xNMask | 1);
            float y7 = y0;
            float z7 = z0 - (zNMask | 1);
            value += (a7 * a7) * (a7 * a7) * _fnlGradCoord3D(seed,
                                                             i + (~xNMask & PRIME_X), j + (yNMask & PRIME_Y), k + (~zNMask & PRIME_Z), x7, y7, z7);
        }

        float a8 = yAFlipMask1 + a1;
        if (a8 > 0)
        {
            float x8 = x1;
            float y8 = (yNMask | 1) + y1;
            float z8 = z1;
            value += (a8 * a8) * (a8 * a8) * _fnlGradCoord3D(seed2,
                                                             i + PRIME_X, j + (yNMask & (PRIME_Y << 1)), k + PRIME_Z, x8, y8, z8);
            skip9 = true;
        }
    }

    bool skipD = false;
    float aA = zAFlipMask0 + a0;
    if (aA > 0)
    {
        float xA = x0;
        float yA = y0;
        float zA = z0 - (zNMask | 1);
        value += (aA * aA) * (aA * aA) * _fnlGradCoord3D(seed,
                                                         i + (xNMask & PRIME_X), j + (yNMask & PRIME_Y), k + (~zNMask & PRIME_Z), xA, yA, zA);
    }
    else
    {
        float aB = xAFlipMask0 + yAFlipMask0 + a0;
        if (aB > 0)
        {
            float xB = x0 - (xNMask | 1);
            float yB = y0 - (yNMask | 1);
            float zB = z0;
            value += (aB * aB) * (aB * aB) * _fnlGradCoord3D(seed,
                                                             i + (~xNMask & PRIME_X), j + (~yNMask & PRIME_Y), k + (zNMask & PRIME_Z), xB, yB, zB);
        }

        float aC = zAFlipMask1 + a1;
        if (aC > 0)
        {
            float xC = x1;
            float yC = y1;
            float zC = (zNMask | 1) + z1;
            value += (aC * aC) * (aC * aC) * _fnlGradCoord3D(seed2,
                                                             i + PRIME_X, j + PRIME_Y, k + (zNMask & (PRIME_Z << 1)), xC, yC, zC);
            skipD = true;
        }
    }

    if (!skip5)
    {
        float a5 = yAFlipMask1 + zAFlipMask1 + a1;
        if (a5 > 0)
        {
            float x5 = x1;
            float y5 = (yNMask | 1) + y1;
            float z5 = (zNMask | 1) + z1;
            value += (a5 * a5) * (a5 * a5) * _fnlGradCoord3D(seed2,
                                                             i + PRIME_X, j + (yNMask & (PRIME_Y << 1)), k + (zNMask & (PRIME_Z << 1)), x5, y5, z5);
        }
    }

    if (!skip9)
    {
        float a9 = xAFlipMask1 + zAFlipMask1 + a1;
        if (a9 > 0)
        {
            float x9 = (xNMask | 1) + x1;
            float y9 = y1;
            float z9 = (zNMask | 1) + z1;
            value += (a9 * a9) * (a9 * a9) * _fnlGradCoord3D(seed2,
                                                             i + (xNMask & (PRIME_X * 2)), j + PRIME_Y, k + (zNMask & (PRIME_Z << 1)), x9, y9, z9);
        }
    }

    if (!skipD)
    {
        float aD = xAFlipMask1 + yAFlipMask1 + a1;
        if (aD > 0)
        {
            float xD = (xNMask | 1) + x1;
            float yD = (yNMask | 1) + y1;
            float zD = z1;
            value += (aD * aD) * (aD * aD) * _fnlGradCoord3D(seed2,
                                                             i + (xNMask & (PRIME_X << 1)), j + (yNMask & (PRIME_Y << 1)), k + PRIME_Z, xD, yD, zD);
        }
    }

    return value * 9.046026385208288f;
}

#endif

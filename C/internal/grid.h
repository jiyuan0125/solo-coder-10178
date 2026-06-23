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

#ifndef FNL_INTERNAL_GRID_H
#define FNL_INTERNAL_GRID_H

#include "hashing.h"


static float _fnlSinglePerlin2D(int seed, FNLfloat x, FNLfloat y)
{
    int x0 = _fnlFastFloor(x);
    int y0 = _fnlFastFloor(y);

    float xd0 = (float)(x - x0);
    float yd0 = (float)(y - y0);
    float xd1 = xd0 - 1;
    float yd1 = yd0 - 1;

    float xs = _fnlInterpQuintic(xd0);
    float ys = _fnlInterpQuintic(yd0);

    x0 *= PRIME_X;
    y0 *= PRIME_Y;
    int x1 = x0 + PRIME_X;
    int y1 = y0 + PRIME_Y;

    float xf0 = _fnlLerp(_fnlGradCoord2D(seed, x0, y0, xd0, yd0), _fnlGradCoord2D(seed, x1, y0, xd1, yd0), xs);
    float xf1 = _fnlLerp(_fnlGradCoord2D(seed, x0, y1, xd0, yd1), _fnlGradCoord2D(seed, x1, y1, xd1, yd1), xs);

    return _fnlLerp(xf0, xf1, ys) * 1.4247691104677813f;
}

static float _fnlSinglePerlin3D(int seed, FNLfloat x, FNLfloat y, FNLfloat z)
{
    int x0 = _fnlFastFloor(x);
    int y0 = _fnlFastFloor(y);
    int z0 = _fnlFastFloor(z);

    float xd0 = (float)(x - x0);
    float yd0 = (float)(y - y0);
    float zd0 = (float)(z - z0);
    float xd1 = xd0 - 1;
    float yd1 = yd0 - 1;
    float zd1 = zd0 - 1;

    float xs = _fnlInterpQuintic(xd0);
    float ys = _fnlInterpQuintic(yd0);
    float zs = _fnlInterpQuintic(zd0);

    x0 *= PRIME_X;
    y0 *= PRIME_Y;
    z0 *= PRIME_Z;
    int x1 = x0 + PRIME_X;
    int y1 = y0 + PRIME_Y;
    int z1 = z0 + PRIME_Z;

    float xf00 = _fnlLerp(_fnlGradCoord3D(seed, x0, y0, z0, xd0, yd0, zd0), _fnlGradCoord3D(seed, x1, y0, z0, xd1, yd0, zd0), xs);
    float xf10 = _fnlLerp(_fnlGradCoord3D(seed, x0, y1, z0, xd0, yd1, zd0), _fnlGradCoord3D(seed, x1, y1, z0, xd1, yd1, zd0), xs);
    float xf01 = _fnlLerp(_fnlGradCoord3D(seed, x0, y0, z1, xd0, yd0, zd1), _fnlGradCoord3D(seed, x1, y0, z1, xd1, yd0, zd1), xs);
    float xf11 = _fnlLerp(_fnlGradCoord3D(seed, x0, y1, z1, xd0, yd1, zd1), _fnlGradCoord3D(seed, x1, y1, z1, xd1, yd1, zd1), xs);

    float yf0 = _fnlLerp(xf00, xf10, ys);
    float yf1 = _fnlLerp(xf01, xf11, ys);

    return _fnlLerp(yf0, yf1, zs) * 0.964921414852142333984375f;
}

// Value Cubic

static float _fnlSingleValueCubic2D(int seed, FNLfloat x, FNLfloat y)
{
    int x1 = _fnlFastFloor(x);
    int y1 = _fnlFastFloor(y);

    float xs = x - (float)x1;
    float ys = y - (float)y1;

    x1 *= PRIME_X;
    y1 *= PRIME_Y;

    int x0 = x1 - PRIME_X;
    int y0 = y1 - PRIME_Y;
    int x2 = x1 + PRIME_X;
    int y2 = y1 + PRIME_Y;
    int x3 = x1 + (int)((long)PRIME_X << 1);
    int y3 = y1 + (int)((long)PRIME_Y << 1);

    return _fnlCubicLerp(
        _fnlCubicLerp(_fnlValCoord2D(seed, x0, y0), _fnlValCoord2D(seed, x1, y0), _fnlValCoord2D(seed, x2, y0), _fnlValCoord2D(seed, x3, y0),
                      xs),
        _fnlCubicLerp(_fnlValCoord2D(seed, x0, y1), _fnlValCoord2D(seed, x1, y1), _fnlValCoord2D(seed, x2, y1), _fnlValCoord2D(seed, x3, y1),
                      xs),
        _fnlCubicLerp(_fnlValCoord2D(seed, x0, y2), _fnlValCoord2D(seed, x1, y2), _fnlValCoord2D(seed, x2, y2), _fnlValCoord2D(seed, x3, y2),
                      xs),
        _fnlCubicLerp(_fnlValCoord2D(seed, x0, y3), _fnlValCoord2D(seed, x1, y3), _fnlValCoord2D(seed, x2, y3), _fnlValCoord2D(seed, x3, y3),
                      xs),
        ys) * (1 / (1.5f * 1.5f));
}

static float _fnlSingleValueCubic3D(int seed, FNLfloat x, FNLfloat y, FNLfloat z)
{
    int x1 = _fnlFastFloor(x);
    int y1 = _fnlFastFloor(y);
    int z1 = _fnlFastFloor(z);

    float xs = x - (float)x1;
    float ys = y - (float)y1;
    float zs = z - (float)z1;

    x1 *= PRIME_X;
    y1 *= PRIME_Y;
    z1 *= PRIME_Z;

    int x0 = x1 - PRIME_X;
    int y0 = y1 - PRIME_Y;
    int z0 = z1 - PRIME_Z;
    int x2 = x1 + PRIME_X;
    int y2 = y1 + PRIME_Y;
    int z2 = z1 + PRIME_Z;
    int x3 = x1 + (int)((long)PRIME_X << 1);
    int y3 = y1 + (int)((long)PRIME_Y << 1);
    int z3 = z1 + (int)((long)PRIME_Z << 1);   

    return _fnlCubicLerp(
        _fnlCubicLerp(
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y0, z0), _fnlValCoord3D(seed, x1, y0, z0), _fnlValCoord3D(seed, x2, y0, z0), _fnlValCoord3D(seed, x3, y0, z0), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y1, z0), _fnlValCoord3D(seed, x1, y1, z0), _fnlValCoord3D(seed, x2, y1, z0), _fnlValCoord3D(seed, x3, y1, z0), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y2, z0), _fnlValCoord3D(seed, x1, y2, z0), _fnlValCoord3D(seed, x2, y2, z0), _fnlValCoord3D(seed, x3, y2, z0), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y3, z0), _fnlValCoord3D(seed, x1, y3, z0), _fnlValCoord3D(seed, x2, y3, z0), _fnlValCoord3D(seed, x3, y3, z0), xs),
            ys),
        _fnlCubicLerp(
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y0, z1), _fnlValCoord3D(seed, x1, y0, z1), _fnlValCoord3D(seed, x2, y0, z1), _fnlValCoord3D(seed, x3, y0, z1), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y1, z1), _fnlValCoord3D(seed, x1, y1, z1), _fnlValCoord3D(seed, x2, y1, z1), _fnlValCoord3D(seed, x3, y1, z1), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y2, z1), _fnlValCoord3D(seed, x1, y2, z1), _fnlValCoord3D(seed, x2, y2, z1), _fnlValCoord3D(seed, x3, y2, z1), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y3, z1), _fnlValCoord3D(seed, x1, y3, z1), _fnlValCoord3D(seed, x2, y3, z1), _fnlValCoord3D(seed, x3, y3, z1), xs),
            ys),
        _fnlCubicLerp(
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y0, z2), _fnlValCoord3D(seed, x1, y0, z2), _fnlValCoord3D(seed, x2, y0, z2), _fnlValCoord3D(seed, x3, y0, z2), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y1, z2), _fnlValCoord3D(seed, x1, y1, z2), _fnlValCoord3D(seed, x2, y1, z2), _fnlValCoord3D(seed, x3, y1, z2), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y2, z2), _fnlValCoord3D(seed, x1, y2, z2), _fnlValCoord3D(seed, x2, y2, z2), _fnlValCoord3D(seed, x3, y2, z2), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y3, z2), _fnlValCoord3D(seed, x1, y3, z2), _fnlValCoord3D(seed, x2, y3, z2), _fnlValCoord3D(seed, x3, y3, z2), xs),
            ys),
        _fnlCubicLerp(
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y0, z3), _fnlValCoord3D(seed, x1, y0, z3), _fnlValCoord3D(seed, x2, y0, z3), _fnlValCoord3D(seed, x3, y0, z3), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y1, z3), _fnlValCoord3D(seed, x1, y1, z3), _fnlValCoord3D(seed, x2, y1, z3), _fnlValCoord3D(seed, x3, y1, z3), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y2, z3), _fnlValCoord3D(seed, x1, y2, z3), _fnlValCoord3D(seed, x2, y2, z3), _fnlValCoord3D(seed, x3, y2, z3), xs),
            _fnlCubicLerp(_fnlValCoord3D(seed, x0, y3, z3), _fnlValCoord3D(seed, x1, y3, z3), _fnlValCoord3D(seed, x2, y3, z3), _fnlValCoord3D(seed, x3, y3, z3), xs),
            ys),
        zs) * (1 / 1.5f * 1.5f * 1.5f);
}

// Value noise

static float _fnlSingleValue2D(int seed, FNLfloat x, FNLfloat y)
{
    int x0 = _fnlFastFloor(x);
    int y0 = _fnlFastFloor(y);

    float xs = _fnlInterpHermite((float)(x - x0));
    float ys = _fnlInterpHermite((float)(y - y0));

    x0 *= PRIME_X;
    y0 *= PRIME_Y;
    int x1 = x0 + PRIME_X;
    int y1 = y0 + PRIME_Y;

    float xf0 = _fnlLerp(_fnlValCoord2D(seed, x0, y0), _fnlValCoord2D(seed, x1, y0), xs);
    float xf1 = _fnlLerp(_fnlValCoord2D(seed, x0, y1), _fnlValCoord2D(seed, x1, y1), xs);

    return _fnlLerp(xf0, xf1, ys);
}

static float _fnlSingleValue3D(int seed, FNLfloat x, FNLfloat y, FNLfloat z)
{
    int x0 = _fnlFastFloor(x);
    int y0 = _fnlFastFloor(y);
    int z0 = _fnlFastFloor(z);

    float xs = _fnlInterpHermite((float)(x - x0));
    float ys = _fnlInterpHermite((float)(y - y0));
    float zs = _fnlInterpHermite((float)(z - z0));

    x0 *= PRIME_X;
    y0 *= PRIME_Y;
    z0 *= PRIME_Z;
    int x1 = x0 + PRIME_X;
    int y1 = y0 + PRIME_Y;
    int z1 = z0 + PRIME_Z;

    float xf00 = _fnlLerp(_fnlValCoord3D(seed, x0, y0, z0), _fnlValCoord3D(seed, x1, y0, z0), xs);
    float xf10 = _fnlLerp(_fnlValCoord3D(seed, x0, y1, z0), _fnlValCoord3D(seed, x1, y1, z0), xs);
    float xf01 = _fnlLerp(_fnlValCoord3D(seed, x0, y0, z1), _fnlValCoord3D(seed, x1, y0, z1), xs);
    float xf11 = _fnlLerp(_fnlValCoord3D(seed, x0, y1, z1), _fnlValCoord3D(seed, x1, y1, z1), xs);

    float yf0 = _fnlLerp(xf00, xf10, ys);
    float yf1 = _fnlLerp(xf01, xf11, ys);

    return _fnlLerp(yf0, yf1, zs);
}

#endif

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

#ifndef FNL_INTERNAL_OPENSIMPLEX2_H
#define FNL_INTERNAL_OPENSIMPLEX2_H

#include "hashing.h"


static float _fnlSingleSimplex2D(int seed, FNLfloat x, FNLfloat y)
{
    // 2D OpenSimplex2 case uses the same algorithm as ordinary Simplex.

    const float SQRT3 = 1.7320508075688772935274463415059f;
    const float G2 = (3 - SQRT3) / 6;

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

    float t = (xi + yi) * G2;
    float x0 = (float)(xi - t);
    float y0 = (float)(yi - t);

    i *= PRIME_X;
    j *= PRIME_Y;

    float n0, n1, n2;

    float a = 0.5f - x0 * x0 - y0 * y0;
    if (a <= 0)
        n0 = 0;
    else
    {
        n0 = (a * a) * (a * a) * _fnlGradCoord2D(seed, i, j, x0, y0);
    }

    float c = (float)(2 * (1 - 2 * G2) * (1 / G2 - 2)) * t + ((float)(-2 * (1 - 2 * G2) * (1 - 2 * G2)) + a);
    if (c <= 0)
        n2 = 0;
    else
    {
        float x2 = x0 + (2 * (float)G2 - 1);
        float y2 = y0 + (2 * (float)G2 - 1);
        n2 = (c * c) * (c * c) * _fnlGradCoord2D(seed, i + PRIME_X, j + PRIME_Y, x2, y2);
    }

    if (y0 > x0)
    {
        float x1 = x0 + (float)G2;
        float y1 = y0 + ((float)G2 - 1);
        float b = 0.5f - x1 * x1 - y1 * y1;
        if (b <= 0)
            n1 = 0;
        else
        {
            n1 = (b * b) * (b * b) * _fnlGradCoord2D(seed, i, j + PRIME_Y, x1, y1);
        }
    }
    else
    {
        float x1 = x0 + ((float)G2 - 1);
        float y1 = y0 + (float)G2;
        float b = 0.5f - x1 * x1 - y1 * y1;
        if (b <= 0)
            n1 = 0;
        else
        {
            n1 = (b * b) * (b * b) * _fnlGradCoord2D(seed, i + PRIME_X, j, x1, y1);
        }
    }

    return (n0 + n1 + n2) * 99.83685446303647f;
}

static float _fnlSingleOpenSimplex23D(int seed, FNLfloat x, FNLfloat y, FNLfloat z)
{
    // 3D OpenSimplex2 case uses two offset rotated cube grids.

    /*
     * --- Rotation moved to TransformNoiseCoordinate method ---
     * const FNLfloat R3 = (FNLfloat)(2.0 / 3.0);
     * FNLfloat r = (x + y + z) * R3; // Rotation, not skew
     * x = r - x; y = r - y; z = r - z;
     */

    int i = _fnlFastRound(x);
    int j = _fnlFastRound(y);
    int k = _fnlFastRound(z);
    float x0 = (float)(x - i);
    float y0 = (float)(y - j);
    float z0 = (float)(z - k);

    int xNSign = (int)(-1.0f - x0) | 1;
    int yNSign = (int)(-1.0f - y0) | 1;
    int zNSign = (int)(-1.0f - z0) | 1;

    float ax0 = xNSign * -x0;
    float ay0 = yNSign * -y0;
    float az0 = zNSign * -z0;

    i *= PRIME_X;
    j *= PRIME_Y;
    k *= PRIME_Z;

    float value = 0;
    float a = (0.6f - x0 * x0) - (y0 * y0 + z0 * z0);

    for (int l = 0; ; l++)
    {
        if (a > 0)
        {
            value += (a * a) * (a * a) * _fnlGradCoord3D(seed, i, j, k, x0, y0, z0);
        }

        float b = a + 1;
        int i1 = i;
        int j1 = j;
        int k1 = k;
        float x1 = x0;
        float y1 = y0;
        float z1 = z0;
        if (ax0 >= ay0 && ax0 >= az0)
        {
            x1 += xNSign;
            b -= xNSign * 2 * x1;
            i1 -= xNSign * PRIME_X;
        }
        else if (ay0 > ax0 && ay0 >= az0)
        {
            y1 += yNSign;
            b -= yNSign * 2 * y1;
            j1 -= yNSign * PRIME_Y;
        }
        else
        {
            z1 += zNSign;
            b -= zNSign * 2 * z1;
            k1 -= zNSign * PRIME_Z;
        }

        if (b > 0)
        {
            value += (b * b) * (b * b) * _fnlGradCoord3D(seed, i1, j1, k1, x1, y1, z1);
        }

        if (l == 1)
            break;

        ax0 = 0.5f - ax0;
        ay0 = 0.5f - ay0;
        az0 = 0.5f - az0;

        x0 = xNSign * ax0;
        y0 = yNSign * ay0;
        z0 = zNSign * az0;

        a += (0.75f - ax0) - (ay0 + az0);

        i += (xNSign >> 1) & PRIME_X;
        j += (yNSign >> 1) & PRIME_Y;
        k += (zNSign >> 1) & PRIME_Z;

        xNSign = -xNSign;
        yNSign = -yNSign;
        zNSign = -zNSign;

        seed = ~seed;
    }

    return value * 32.69428253173828125f;
}

#endif

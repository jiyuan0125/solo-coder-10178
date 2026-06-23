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

#ifndef FNL_INTERNAL_HASHING_H
#define FNL_INTERNAL_HASHING_H

#include "constants.h"
#include "utilities.h"


static const int PRIME_X = 501125321;
static const int PRIME_Y = 1136930381;
static const int PRIME_Z = 1720413743;

static inline int _fnlHash2D(int seed, int xPrimed, int yPrimed)
{
    int hash = seed ^ xPrimed ^ yPrimed;

    hash *= 0x27d4eb2d;
    return hash;
}

static inline int _fnlHash3D(int seed, int xPrimed, int yPrimed, int zPrimed)
{
    int hash = seed ^ xPrimed ^ yPrimed ^ zPrimed;

    hash *= 0x27d4eb2d;
    return hash;
}

static inline float _fnlValCoord2D(int seed, int xPrimed, int yPrimed)
{
    int hash = _fnlHash2D(seed, xPrimed, yPrimed);
    hash *= hash;
    hash ^= hash << 19;
    return hash * (1 / 2147483648.0f);
}

static inline float _fnlValCoord3D(int seed, int xPrimed, int yPrimed, int zPrimed)
{
    int hash = _fnlHash3D(seed, xPrimed, yPrimed, zPrimed);
    hash *= hash;
    hash ^= hash << 19;
    return hash * (1 / 2147483648.0f);
}

static inline float _fnlGradCoord2D(int seed, int xPrimed, int yPrimed, float xd, float yd)
{
    int hash = _fnlHash2D(seed, xPrimed, yPrimed);
    hash ^= hash >> 15;
    hash &= 127 << 1;
    return xd * GRADIENTS_2D[hash] + yd * GRADIENTS_2D[hash | 1];
}

static inline float _fnlGradCoord3D(int seed, int xPrimed, int yPrimed, int zPrimed, float xd, float yd, float zd)
{
    int hash = _fnlHash3D(seed, xPrimed, yPrimed, zPrimed);
    hash ^= hash >> 15;
    hash &= 63 << 2;
    return xd * GRADIENTS_3D[hash] + yd * GRADIENTS_3D[hash | 1] + zd * GRADIENTS_3D[hash | 2];
}

static inline void _fnlGradCoordOut2D(int seed, int xPrimed, int yPrimed, float *xo, float *yo)
{
    int hash = _fnlHash2D(seed, xPrimed, yPrimed) & (255 << 1);

    *xo = RAND_VECS_2D[hash];
    *yo = RAND_VECS_2D[hash | 1];
}

static inline void _fnlGradCoordOut3D(int seed, int xPrimed, int yPrimed, int zPrimed, float *xo, float *yo, float *zo)
{
    int hash = _fnlHash3D(seed, xPrimed, yPrimed, zPrimed) & (255 << 2);

    *xo = RAND_VECS_3D[hash];
    *yo = RAND_VECS_3D[hash | 1];
    *zo = RAND_VECS_3D[hash | 2];
}

static inline void _fnlGradCoordDual2D(int seed, int xPrimed, int yPrimed, float xd, float yd, float *xo, float *yo)
{
    int hash = _fnlHash2D(seed, xPrimed, yPrimed);
    int index1 = hash & (127 << 1);
    int index2 = (hash >> 7) & (255 << 1);

    float xg = GRADIENTS_2D[index1];
    float yg = GRADIENTS_2D[index1 | 1];
    float value = xd * xg + yd * yg;

    float xgo = RAND_VECS_2D[index2];
    float ygo = RAND_VECS_2D[index2 | 1];

    *xo = value * xgo;
    *yo = value * ygo;
}

static inline void _fnlGradCoordDual3D(int seed, int xPrimed, int yPrimed, int zPrimed, float xd, float yd, float zd, float *xo, float *yo, float *zo)
{
    int hash = _fnlHash3D(seed, xPrimed, yPrimed, zPrimed);
    int index1 = hash & (63 << 2);
    int index2 = (hash >> 6) & (255 << 2);

    float xg = GRADIENTS_3D[index1];
    float yg = GRADIENTS_3D[index1 | 1];
    float zg = GRADIENTS_3D[index1 | 2];
    float value = xd * xg + yd * yg + zd * zg;

    float xgo = RAND_VECS_3D[index2];
    float ygo = RAND_VECS_3D[index2 | 1];
    float zgo = RAND_VECS_3D[index2 | 2];

    *xo = value * xgo;
    *yo = value * ygo;
    *zo = value * zgo;
}

#endif

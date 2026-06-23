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

#ifndef FNL_INTERNAL_DOMAINWARP_H
#define FNL_INTERNAL_DOMAINWARP_H

#include "fnl_fractal.h"


// Forward declare
static void _fnlSingleDomainWarpBasicGrid2D(int seed, float warpAmp, float frequency, FNLfloat x, FNLfloat y, FNLfloat *xp, FNLfloat *yp);
static void _fnlSingleDomainWarpBasicGrid3D(int seed, float warpAmp, float frequency, FNLfloat x, FNLfloat y, FNLfloat z, FNLfloat *xp, FNLfloat *yp, FNLfloat *zp);
static void _fnlSingleDomainWarpSimplexGradient(int seed, float warpAmp, float frequency, FNLfloat x, FNLfloat y, FNLfloat *xr, FNLfloat *yr, bool outGradOnly);
static void _fnlSingleDomainWarpOpenSimplex2Gradient(int seed, float warpAmp, float frequency, FNLfloat x, FNLfloat y, FNLfloat z, FNLfloat *xr, FNLfloat *yr, FNLfloat *zr, bool outGradOnly);

static inline void _fnlDoSingleDomainWarp2D(const fnl_state *state, int seed, float amp, float freq, FNLfloat x, FNLfloat y, FNLfloat *xp, FNLfloat *yp)
{
    switch (state->domain_warp_type)
    {
    case FNL_DOMAIN_WARP_OPENSIMPLEX2:
        _fnlSingleDomainWarpSimplexGradient(seed, amp * 38.283687591552734375f, freq, x, y, xp, yp, false);
        break;
    case FNL_DOMAIN_WARP_OPENSIMPLEX2_REDUCED:
        _fnlSingleDomainWarpSimplexGradient(seed, amp * 16.0f, freq, x, y, xp, yp, true);
        break;
    case FNL_DOMAIN_WARP_BASICGRID:
        _fnlSingleDomainWarpBasicGrid2D(seed, amp, freq, x, y, xp, yp);
        break;
    }
}

static inline void _fnlDoSingleDomainWarp3D(const fnl_state *state, int seed, float amp, float freq, FNLfloat x, FNLfloat y, FNLfloat z, FNLfloat *xp, FNLfloat *yp, FNLfloat *zp)
{
    switch (state->domain_warp_type)
    {
    case FNL_DOMAIN_WARP_OPENSIMPLEX2:
        _fnlSingleDomainWarpOpenSimplex2Gradient(seed, amp * 32.69428253173828125f, freq, x, y, z, xp, yp, zp, false);
        break;
    case FNL_DOMAIN_WARP_OPENSIMPLEX2_REDUCED:
        _fnlSingleDomainWarpOpenSimplex2Gradient(seed, amp * 7.71604938271605f, freq, x, y, z, xp, yp, zp, true);
        break;
    case FNL_DOMAIN_WARP_BASICGRID:
        _fnlSingleDomainWarpBasicGrid3D(seed, amp, freq, x, y, z, xp, yp, zp);
        break;
    }
}

// Domain Warp Single Wrapper

static void _fnlDomainWarpSingle2D(const fnl_state *state, FNLfloat *x, FNLfloat *y)
{
    int seed = state->seed;
    float amp = state->domain_warp_amp * _fnlCalculateFractalBounding(state);
    float freq = state->frequency;

    FNLfloat xs = *x;
    FNLfloat ys = *y;
    _fnlTransformDomainWarpCoordinate2D(state, &xs, &ys);

    _fnlDoSingleDomainWarp2D(state, seed, amp, freq, xs, ys, x, y);
}

static void _fnlDomainWarpSingle3D(const fnl_state *state, FNLfloat *x, FNLfloat *y, FNLfloat *z)
{
    int seed = state->seed;
    float amp = state->domain_warp_amp * _fnlCalculateFractalBounding(state);
    float freq = state->frequency;

    FNLfloat xs = *x;
    FNLfloat ys = *y;
    FNLfloat zs = *z;
    _fnlTransformDomainWarpCoordinate3D(state, &xs, &ys, &zs);

    _fnlDoSingleDomainWarp3D(state, seed, amp, freq, xs, ys, zs, x, y, z);
}

// Domain Warp Fractal Progressive

static void _fnlDomainWarpFractalProgressive2D(const fnl_state *state, FNLfloat *x, FNLfloat *y)
{
    int seed = state->seed;
    float amp = state->domain_warp_amp * _fnlCalculateFractalBounding(state);
    float freq = state->frequency;

    for (int i = 0; i < state->octaves; i++)
    {
        FNLfloat xs = *x;
        FNLfloat ys = *y;
        _fnlTransformDomainWarpCoordinate2D(state, &xs, &ys);

        _fnlDoSingleDomainWarp2D(state, seed, amp, freq, xs, ys, x, y);

        seed++;
        amp *= state->gain;
        freq *= state->lacunarity;
    }
}

static void _fnlDomainWarpFractalProgressive3D(const fnl_state *state, FNLfloat *x, FNLfloat *y, FNLfloat *z)
{
    int seed = state->seed;
    float amp = state->domain_warp_amp * _fnlCalculateFractalBounding(state);
    float freq = state->frequency;

    for (int i = 0; i < state->octaves; i++)
    {
        FNLfloat xs = *x;
        FNLfloat ys = *y;
        FNLfloat zs = *z;
        _fnlTransformDomainWarpCoordinate3D(state, &xs, &ys, &zs);

        _fnlDoSingleDomainWarp3D(state, seed, amp, freq, xs, ys, zs, x, y, z);

        seed++;
        amp *= state->gain;
        freq *= state->lacunarity;
    }
}

// Domain Warp Fractal Independent

static void _fnlDomainWarpFractalIndependent2D(const fnl_state *state, FNLfloat *x, FNLfloat *y)
{
    FNLfloat xs = *x;
    FNLfloat ys = *y;
    _fnlTransformDomainWarpCoordinate2D(state, &xs, &ys);

    int seed = state->seed;
    float amp = state->domain_warp_amp * _fnlCalculateFractalBounding(state);
    float freq = state->frequency;

    for (int i = 0; i < state->octaves; i++)
    {
        _fnlDoSingleDomainWarp2D(state, seed, amp, freq, xs, ys, x, y);

        seed++;
        amp *= state->gain;
        freq *= state->lacunarity;
    }
}

static void _fnlDomainWarpFractalIndependent3D(const fnl_state *state, FNLfloat *x, FNLfloat *y, FNLfloat *z)
{
    FNLfloat xs = *x;
    FNLfloat ys = *y;
    FNLfloat zs = *z;
    _fnlTransformDomainWarpCoordinate3D(state, &xs, &ys, &zs);

    int seed = state->seed;
    float amp = state->domain_warp_amp * _fnlCalculateFractalBounding(state);
    float freq = state->frequency;

    for (int i = 0; i < state->octaves; i++)
    {
        _fnlDoSingleDomainWarp3D(state, seed, amp, freq, xs, ys, zs, x, y, z);

        seed++;
        amp *= state->gain;
        freq *= state->lacunarity;
    }
}

// Domain Warp Basic Grid

static void _fnlSingleDomainWarpBasicGrid2D(int seed, float warpAmp, float frequency, FNLfloat x, FNLfloat y, FNLfloat *xp, FNLfloat *yp)
{
    FNLfloat xf = x * frequency;
    FNLfloat yf = y * frequency;

    int x0 = _fnlFastFloor(xf);
    int y0 = _fnlFastFloor(yf);

    float xs = _fnlInterpHermite((float)(xf - x0));
    float ys = _fnlInterpHermite((float)(yf - y0));

    x0 *= PRIME_X;
    y0 *= PRIME_Y;
    int x1 = x0 + PRIME_X;
    int y1 = y0 + PRIME_Y;

    int idx0 = _fnlHash2D(seed, x0, y0) & (255 << 1);
    int idx1 = _fnlHash2D(seed, x1, y0) & (255 << 1);

    float lx0x = _fnlLerp(RAND_VECS_2D[idx0], RAND_VECS_2D[idx1], xs);
    float ly0x = _fnlLerp(RAND_VECS_2D[idx0 | 1], RAND_VECS_2D[idx1 | 1], xs);

    idx0 = _fnlHash2D(seed, x0, y1) & (255 << 1);
    idx1 = _fnlHash2D(seed, x1, y1) & (255 << 1);

    float lx1x = _fnlLerp(RAND_VECS_2D[idx0], RAND_VECS_2D[idx1], xs);
    float ly1x = _fnlLerp(RAND_VECS_2D[idx0 | 1], RAND_VECS_2D[idx1 | 1], xs);

    *xp += _fnlLerp(lx0x, lx1x, ys) * warpAmp;
    *yp += _fnlLerp(ly0x, ly1x, ys) * warpAmp;
}

static void _fnlSingleDomainWarpBasicGrid3D(int seed, float warpAmp, float frequency, FNLfloat x, FNLfloat y, FNLfloat z, FNLfloat *xp, FNLfloat *yp, FNLfloat *zp)
{
    FNLfloat xf = x * frequency;
    FNLfloat yf = y * frequency;
    FNLfloat zf = z * frequency;

    int x0 = _fnlFastFloor(xf);
    int y0 = _fnlFastFloor(yf);
    int z0 = _fnlFastFloor(zf);

    float xs = _fnlInterpHermite((float)(xf - x0));
    float ys = _fnlInterpHermite((float)(yf - y0));
    float zs = _fnlInterpHermite((float)(zf - z0));

    x0 *= PRIME_X;
    y0 *= PRIME_Y;
    z0 *= PRIME_Z;
    int x1 = x0 + PRIME_X;
    int y1 = y0 + PRIME_Y;
    int z1 = z0 + PRIME_Z;

    int idx0 = _fnlHash3D(seed, x0, y0, z0) & (255 << 2);
    int idx1 = _fnlHash3D(seed, x1, y0, z0) & (255 << 2);

    float lx0x = _fnlLerp(RAND_VECS_3D[idx0], RAND_VECS_3D[idx1], xs);
    float ly0x = _fnlLerp(RAND_VECS_3D[idx0 | 1], RAND_VECS_3D[idx1 | 1], xs);
    float lz0x = _fnlLerp(RAND_VECS_3D[idx0 | 2], RAND_VECS_3D[idx1 | 2], xs);

    idx0 = _fnlHash3D(seed, x0, y1, z0) & (255 << 2);
    idx1 = _fnlHash3D(seed, x1, y1, z0) & (255 << 2);

    float lx1x = _fnlLerp(RAND_VECS_3D[idx0], RAND_VECS_3D[idx1], xs);
    float ly1x = _fnlLerp(RAND_VECS_3D[idx0 | 1], RAND_VECS_3D[idx1 | 1], xs);
    float lz1x = _fnlLerp(RAND_VECS_3D[idx0 | 2], RAND_VECS_3D[idx1 | 2], xs);

    float lx0y = _fnlLerp(lx0x, lx1x, ys);
    float ly0y = _fnlLerp(ly0x, ly1x, ys);
    float lz0y = _fnlLerp(lz0x, lz1x, ys);

    idx0 = _fnlHash3D(seed, x0, y0, z1) & (255 << 2);
    idx1 = _fnlHash3D(seed, x1, y0, z1) & (255 << 2);

    lx0x = _fnlLerp(RAND_VECS_3D[idx0], RAND_VECS_3D[idx1], xs);
    ly0x = _fnlLerp(RAND_VECS_3D[idx0 | 1], RAND_VECS_3D[idx1 | 1], xs);
    lz0x = _fnlLerp(RAND_VECS_3D[idx0 | 2], RAND_VECS_3D[idx1 | 2], xs);

    idx0 = _fnlHash3D(seed, x0, y1, z1) & (255 << 2);
    idx1 = _fnlHash3D(seed, x1, y1, z1) & (255 << 2);

    lx1x = _fnlLerp(RAND_VECS_3D[idx0], RAND_VECS_3D[idx1], xs);
    ly1x = _fnlLerp(RAND_VECS_3D[idx0 | 1], RAND_VECS_3D[idx1 | 1], xs);
    lz1x = _fnlLerp(RAND_VECS_3D[idx0 | 2], RAND_VECS_3D[idx1 | 2], xs);

    *xp += _fnlLerp(lx0y, _fnlLerp(lx0x, lx1x, ys), zs) * warpAmp;
    *yp += _fnlLerp(ly0y, _fnlLerp(ly0x, ly1x, ys), zs) * warpAmp;
    *zp += _fnlLerp(lz0y, _fnlLerp(lz0x, lz1x, ys), zs) * warpAmp;
}

// Domain Warp Simplex/OpenSimplex2

static void _fnlSingleDomainWarpSimplexGradient(int seed, float warpAmp, float frequency, FNLfloat x, FNLfloat y, FNLfloat *xr, FNLfloat *yr, bool outGradOnly)
{
    const float SQRT3 = 1.7320508075688772935274463415059f;
    const float G2 = (3 - SQRT3) / 6;

    x *= frequency;
    y *= frequency;

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

    float vx, vy;
    vx = vy = 0;

    float a = 0.5f - x0 * x0 - y0 * y0;
    if (a > 0)
    {
        float aaaa = (a * a) * (a * a);
        float xo, yo;
        if (outGradOnly)
            _fnlGradCoordOut2D(seed, i, j, &xo, &yo);
        else
            _fnlGradCoordDual2D(seed, i, j, x0, y0, &xo, &yo);
        vx += aaaa * xo;
        vy += aaaa * yo;
    }

    float c = (float)(2 * (1 - 2 * G2) * (1 / G2 - 2)) * t + ((float)(-2 * (1 - 2 * G2) * (1 - 2 * G2)) + a);
    if (c > 0)
    {
        float x2 = x0 + (2 * (float)G2 - 1);
        float y2 = y0 + (2 * (float)G2 - 1);
        float cccc = (c * c) * (c * c);
        float xo, yo;
        if (outGradOnly)
            _fnlGradCoordOut2D(seed, i + PRIME_X, j + PRIME_Y, &xo, &yo);
        else
            _fnlGradCoordDual2D(seed, i + PRIME_X, j + PRIME_Y, x2, y2, &xo, &yo);
        vx += cccc * xo;
        vy += cccc * yo;
    }

    if (y0 > x0)
    {
        float x1 = x0 + (float)G2;
        float y1 = y0 + ((float)G2 - 1);
        float b = 0.5f - x1 * x1 - y1 * y1;
        if (b > 0)
        {
            float bbbb = (b * b) * (b * b);
            float xo, yo;
            if (outGradOnly)
                _fnlGradCoordOut2D(seed, i, j + PRIME_Y, &xo, &yo);
            else
                _fnlGradCoordDual2D(seed, i, j + PRIME_Y, x1, y1, &xo, &yo);
            vx += bbbb * xo;
            vy += bbbb * yo;
        }
    }
    else
    {
        float x1 = x0 + ((float)G2 - 1);
        float y1 = y0 + (float)G2;
        float b = 0.5f - x1 * x1 - y1 * y1;
        if (b > 0)
        {
            float bbbb = (b * b) * (b * b);
            float xo, yo;
            if (outGradOnly)
                _fnlGradCoordOut2D(seed, i + PRIME_X, j, &xo, &yo);
            else
                _fnlGradCoordDual2D(seed, i + PRIME_X, j, x1, y1, &xo, &yo);
            vx += bbbb * xo;
            vy += bbbb * yo;
        }
    }

    *xr += vx * warpAmp;
    *yr += vy * warpAmp;
}

static void _fnlSingleDomainWarpOpenSimplex2Gradient(int seed, float warpAmp, float frequency, FNLfloat x, FNLfloat y, FNLfloat z, FNLfloat *xr, FNLfloat *yr, FNLfloat *zr, bool outGradOnly)
{
    x *= frequency;
    y *= frequency;
    z *= frequency;

    /*
     * --- Rotation moved to TransformDomainWarpCoordinate method ---
     * const FNLfloat R3 = (FNLfloat)(2.0 / 3.0);
     * FNLfloat r = (x + y + z) * R3; // Rotation, not skew
     * x = r - x; y = r - y; z = r - z;
     */

    int i = _fnlFastRound(x);
    int j = _fnlFastRound(y);
    int k = _fnlFastRound(z);
    float x0 = (float)x - i;
    float y0 = (float)y - j;
    float z0 = (float)z - k;

    int xNSign = (int)(-x0 - 1.0f) | 1;
    int yNSign = (int)(-y0 - 1.0f) | 1;
    int zNSign = (int)(-z0 - 1.0f) | 1;

    float ax0 = xNSign * -x0;
    float ay0 = yNSign * -y0;
    float az0 = zNSign * -z0;

    i *= PRIME_X;
    j *= PRIME_Y;
    k *= PRIME_Z;

    float vx, vy, vz;
    vx = vy = vz = 0;

    float a = (0.6f - x0 * x0) - (y0 * y0 + z0 * z0);
    for (int l = 0; l < 2; l++)
    {
        if (a > 0)
        {
            float aaaa = (a * a) * (a * a);
            float xo, yo, zo;
            if (outGradOnly)
                _fnlGradCoordOut3D(seed, i, j, k, &xo, &yo, &zo);
            else
                _fnlGradCoordDual3D(seed, i, j, k, x0, y0, z0, &xo, &yo, &zo);
            vx += aaaa * xo;
            vy += aaaa * yo;
            vz += aaaa * zo;
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
            float bbbb = (b * b) * (b * b);
            float xo, yo, zo;
            if (outGradOnly)
                _fnlGradCoordOut3D(seed, i1, j1, k1, &xo, &yo, &zo);
            else
                _fnlGradCoordDual3D(seed, i1, j1, k1, x1, y1, z1, &xo, &yo, &zo);
            vx += bbbb * xo;
            vy += bbbb * yo;
            vz += bbbb * zo;
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

        seed += 1293373;
    }

    *xr += vx * warpAmp;
    *yr += vy * warpAmp;
    *zr += vz * warpAmp;
}


#endif

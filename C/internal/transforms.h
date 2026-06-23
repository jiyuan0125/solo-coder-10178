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

#ifndef FNL_INTERNAL_TRANSFORMS_H
#define FNL_INTERNAL_TRANSFORMS_H

#include "hashing.h"


static void _fnlTransformNoiseCoordinate2D(const fnl_state *state, FNLfloat *x, FNLfloat *y)
{
    *x *= state->frequency;
    *y *= state->frequency;

    switch (state->noise_type)
    {
    case FNL_NOISE_OPENSIMPLEX2:
    case FNL_NOISE_OPENSIMPLEX2S:
    {
        const FNLfloat SQRT3 = (FNLfloat)1.7320508075688772935274463415059;
        const FNLfloat F2 = 0.5f * (SQRT3 - 1);
        FNLfloat t = (*x + *y) * F2;
        *x += t;
        *y += t;
    }
    break;
    default:
        break;
    }
}

static void _fnlTransformNoiseCoordinate3D(const fnl_state *state, FNLfloat *x, FNLfloat *y, FNLfloat *z)
{
    *x *= state->frequency;
    *y *= state->frequency;
    *z *= state->frequency;

    switch (state->rotation_type_3d)
    {
    case FNL_ROTATION_IMPROVE_XY_PLANES:
    {
        FNLfloat xy = *x + *y;
        FNLfloat s2 = xy * -(FNLfloat)0.211324865405187;
        *z *= (FNLfloat)0.577350269189626;
        *x += s2 - *z;
        *y = *y + s2 - *z;
        *z += xy * (FNLfloat)0.577350269189626;
    }
    break;
    case FNL_ROTATION_IMPROVE_XZ_PLANES:
    {
        FNLfloat xz = *x + *z;
        FNLfloat s2 = xz * -(FNLfloat)0.211324865405187;
        *y *= (FNLfloat)0.577350269189626;
        *x += s2 - *y;
        *z += s2 - *y;
        *y += xz * (FNLfloat)0.577350269189626;
    }
    break;
    default:
        switch (state->noise_type)
        {
        case FNL_NOISE_OPENSIMPLEX2:
        case FNL_NOISE_OPENSIMPLEX2S:
        {
            const FNLfloat R3 = (FNLfloat)(2.0 / 3.0);
            FNLfloat r = (*x + *y + *z) * R3; // Rotation, not skew
            *x = r - *x;
            *y = r - *y;
            *z = r - *z;
        }
        break;
        default:
            break;
        }
    }
}

// Domain Warp Coordinate Transforms

static void _fnlTransformDomainWarpCoordinate2D(const fnl_state *state, FNLfloat *x, FNLfloat *y)
{
    switch (state->domain_warp_type)
    {
    case FNL_DOMAIN_WARP_OPENSIMPLEX2:
    case FNL_DOMAIN_WARP_OPENSIMPLEX2_REDUCED:
    {
        const FNLfloat SQRT3 = (FNLfloat)1.7320508075688772935274463415059;
        const FNLfloat F2 = 0.5f * (SQRT3 - 1);
        FNLfloat t = (*x + *y) * F2;
        *x += t;
        *y += t;
    }
    break;
    default:
        break;
    }
}

static void _fnlTransformDomainWarpCoordinate3D(const fnl_state *state, FNLfloat *x, FNLfloat *y, FNLfloat *z)
{
    switch (state->rotation_type_3d)
    {
    case FNL_ROTATION_IMPROVE_XY_PLANES:
    {
        FNLfloat xy = *x + *y;
        FNLfloat s2 = xy * -(FNLfloat)0.211324865405187;
        *z *= (FNLfloat)0.577350269189626;
        *x += s2 - *z;
        *y = *y + s2 - *z;
        *z += xy * (FNLfloat)0.577350269189626;
    }
    break;
    case FNL_ROTATION_IMPROVE_XZ_PLANES:
    {
        FNLfloat xz = *x + *z;
        FNLfloat s2 = xz * -(FNLfloat)0.211324865405187;
        *y *= (FNLfloat)0.577350269189626;
        *x += s2 - *y;
        *z += s2 - *y;
        *y += xz * (FNLfloat)0.577350269189626;
    }
    break;
    default:
        switch (state->domain_warp_type)
        {
        case FNL_DOMAIN_WARP_OPENSIMPLEX2:
        case FNL_DOMAIN_WARP_OPENSIMPLEX2_REDUCED:
        {
            const FNLfloat R3 = (FNLfloat)(2.0 / 3.0);
            FNLfloat r = (*x + *y + *z) * R3; // Rotation, not skew
            *x = r - *x;
            *y = r - *y;
            *z = r - *z;
        }
        break;
        default:
            break;
        }
    }
}

#endif

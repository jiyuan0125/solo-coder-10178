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

#ifndef FNL_INTERNAL_DISPATCH_H
#define FNL_INTERNAL_DISPATCH_H

#include "fnl_opensimplex2.h"
#include "fnl_opensimplex2s.h"
#include "fnl_cellular.h"
#include "fnl_grid.h"

static float _fnlGenNoiseSingle2D(const fnl_state *state, int seed, FNLfloat x, FNLfloat y)
{
    switch (state->noise_type)
    {
    case FNL_NOISE_OPENSIMPLEX2:
        return _fnlSingleSimplex2D(seed, x, y);
    case FNL_NOISE_OPENSIMPLEX2S:
        return _fnlSingleOpenSimplex2S2D(seed, x, y);
    case FNL_NOISE_CELLULAR:
        return _fnlSingleCellular2D(state, seed, x, y);
    case FNL_NOISE_PERLIN:
        return _fnlSinglePerlin2D(seed, x, y);
    case FNL_NOISE_VALUE_CUBIC:
        return _fnlSingleValueCubic2D(seed, x, y);
    case FNL_NOISE_VALUE:
        return _fnlSingleValue2D(seed, x, y);
    default:
        return 0;
    }
}

static float _fnlGenNoiseSingle3D(const fnl_state *state, int seed, FNLfloat x, FNLfloat y, FNLfloat z)
{
    switch (state->noise_type)
    {
    case FNL_NOISE_OPENSIMPLEX2:
        return _fnlSingleOpenSimplex23D(seed, x, y, z);
    case FNL_NOISE_OPENSIMPLEX2S:
        return _fnlSingleOpenSimplex2S3D(seed, x, y, z);
    case FNL_NOISE_CELLULAR:
        return _fnlSingleCellular3D(state, seed, x, y, z);
    case FNL_NOISE_PERLIN:
        return _fnlSinglePerlin3D(seed, x, y, z);
    case FNL_NOISE_VALUE_CUBIC:
        return _fnlSingleValueCubic3D(seed, x, y, z);
    case FNL_NOISE_VALUE:
        return _fnlSingleValue3D(seed, x, y, z);
    default:
        return 0;
    }
}

#endif

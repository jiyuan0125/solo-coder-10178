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

#ifndef FNL_INTERNAL_FRACTAL_H
#define FNL_INTERNAL_FRACTAL_H

#include "dispatch.h"

static float _fnlGenFractalFBM2D(const fnl_state *state, FNLfloat x, FNLfloat y)
{
    int seed = state->seed;
    float sum = 0;
    float amp = _fnlCalculateFractalBounding(state);

    for (int i = 0; i < state->octaves; i++)
    {
        float noise = _fnlGenNoiseSingle2D(state, seed++, x, y);
        sum += noise * amp;
        amp *= _fnlLerp(1.0f, _fnlFastMin(noise + 1, 2) * 0.5f, state->weighted_strength);

        x *= state->lacunarity;
        y *= state->lacunarity;
        amp *= state->gain;
    }

    return sum;
}

static float _fnlGenFractalFBM3D(const fnl_state *state, FNLfloat x, FNLfloat y, FNLfloat z)
{
    int seed = state->seed;
    float sum = 0;
    float amp = _fnlCalculateFractalBounding(state);

    for (int i = 0; i < state->octaves; i++)
    {
        float noise = _fnlGenNoiseSingle3D(state, seed++, x, y, z);
        sum += noise * amp;
        amp *= _fnlLerp(1.0f, (noise + 1) * 0.5f, state->weighted_strength);

        x *= state->lacunarity;
        y *= state->lacunarity;
        z *= state->lacunarity;
        amp *= state->gain;
    }

    return sum;
}

// Fractal Ridged

static float _fnlGenFractalRidged2D(const fnl_state *state, FNLfloat x, FNLfloat y)
{
    int seed = state->seed;
    float sum = 0;
    float amp = _fnlCalculateFractalBounding(state);

    for (int i = 0; i < state->octaves; i++)
    {
        float noise = _fnlFastAbs(_fnlGenNoiseSingle2D(state, seed++, x, y));
        sum += (noise * -2 + 1) * amp;
        amp *= _fnlLerp(1.0f, 1 - noise, state->weighted_strength);

        x *= state->lacunarity;
        y *= state->lacunarity;
        amp *= state->gain;
    }

    return sum;
}

static float _fnlGenFractalRidged3D(const fnl_state *state, FNLfloat x, FNLfloat y, FNLfloat z)
{
    int seed = state->seed;
    float sum = 0;
    float amp = _fnlCalculateFractalBounding(state);

    for (int i = 0; i < state->octaves; i++)
    {
        float noise = _fnlFastAbs(_fnlGenNoiseSingle3D(state, seed++, x, y, z));
        sum += (noise * -2 + 1) * amp;
        amp *= _fnlLerp(1.0f, 1 - noise, state->weighted_strength);

        x *= state->lacunarity;
        y *= state->lacunarity;
        z *= state->lacunarity;
        amp *= state->gain;
    }

    return sum;
}

// Fractal PingPong

static float _fnlGenFractalPingPong2D(const fnl_state *state, FNLfloat x, FNLfloat y)
{
    int seed = state->seed;
    float sum = 0;
    float amp = _fnlCalculateFractalBounding(state);

    for (int i = 0; i < state->octaves; i++)
    {
        float noise = _fnlPingPong((_fnlGenNoiseSingle2D(state, seed++, x, y) + 1) * state->ping_pong_strength);
        sum += (noise - 0.5f) * 2 * amp;
        amp *= _fnlLerp(1.0f, noise, state->weighted_strength);

        x *= state->lacunarity;
        y *= state->lacunarity;
        amp *= state->gain;
    }

    return sum;
}

static float _fnlGenFractalPingPong3D(const fnl_state *state, FNLfloat x, FNLfloat y, FNLfloat z)
{
    int seed = state->seed;
    float sum = 0;
    float amp = _fnlCalculateFractalBounding(state);

    for (int i = 0; i < state->octaves; i++)
    {
        float noise = _fnlPingPong((_fnlGenNoiseSingle3D(state, seed++, x, y, z) + 1) * state->ping_pong_strength);
        sum += (noise - 0.5f) * 2 * amp;
        amp *= _fnlLerp(1.0f, noise, state->weighted_strength);

        x *= state->lacunarity;
        y *= state->lacunarity;
        z *= state->lacunarity;
        amp *= state->gain;
    }

    return sum;
}

#endif

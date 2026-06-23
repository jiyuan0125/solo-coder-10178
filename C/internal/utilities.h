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

#ifndef FNL_INTERNAL_UTILITIES_H
#define FNL_INTERNAL_UTILITIES_H



static inline float _fnlFastMin(float x, float y) { return x < y ? x : y; }

static inline float _fnlFastMax(float x, float y) { return x > y ? x : y; }

static inline float _fnlFastAbs(float f) { return f < 0 ? -f : f; }

static inline float _fnlCasti32Tof32(int i)
{
    union
    {
        float f;
        int32_t i;
    } u;
    u.i = i;
    return u.f;
}

static inline int _fnlCastf32Toi32(float f)
{
    union
    {
        float f;
        int32_t i;
    } u;
    u.f = f;
    return u.i;
}

static inline float _fnlInvSqrt(float a)
{
    float xhalf = 0.5f * a;
    a = _fnlCasti32Tof32(0x5f3759df - (_fnlCastf32Toi32(a) >> 1));
    a = a * (1.5f - xhalf * a * a);
    return a;
}

// NOTE: If your language does not support this method (seen above), then simply use the native sqrt function.
static inline float _fnlFastSqrt(float a) { return a * _fnlInvSqrt(a); }

static inline int _fnlFastFloor(FNLfloat f) { return (f >= 0 ? (int)f : (int)f - 1); }

static inline int _fnlFastRound(FNLfloat f) { return (f >= 0) ? (int)(f + 0.5f) : (int)(f - 0.5f); }

static inline float _fnlLerp(float a, float b, float t) { return a + t * (b - a); }

static inline float _fnlInterpHermite(float t) { return t * t * (3 - 2 * t); }

static inline float _fnlInterpQuintic(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }

static inline float _fnlCubicLerp(float a, float b, float c, float d, float t)
{
    float p = (d - c) - (a - b);
    return t * t * t * p + t * t * ((a - b) - p) + t * (c - a) + b;
}

static inline float _fnlPingPong(float t)
{
    t -= (int)(t * 0.5f) * 2;
    return t < 1 ? t : 2 - t;
}

static float _fnlCalculateFractalBounding(const fnl_state *state)
{
    float gain = _fnlFastAbs(state->gain);
    float amp = gain;
    float ampFractal = 1.0f;
    for (int i = 1; i < state->octaves; i++)
    {
        ampFractal += amp;
        amp *= gain;
    }
    return 1.0f / ampFractal;
}

#endif

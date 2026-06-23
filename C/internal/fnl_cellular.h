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

#ifndef FNL_INTERNAL_CELLULAR_H
#define FNL_INTERNAL_CELLULAR_H

#include "fnl_hashing.h"


static float _fnlSingleCellular2D(const fnl_state *state, int seed, FNLfloat x, FNLfloat y)
{
    int xr = _fnlFastRound(x);
    int yr = _fnlFastRound(y);

    float distance0 = FLT_MAX;
    float distance1 = FLT_MAX;
    int closestHash = 0;

    float cellularJitter = 0.43701595f * state->cellular_jitter_mod;

    int xPrimed = (xr - 1) * PRIME_X;
    int yPrimedBase = (yr - 1) * PRIME_Y;

    switch (state->cellular_distance_func)
    {
    default:
    case FNL_CELLULAR_DISTANCE_EUCLIDEAN:
    case FNL_CELLULAR_DISTANCE_EUCLIDEANSQ:
        for (int xi = xr - 1; xi <= xr + 1; xi++)
        {
            int yPrimed = yPrimedBase;

            for (int yi = yr - 1; yi <= yr + 1; yi++)
            {
                int hash = _fnlHash2D(seed, xPrimed, yPrimed);
                int idx = hash & (255 << 1);

                float vecX = (float)(xi - x) + RAND_VECS_2D[idx] * cellularJitter;
                float vecY = (float)(yi - y) + RAND_VECS_2D[idx | 1] * cellularJitter;

                float newDistance = vecX * vecX + vecY * vecY;

                distance1 = _fnlFastMax(_fnlFastMin(distance1, newDistance), distance0);
                if (newDistance < distance0)
                {
                    distance0 = newDistance;
                    closestHash = hash;
                }
                yPrimed += PRIME_Y;
            }
            xPrimed += PRIME_X;
        }
        break;
    case FNL_CELLULAR_DISTANCE_MANHATTAN:
        for (int xi = xr - 1; xi <= xr + 1; xi++)
        {
            int yPrimed = yPrimedBase;

            for (int yi = yr - 1; yi <= yr + 1; yi++)
            {
                int hash = _fnlHash2D(seed, xPrimed, yPrimed);
                int idx = hash & (255 << 1);

                float vecX = (float)(xi - x) + RAND_VECS_2D[idx] * cellularJitter;
                float vecY = (float)(yi - y) + RAND_VECS_2D[idx | 1] * cellularJitter;

                float newDistance = _fnlFastAbs(vecX) + _fnlFastAbs(vecY);

                distance1 = _fnlFastMax(_fnlFastMin(distance1, newDistance), distance0);
                if (newDistance < distance0)
                {
                    distance0 = newDistance;
                    closestHash = hash;
                }
                yPrimed += PRIME_Y;
            }
            xPrimed += PRIME_X;
        }
        break;
    case FNL_CELLULAR_DISTANCE_HYBRID:
        for (int xi = xr - 1; xi <= xr + 1; xi++)
        {
            int yPrimed = yPrimedBase;
            for (int yi = yr - 1; yi <= yr + 1; yi++)
            {
                int hash = _fnlHash2D(seed, xPrimed, yPrimed);
                int idx = hash & (255 << 1);

                float vecX = (float)(xi - x) + RAND_VECS_2D[idx] * cellularJitter;
                float vecY = (float)(yi - y) + RAND_VECS_2D[idx | 1] * cellularJitter;

                float newDistance = (_fnlFastAbs(vecX) + _fnlFastAbs(vecY)) + (vecX * vecX + vecY * vecY);

                distance1 = _fnlFastMax(_fnlFastMin(distance1, newDistance), distance0);
                if (newDistance < distance0)
                {
                    distance0 = newDistance;
                    closestHash = hash;
                }
                yPrimed += PRIME_Y;
            }
            xPrimed += PRIME_X;
        }
        break;
    }

    if (state->cellular_distance_func == FNL_CELLULAR_DISTANCE_EUCLIDEAN && state->cellular_return_type >= FNL_CELLULAR_RETURN_TYPE_DISTANCE)
    {
        distance0 = _fnlFastSqrt(distance0);
        if (state->cellular_return_type >= FNL_CELLULAR_RETURN_TYPE_DISTANCE2)
            distance1 = _fnlFastSqrt(distance1);
    }

    switch (state->cellular_return_type)
    {
    case FNL_CELLULAR_RETURN_TYPE_CELLVALUE:
        return closestHash * (1 / 2147483648.0f);
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE:
        return distance0 - 1;
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE2:
        return distance1 - 1;
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE2ADD:
        return (distance1 + distance0) * 0.5f - 1;
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE2SUB:
        return distance1 - distance0 - 1;
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE2MUL:
        return distance1 * distance0 * 0.5f - 1;
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE2DIV:
        return distance0 / distance1 - 1;
    default:
        return 0;
    }
}

static float _fnlSingleCellular3D(const fnl_state *state, int seed, FNLfloat x, FNLfloat y, FNLfloat z)
{
    int xr = _fnlFastRound(x);
    int yr = _fnlFastRound(y);
    int zr = _fnlFastRound(z);

    float distance0 = FLT_MAX;
    float distance1 = FLT_MAX;
    int closestHash = 0;

    float cellularJitter = 0.39614353f * state->cellular_jitter_mod;

    int xPrimed = (xr - 1) * PRIME_X;
    int yPrimedBase = (yr - 1) * PRIME_Y;
    int zPrimedBase = (zr - 1) * PRIME_Z;

    switch (state->cellular_distance_func)
    {
    default:
    case FNL_CELLULAR_DISTANCE_EUCLIDEAN:
    case FNL_CELLULAR_DISTANCE_EUCLIDEANSQ:
        for (int xi = xr - 1; xi <= xr + 1; xi++)
        {
            int yPrimed = yPrimedBase;

            for (int yi = yr - 1; yi <= yr + 1; yi++)
            {
                int zPrimed = zPrimedBase;

                for (int zi = zr - 1; zi <= zr + 1; zi++)
                {
                    int hash = _fnlHash3D(seed, xPrimed, yPrimed, zPrimed);
                    int idx = hash & (255 << 2);

                    float vecX = (float)(xi - x) + RAND_VECS_3D[idx] * cellularJitter;
                    float vecY = (float)(yi - y) + RAND_VECS_3D[idx | 1] * cellularJitter;
                    float vecZ = (float)(zi - z) + RAND_VECS_3D[idx | 2] * cellularJitter;

                    float newDistance = vecX * vecX + vecY * vecY + vecZ * vecZ;

                    distance1 = _fnlFastMax(_fnlFastMin(distance1, newDistance), distance0);
                    if (newDistance < distance0)
                    {
                        distance0 = newDistance;
                        closestHash = hash;
                    }
                    zPrimed += PRIME_Z;
                }
                yPrimed += PRIME_Y;
            }
            xPrimed += PRIME_X;
        }
        break;
    case FNL_CELLULAR_DISTANCE_MANHATTAN:
        for (int xi = xr - 1; xi <= xr + 1; xi++)
        {
            int yPrimed = yPrimedBase;

            for (int yi = yr - 1; yi <= yr + 1; yi++)
            {
                int zPrimed = zPrimedBase;

                for (int zi = zr - 1; zi <= zr + 1; zi++)
                {
                    int hash = _fnlHash3D(seed, xPrimed, yPrimed, zPrimed);
                    int idx = hash & (255 << 2);

                    float vecX = (float)(xi - x) + RAND_VECS_3D[idx] * cellularJitter;
                    float vecY = (float)(yi - y) + RAND_VECS_3D[idx | 1] * cellularJitter;
                    float vecZ = (float)(zi - z) + RAND_VECS_3D[idx | 2] * cellularJitter;

                    float newDistance = _fnlFastAbs(vecX) + _fnlFastAbs(vecY) + _fnlFastAbs(vecZ);

                    distance1 = _fnlFastMax(_fnlFastMin(distance1, newDistance), distance0);
                    if (newDistance < distance0)
                    {
                        distance0 = newDistance;
                        closestHash = hash;
                    }
                    zPrimed += PRIME_Z;
                }
                yPrimed += PRIME_Y;
            }
            xPrimed += PRIME_X;
        }
        break;
    case FNL_CELLULAR_DISTANCE_HYBRID:
        for (int xi = xr - 1; xi <= xr + 1; xi++)
        {
            int yPrimed = yPrimedBase;

            for (int yi = yr - 1; yi <= yr + 1; yi++)
            {
                int zPrimed = zPrimedBase;

                for (int zi = zr - 1; zi <= zr + 1; zi++)
                {
                    int hash = _fnlHash3D(seed, xPrimed, yPrimed, zPrimed);
                    int idx = hash & (255 << 2);

                    float vecX = (float)(xi - x) + RAND_VECS_3D[idx] * cellularJitter;
                    float vecY = (float)(yi - y) + RAND_VECS_3D[idx | 1] * cellularJitter;
                    float vecZ = (float)(zi - z) + RAND_VECS_3D[idx | 2] * cellularJitter;

                    float newDistance = (_fnlFastAbs(vecX) + _fnlFastAbs(vecY) + _fnlFastAbs(vecZ)) + (vecX * vecX + vecY * vecY + vecZ * vecZ);

                    distance1 = _fnlFastMax(_fnlFastMin(distance1, newDistance), distance0);
                    if (newDistance < distance0)
                    {
                        distance0 = newDistance;
                        closestHash = hash;
                    }
                    zPrimed += PRIME_Z;
                }
                yPrimed += PRIME_Y;
            }
            xPrimed += PRIME_X;
        }
        break;
    }

    if (state->cellular_distance_func == FNL_CELLULAR_DISTANCE_EUCLIDEAN && state->cellular_return_type >= FNL_CELLULAR_RETURN_TYPE_DISTANCE)
    {
        distance0 = _fnlFastSqrt(distance0);
        if (state->cellular_return_type >= FNL_CELLULAR_RETURN_TYPE_DISTANCE2)
            distance1 = _fnlFastSqrt(distance1);
    }

    switch (state->cellular_return_type)
    {
    case FNL_CELLULAR_RETURN_TYPE_CELLVALUE:
        return closestHash * (1 / 2147483648.0f);
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE:
        return distance0 - 1;
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE2:
        return distance1 - 1;
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE2ADD:
        return (distance1 + distance0) * 0.5f - 1;
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE2SUB:
        return distance1 - distance0 - 1;
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE2MUL:
        return distance1 * distance0 * 0.5f - 1;
    case FNL_CELLULAR_RETURN_TYPE_DISTANCE2DIV:
        return distance0 / distance1 - 1;
    default:
        return 0;
    }
}

#endif

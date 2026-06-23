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
//
// .'',;:cldxkO00KKXXNNWWWNNXKOkxdollcc::::::;:::ccllloooolllllllllooollc:,'...        ...........',;cldxkO000Okxdlc::;;;,,;;;::cclllllll
// ..',;:ldxO0KXXNNNNNNNNXXK0kxdolcc::::::;;;,,,,,,;;;;;;;;;;:::cclllllc:;'....       ...........',;:ldxO0KXXXK0Okxdolc::;;;;::cllodddddo
// ...',:loxO0KXNNNNNXXKK0Okxdolc::;::::::::;;;,,'''''.....''',;:clllllc:;,'............''''''''',;:loxO0KXNNNNNXK0Okxdollccccllodxxxxxxd
// ....';:ldkO0KXXXKK00Okxdolcc:;;;;;::cclllcc:;;,''..... ....',;clooddolcc:;;;;,,;;;;;::::;;;;;;:cloxk0KXNWWWWWWNXKK0Okxddoooddxxkkkkkxx
// .....';:ldxkOOOOOkxxdolcc:;;;,,,;;:cllooooolcc:;'...      ..,:codxkkkxddooollloooooooollcc:::::clodkO0KXNWWWWWWNNXK00Okxxxxxxxxkkkkxxx
// . ....';:cloddddo___________,,,,;;:clooddddoolc:,...      ..,:ldx__00OOOkkk___kkkkkkxxdollc::::cclodkO0KXXNNNNNNXXK0OOkxxxxxxxxxxxxddd
// .......',;:cccc:|           |,,,;;:cclooddddoll:;'..     ..';cox|  \KKK000|   |KK00OOkxdocc___;::clldxxkO0KKKKK00Okkxdddddddddddddddoo
// .......'',,,,,''|   ________|',,;;::cclloooooolc:;'......___:ldk|   \KK000|   |XKKK0Okxolc|   |;;::cclodxxkkkkxxdoolllcclllooodddooooo
// ''......''''....|   |  ....'',,,,;;;::cclloooollc:;,''.'|   |oxk|    \OOO0|   |KKK00Oxdoll|___|;;;;;::ccllllllcc::;;,,;;;:cclloooooooo
// ;;,''.......... |   |_____',,;;;____:___cllo________.___|   |___|     \xkk|   |KK_______ool___:::;________;;;_______...'',;;:ccclllloo
// c:;,''......... |         |:::/     '   |lo/        |           |      \dx|   |0/       \d|   |cc/        |'/       \......',,;;:ccllo
// ol:;,'..........|    _____|ll/    __    |o/   ______|____    ___|   |   \o|   |/   ___   \|   |o/   ______|/   ___   \ .......'',;:clo
// dlc;,...........|   |::clooo|    /  |   |x\___   \KXKKK0|   |dol|   |\   \|   |   |   |   |   |d\___   \..|   |  /   /       ....',:cl
// xoc;'...  .....'|   |llodddd|    \__|   |_____\   \KKK0O|   |lc:|   |'\       |   |___|   |   |_____\   \.|   |_/___/...      ...',;:c
// dlc;'... ....',;|   |oddddddo\          |          |Okkx|   |::;|   |..\      |\         /|   |          | \         |...    ....',;:c
// ol:,'.......',:c|___|xxxddollc\_____,___|_________/ddoll|___|,,,|___|...\_____|:\ ______/l|___|_________/...\________|'........',;::cc
// c:;'.......';:codxxkkkkxxolc::;::clodxkOO0OOkkxdollc::;;,,''''',,,,''''''''''',,'''''',;:loxkkOOkxol:;,'''',,;:ccllcc:;,'''''',;::ccll
// ;,'.......',:codxkOO0OOkxdlc:;,,;;:cldxxkkxxdolc:;;,,''.....'',;;:::;;,,,'''''........,;cldkO0KK0Okdoc::;;::cloodddoolc:;;;;;::ccllooo
// .........',;:lodxOO0000Okdoc:,,',,;:clloddoolc:;,''.......'',;:clooollc:;;,,''.......',:ldkOKXNNXX0Oxdolllloddxxxxxxdolccccccllooodddd
// .    .....';:cldxkO0000Okxol:;,''',,;::cccc:;,,'.......'',;:cldxxkkxxdolc:;;,'.......';coxOKXNWWWNXKOkxddddxxkkkkkkxdoollllooddxxxxkkk
//       ....',;:codxkO000OOxdoc:;,''',,,;;;;,''.......',,;:clodkO00000Okxolc::;,,''..',;:ldxOKXNWWWNNK0OkkkkkkkkkkkxxddooooodxxkOOOOO000
//       ....',;;clodxkkOOOkkdolc:;,,,,,,,,'..........,;:clodxkO0KKXKK0Okxdolcc::;;,,,;;:codkO0XXNNNNXKK0OOOOOkkkkxxdoollloodxkO0KKKXXXXX
//
// VERSION: 1.1.1
// https://github.com/Auburn/FastNoiseLite

// In *one* C or C++ file, use #define FNL_IMPL to generate implementation

#ifndef FASTNOISELITE_H
#define FASTNOISELITE_H

// Switch between using floats or doubles for input position
typedef float FNLfloat;
//typedef double FNLfloat;

#include <math.h>
#include <stdint.h>
#include <stdbool.h> 
#include <float.h>

// Enums
typedef enum
{
    FNL_NOISE_OPENSIMPLEX2,
    FNL_NOISE_OPENSIMPLEX2S,
    FNL_NOISE_CELLULAR,
    FNL_NOISE_PERLIN,
    FNL_NOISE_VALUE_CUBIC,
    FNL_NOISE_VALUE
} fnl_noise_type;

typedef enum
{
    FNL_ROTATION_NONE,
    FNL_ROTATION_IMPROVE_XY_PLANES,
    FNL_ROTATION_IMPROVE_XZ_PLANES
} fnl_rotation_type_3d;

typedef enum
{
    FNL_FRACTAL_NONE,
    FNL_FRACTAL_FBM,
    FNL_FRACTAL_RIDGED,
    FNL_FRACTAL_PINGPONG,
    FNL_FRACTAL_DOMAIN_WARP_PROGRESSIVE,
    FNL_FRACTAL_DOMAIN_WARP_INDEPENDENT
} fnl_fractal_type;

typedef enum
{
    FNL_CELLULAR_DISTANCE_EUCLIDEAN,
    FNL_CELLULAR_DISTANCE_EUCLIDEANSQ,
    FNL_CELLULAR_DISTANCE_MANHATTAN,
    FNL_CELLULAR_DISTANCE_HYBRID
} fnl_cellular_distance_func;

typedef enum
{
    FNL_CELLULAR_RETURN_TYPE_CELLVALUE,
    FNL_CELLULAR_RETURN_TYPE_DISTANCE,
    FNL_CELLULAR_RETURN_TYPE_DISTANCE2,
    FNL_CELLULAR_RETURN_TYPE_DISTANCE2ADD,
    FNL_CELLULAR_RETURN_TYPE_DISTANCE2SUB,
    FNL_CELLULAR_RETURN_TYPE_DISTANCE2MUL,
    FNL_CELLULAR_RETURN_TYPE_DISTANCE2DIV,
} fnl_cellular_return_type;

typedef enum
{
    FNL_DOMAIN_WARP_OPENSIMPLEX2,
    FNL_DOMAIN_WARP_OPENSIMPLEX2_REDUCED,
    FNL_DOMAIN_WARP_BASICGRID
} fnl_domain_warp_type;

/**
 * Structure containing entire noise system state.
 * @note Must only be created using fnlCreateState(optional: seed). To ensure defaults are set.
 */
typedef struct fnl_state
{
    /**
     * Seed used for all noise types.
     * @remark Default: 1337
     */
    int seed;

    /**
     * The frequency for all noise types.
     * @remark Default: 0.01
     */
    float frequency;

    /**
     * The noise algorithm to be used by GetNoise(...).
     * @remark Default: FNL_NOISE_OPENSIMPLEX2
     */
    fnl_noise_type noise_type;

    /**
     * Sets noise rotation type for 3D.
     * @remark Default: FNL_ROTATION_NONE
     */
    fnl_rotation_type_3d rotation_type_3d;

    /**
     * The method used for combining octaves for all fractal noise types.
     * @remark Default: None
     * @remark FNL_FRACTAL_DOMAIN_WARP_... only effects fnlDomainWarp...
     */
    fnl_fractal_type fractal_type;

    /**
     * The octave count for all fractal noise types.
     * @remark Default: 3
     */
    int octaves;

    /**
     * The octave lacunarity for all fractal noise types.
     * @remark Default: 2.0
     */
    float lacunarity;

    /**
     * The octave gain for all fractal noise types.
     * @remark Default: 0.5
     */
    float gain;

    /**
     * The octave weighting for all none Domaain Warp fractal types.
     * @remark Default: 0.0
     * @remark 
     */
    float weighted_strength;

    /**
     * The strength of the fractal ping pong effect.
     * @remark Default: 2.0
     */
    float ping_pong_strength;

    /**
     * The distance function used in cellular noise calculations.
     * @remark Default: FNL_CELLULAR_DISTANCE_EUCLIDEANSQ
     */
    fnl_cellular_distance_func cellular_distance_func;

    /**
     * The cellular return type from cellular noise calculations.
     * @remark Default: FNL_CELLULAR_RETURN_TYPE_DISTANCE
     */
    fnl_cellular_return_type cellular_return_type;

    /**
     * The maximum distance a cellular point can move from it's grid position.
     * @remark Default: 1.0
     * @note Setting this higher than 1 will cause artifacts.
     */
    float cellular_jitter_mod;

    /**
     * The warp algorithm when using fnlDomainWarp...
     * @remark Default: OpenSimplex2
     */
    fnl_domain_warp_type domain_warp_type;

    /**
     * The maximum warp distance from original position when using fnlDomainWarp...
     * @remark Default: 1.0
     */
    float domain_warp_amp;
} fnl_state;

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * Creates a noise state with default values.
 * @param seed Optionally set the state seed.
 */
fnl_state fnlCreateState();

/**
 * 2D noise at given position using the state settings
 * @returns Noise output bounded between -1 and 1.
 */
float fnlGetNoise2D(const fnl_state *state, FNLfloat x, FNLfloat y);

/**
 * 3D noise at given position using the state settings
 * @returns Noise output bounded between -1 and 1.
 */
float fnlGetNoise3D(const fnl_state *state, FNLfloat x, FNLfloat y, FNLfloat z);

/**
 * 2D warps the input position using current domain warp settings.
 * 
 * Example usage with fnlGetNoise2D:
 * ```
 * fnlDomainWarp2D(&state, &x, &y);
 * noise = fnlGetNoise2D(&state, x, y);
 * ```
 */
void fnlDomainWarp2D(const fnl_state *state, FNLfloat *x, FNLfloat *y);

/**
 * 3D warps the input position using current domain warp settings.
 * 
 * Example usage with fnlGetNoise3D:
 * ```
 * fnlDomainWarp3D(&state, &x, &y, &z);
 * noise = fnlGetNoise3D(&state, x, y, z);
 * ```
 */
void fnlDomainWarp3D(const fnl_state *state, FNLfloat *x, FNLfloat *y, FNLfloat *z);

#if defined(__cplusplus)
}
#endif


#if defined(FNL_IMPL)

#if defined(__cplusplus)
extern "C" {
#endif

#include "internal/constants.h"
#include "internal/utilities.h"
#include "internal/hashing.h"
#include "internal/transforms.h"
#include "internal/opensimplex2.h"
#include "internal/opensimplex2s.h"
#include "internal/cellular.h"
#include "internal/grid.h"
#include "internal/dispatch.h"
#include "internal/fractal.h"
#include "internal/domainwarp.h"

fnl_state fnlCreateState()
{
    fnl_state newState;
    newState.seed = 1337;
    newState.frequency = 0.01f;
    newState.noise_type = FNL_NOISE_OPENSIMPLEX2;
    newState.rotation_type_3d = FNL_ROTATION_NONE;
    newState.fractal_type = FNL_FRACTAL_NONE;
    newState.octaves = 3;
    newState.lacunarity = 2.0f;
    newState.gain = 0.5f;
    newState.weighted_strength = 0.0f;
    newState.ping_pong_strength = 2.0f;
    newState.cellular_distance_func = FNL_CELLULAR_DISTANCE_EUCLIDEANSQ;
    newState.cellular_return_type = FNL_CELLULAR_RETURN_TYPE_DISTANCE;
    newState.cellular_jitter_mod = 1.0f;
    newState.domain_warp_amp = 30.0f;
    newState.domain_warp_type = FNL_DOMAIN_WARP_OPENSIMPLEX2;
    return newState;
}

float fnlGetNoise2D(const fnl_state *state, FNLfloat x, FNLfloat y)
{
    _fnlTransformNoiseCoordinate2D(state, &x, &y);

    switch (state->fractal_type)
    {
    default:
        return _fnlGenNoiseSingle2D(state, state->seed, x, y);
    case FNL_FRACTAL_FBM:
        return _fnlGenFractalFBM2D(state, x, y);
    case FNL_FRACTAL_RIDGED:
        return _fnlGenFractalRidged2D(state, x, y);
    case FNL_FRACTAL_PINGPONG:
        return _fnlGenFractalPingPong2D(state, x, y);
    }
}

float fnlGetNoise3D(const fnl_state *state, FNLfloat x, FNLfloat y, FNLfloat z)
{
    _fnlTransformNoiseCoordinate3D(state, &x, &y, &z);

    // Select a noise type
    switch (state->fractal_type)
    {
    default:
        return _fnlGenNoiseSingle3D(state, state->seed, x, y, z);
    case FNL_FRACTAL_FBM:
        return _fnlGenFractalFBM3D(state, x, y, z);
    case FNL_FRACTAL_RIDGED:
        return _fnlGenFractalRidged3D(state, x, y, z);
    case FNL_FRACTAL_PINGPONG:
        return _fnlGenFractalPingPong3D(state, x, y, z);
    }
}

void fnlDomainWarp2D(const fnl_state *state, FNLfloat *x, FNLfloat *y)
{
    switch (state->fractal_type)
    {
    default:
        _fnlDomainWarpSingle2D(state, x, y);
        break;
    case FNL_FRACTAL_DOMAIN_WARP_PROGRESSIVE:
        _fnlDomainWarpFractalProgressive2D(state, x, y);
        break;
    case FNL_FRACTAL_DOMAIN_WARP_INDEPENDENT:
        _fnlDomainWarpFractalIndependent2D(state, x, y);
        break;
    }
}

void fnlDomainWarp3D(const fnl_state *state, FNLfloat *x, FNLfloat *y, FNLfloat *z)
{
    switch (state->fractal_type)
    {
    default:
        _fnlDomainWarpSingle3D(state, x, y, z);
        break;
    case FNL_FRACTAL_DOMAIN_WARP_PROGRESSIVE:
        _fnlDomainWarpFractalProgressive3D(state, x, y, z);
        break;
    case FNL_FRACTAL_DOMAIN_WARP_INDEPENDENT:
        _fnlDomainWarpFractalIndependent3D(state, x, y, z);
        break;
    }
}


#if defined(__cplusplus)
}
#endif

#endif // FNL_IMPL

#endif // FASTNOISELITE_H

Add `#define FNL_IMPL` before including `FastNoiseLite.h` in exactly one source file, or you will get linker errors

## Internal Directory

The `internal/` directory contains **private** implementation details. These headers are not part of the public API and must not be directly included or modified by users. They are automatically included by `FastNoiseLite.h` when `FNL_IMPL` is defined, in a specific dependency order:

1. `fnl_constants.h` — Gradient and random vector lookup tables with compile-time size guards
2. `fnl_utilities.h` — Helper functions (fast floor, min, etc.)
3. `fnl_hashing.h` — PRIME constants, hash functions, gradient/value coordinate functions
4. `fnl_transforms.h` — Noise and domain warp coordinate transforms
5. `fnl_opensimplex2.h` — OpenSimplex2 noise generators
6. `fnl_opensimplex2s.h` — OpenSimplex2S noise generators
7. `fnl_cellular.h` — Cellular/Worley noise generators
8. `fnl_grid.h` — Axis-aligned grid noise generators (Perlin, Value Cubic, Value)
9. `fnl_dispatch.h` — Noise type dispatch (selects generator by enum)
10. `fnl_fractal.h` — Fractal layering (FBM, Ridged, PingPong)
11. `fnl_domainwarp.h` — Domain warp implementations

Direct inclusion of any header under `internal/` is unsupported and may break without notice.

## Getting Started

Here's an example for creating a 128x128 array of OpenSimplex2 noise

```c
// Create and configure noise state
fnl_state noise = fnlCreateState();
noise.noise_type = FNL_NOISE_OPENSIMPLEX2;

// Gather noise data
float* noiseData = malloc(128 * 128 * sizeof(float));
int index = 0;

for (int y = 0; y < 128; y++)
{
    for (int x = 0; x < 128; x++) 
    {
        noiseData[index++] = fnlGetNoise2D(&noise, x, y);
    }
}

// Do something with this data...

// Free data later
free(noiseData);
```

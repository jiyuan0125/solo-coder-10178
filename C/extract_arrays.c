#include <stdio.h>
#include <string.h>

#define FNL_IMPL
#include "FastNoiseLite.h"

void print_array(const char *name, const float *arr, size_t count) {
    printf("static const float %s[] = \n{\n", name);
    for (size_t i = 0; i < count; i += 8) {
        printf("    ");
        for (size_t j = 0; j < 8 && i + j < count; j++) {
            if (j > 0) printf(", ");
            printf("%.9gf", arr[i + j]);
            if (i + j < count - 1) printf(",");
        }
        if (i + 8 < count) printf(",");
        printf("\n");
    }
    printf("};\n\n");
}

int main() {
    print_array("GRADIENTS_2D", GRADIENTS_2D, sizeof(GRADIENTS_2D) / sizeof(float));
    print_array("RAND_VECS_2D", RAND_VECS_2D, sizeof(RAND_VECS_2D) / sizeof(float));
    print_array("GRADIENTS_3D", GRADIENTS_3D, sizeof(GRADIENTS_3D) / sizeof(float));
    print_array("RAND_VECS_3D", RAND_VECS_3D, sizeof(RAND_VECS_3D) / sizeof(float));
    return 0;
}

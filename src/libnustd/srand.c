#include "gcc/stdlib.h"

static unsigned rand_data;

/**
 * Original name: srand
 */
void srand(unsigned seed) {
    rand_data = seed;
}

/**
 * Original name: rand
 */
int rand(void) {
    rand_data = (rand_data * 20077) + 12345;

    return (rand_data >> 16) % (RAND_MAX + 1);
}

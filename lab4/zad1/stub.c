#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void compute_ones(uint32_t value)
{
    uint32_t ones_num;
    
    /* Miejsce na twoja wstawke. */
    
    printf("Number of ones in %d: %d\n", value, ones_num);
}

int main()
{
    compute_ones(0);
    compute_ones(1);
    compute_ones(3);
    compute_ones(7);
    compute_ones(8);
    compute_ones(15);
    return 0;
}

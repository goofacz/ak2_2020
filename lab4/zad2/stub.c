#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const size_t alignment = 128;
static const size_t values_num = 100;

uint8_t* generate_data(size_t values_num)
{
    uint8_t* data = (uint8_t*) aligned_alloc(alignment, values_num * sizeof(uint8_t));
    if (!data) {
        perror("Failed to allocate memory for test data!");
    }
    
    for (size_t i = 0; i < values_num; i++) {
        data[i] = 0. + (uint8_t) rand() % 255;
    }
    
    return data;
}

void print_data(const uint8_t* data, size_t values_num)
{
    for (size_t i = 0; i < values_num; i++) {
        printf("%d   ", data[i]);
        if (i > 0 && ((i + 1) % 5) == 0)   {
            printf("\n");
        }
    }

    printf("\n");
}

void reference(const uint8_t* data, size_t values_num)
{
    unsigned int counter = 0;
    
    for (size_t i = 0; i < values_num; i++) {
        if (data[i] >= 50 && data[i] <= 150) {
            counter++;
        }
    }
    
    printf("Values in range <50, 150>: %d\n", counter);
}

void student_impl(const uint8_t* data, size_t values_num)
{
    unsigned int counter = 0;
    
    /* Miejsce na twoja wstawke */
     
    printf("Values in range <50, 150>: %d\n", counter);
}

int main()
{
    uint8_t* data = generate_data(values_num);
    //print_data(data, values_num);
    reference(data, values_num);
    student_impl(data, values_num);
    free(data);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

float training[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
    {5, 10},
};

float rand_float(void)
{
    return (float) rand() / (float) RAND_MAX;
}

int main()
{
    // Y = X * W
    float weight = rand_float();
    printf("%f\n", weight);
    return 0;
}

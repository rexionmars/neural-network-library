#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Temporary colors
#define YWL "\033[0;33m"
#define OFF "\033[0m"
#define PRL "\033[0;35m"

float train[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
    {5, 10},
};

#define train_count sizeof(train) / sizeof(train[0])

float rand_float(void)
{
    return (float) rand() / (float) RAND_MAX;
}

int main()
{
    // Y = X * W
    //srand(time(0));
    srand(69);
    float weight = rand_float() * 10.0f;

    for (size_t i = 0; i < train_count; i++) {
        float x = train[i][0];
        float y = x * weight;

        printf("ACTUAL: %s%f%s, EXPECTED: %s%f%s\n", YWL, y, OFF, PRL, train[i][0], OFF);
    }

    return 0;
}

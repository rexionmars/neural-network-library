#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Temporary colors
#define OFF "\033[0m"
#define GREN "\033[0;32m"
#define RED "\033[0;31m"

float train[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
    {5, 10},
    {6, 12},
    {7, 14},
    {8, 16},
    {9, 18},
};

#define train_count sizeof(train) / sizeof(train[0])

float rand_float(void)
{
    return (float) rand() / (float) RAND_MAX;
}

float cost(float weight)
{
    float result = 0.0f;
    for (size_t i = 0; i < train_count; i++) {
        float x = train[i][0];
        float y = x * weight;
        float distance = y - train[i][1];

        result += distance * distance;
    }
    result /= train_count;
    return result;
}

int main()
{
    // Y = X * W
    srand(time(0));
    float weight = rand_float() * 10.0f;

    float eps = 1e-3;
    float rate = 1e-3;

    //printf("COST BEFORE TRAIN: %f\n", cost(weight));
    for (size_t i = 0; i < 20; ++i) {
        float distance_cost =  (cost(weight + eps) - cost(weight)) / eps;
        weight -= rate * distance_cost;
        printf("%sCOST = %f%s, WEIGHT = %f\n", RED, cost(weight), OFF, weight);
    }
    printf("\n%sWEIGHT: %f%s\n", GREN, weight, OFF);

    return 0;
}

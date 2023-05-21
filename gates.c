#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define OFF "\033[0m"
#define GREN "\033[0;32m"
#define RED "\033[0;31m"
#define YWL "\033[0;33m"
#define BLU "\033[0;34m"
#define CYN "\033[0;36m"

// Sigmoid function
// S(x) = 1 / 1 + e**-x = e**x / e**x + 1 = 1 - S(-x)
float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x));
}

// OR gate
float train[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1},
};

#define train_count sizeof(train) / sizeof(train[0])

float cost(float w1, float w2)
{
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i) {
        float x1 = train[i][0];
        float x2 = train[i][1];

        float y = sigmoidf(x1 * w1 + x2 * w2);
        float distance = y - train[i][2];
        result += distance * distance;
    }
    result /= train_count;
    return result;
}

float rand_float(void)
{
    return (float) rand() / (float) RAND_MAX;
}

int main(void)
{
    srand(time(0));
    float w1 = rand_float();
    float w2 = rand_float();
    float eps = 1e-1;
    float rate = 1e-1;

    for (size_t i = 0; i < 10000; ++i) {
        float cos = cost(w1, w2);
        printf("Weight 1: %f, Weight 2: %f, COST: %f\n", w1, w2, cos);
        float diference_w1 = (cost(w1 + eps, w2) - cos) / eps;
        float diference_w2 = (cost(w1, w2 + eps) - cos) / eps;

        w1 -= rate * diference_w1;
        w2 -= rate * diference_w2;
    }
    printf("\n%sWeight 1: %f, %sWeight 2: %f%s, COST: %f%s\n\n", YWL, w1, BLU, w2, RED, cost(w1, w2), OFF);

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            printf("%zu | %zu = %f\n", i, j, sigmoidf(i * w1 + j * w2));
        }
    }

    return 0;
}

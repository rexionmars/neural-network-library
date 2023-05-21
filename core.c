#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Temporary colors
#define OFF "\033[0m"
#define GREN "\033[0;32m"
#define RED "\033[0;31m"
#define YWL "\033[0;33m"

float train[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
};

#define train_count sizeof(train) / sizeof(train[0])

float rand_float(void)
{
    return (float) rand() / (float) RAND_MAX;
}

// Entrys: x1, x2, x3, x..., Bias
// Weights: w1, w2, w3, w...
// Y = (x1 * w1) + (x2 * w2) + (x3 * w3) + ... + Bias

float cost(float weight, float bias)
{
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i) {
        float x = train[i][0];
        float y = x * weight + bias;
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
    float bias = rand_float() * 5.0f;

    float eps = 1e-3;
    float rate = 1e-3;

    for (size_t i = 0; i < 5 * 1000; ++i) {
        float cos = cost(weight, bias);
        float diference_weight =  (cost(weight + eps, bias) - cos) / eps;
        float diference_bias = (cost(weight, bias + eps) - cos) / eps;

        weight -= rate * diference_weight;
        bias -= rate * diference_bias;

        printf("%sCOST = %f%s, WEIGHT = %f, BIAS = %f\n", RED, cost(weight, bias), OFF, weight, bias);
    }
    printf("\n%sWEIGHT: %f BIAS: %f%s\n", YWL, weight, bias, OFF);

    return 0;
}

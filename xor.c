#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float or_weight1;
    float or_weight2;
    float or_bias;

    float nand_weight1;
    float nand_weight2;
    float nand_bias;

    float and_weight1;
    float and_weight2;
    float and_bias;
} Xor;

// Sigmoid function
// S(x) = 1 / 1 + e**-x = e**x / e**x + 1 = 1 - S(-x)
float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x));
}

float forward(Xor m, float x1, float x2)
{
    // First Layer
    float a = sigmoidf(m.or_weight1 * x1 + m.or_weight2 * x2 + m.or_bias);
    float b = sigmoidf(m.nand_weight1 * x1 + m.nand_weight2 * x2 + m.nand_bias);

    // Second Layer
    return sigmoidf(a * m.and_weight1 + b * m.and_weight2 + m.and_bias);
}

typedef float sample[3];
sample xor_train[] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
};

sample *train = xor_train;
size_t train_count = 4;

float cost(Xor m)
{
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i) {
        float x1 = train[i][0];
        float x2 = train[i][1];

        float y = forward(m, x1, x2);
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

Xor rand_xor(void)
{
    Xor m;
    m.or_weight1 = rand_float();
    m.or_weight2 = rand_float();
    m.nand_weight1 = rand_float();

    m.nand_weight2 = rand_float();
    m.nand_bias = rand_float();

    m.and_weight1 = rand_float();
    m.and_weight2 = rand_float();
    m.and_bias = rand_float();

    return m;
}

void print_xor(Xor m){
    printf("or_weight1 = %f\n", m.or_weight1);
    printf("or_weight2 = %f\n", m.or_weight2);
    printf("or_bias = %f\n", m.or_bias);
    printf("nand_weight1 = %f\n", m.nand_weight1);
    printf("nand_weight2 = %f\n", m.nand_weight2);
    printf("nand_bias = %f\n", m.nand_bias);
    printf("and_weight1 = %f\n", m.and_weight1);
    printf("and_weight2 = %f\n", m.and_weight2);
    printf("and_bias = %f\n", m.and_bias);
}

int main(void)
{
    Xor m = rand_xor();
    print_xor(m);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

/*
* Sigmoid function
* S(x) = 1 / 1 + e**-x = e**x / e**x + 1 = 1 - S(-x)
*/
float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x));
}

float forward(Xor model, float x1, float x2)
{
    float a = sigmoidf(model.or_weight1*x1 + model.or_weight2 * x2+model.or_bias);
    float b = sigmoidf(model.nand_weight1*x1 + model.nand_weight2*x2 + model.nand_bias);
    return sigmoidf(a*model.and_weight1 + b*model.and_weight2 + model.and_bias);
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

float cost(Xor model)
{
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i) {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = forward(model, x1, x2);
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
    Xor model;
    model.or_weight1 = rand_float();
    model.or_weight2 = rand_float();
    model.or_bias = rand_float();

    model.nand_weight1 = rand_float();
    model.nand_weight2 = rand_float();
    model.nand_bias = rand_float();

    model.and_weight1 = rand_float();
    model.and_weight2 = rand_float();
    model.and_bias = rand_float();
    return model;
}

void print_xor(Xor model){
    printf("or_weight1 = %f\n", model.or_weight1);
    printf("or_weight2 = %f\n", model.or_weight2);
    printf("or_bias = %f\n", model.or_bias);
    printf("nand_weight1 = %f\n", model.nand_weight1);
    printf("nand_weight2 = %f\n", model.nand_weight2);
    printf("nand_bias = %f\n", model.nand_bias);
    printf("and_weight1 = %f\n", model.and_weight1);
    printf("and_weight2 = %f\n", model.and_weight2);
    printf("and_bias = %f\n", model.and_bias);
}

Xor learn(Xor model, Xor gate, float rate)
{
    model.or_weight1 -= rate * gate.or_weight1;
    model.or_weight2 -= rate * gate.or_weight2;
    model.or_bias -= rate * gate.or_bias;

    model.nand_weight1 -= rate * gate.nand_weight1;
    model.nand_weight2 -= rate * gate.nand_weight2;
    model.nand_bias -= rate * gate.nand_bias;

    model.and_weight1 -= rate * gate.and_weight1;
    model.and_weight2 -= rate * gate.and_weight2;
    model.and_bias -= rate * gate.and_bias;
    return model;
}

Xor finite_difference(Xor model, float eps)
{
    Xor gate;
    float c = cost(model);
    float saved;

    saved = model.or_weight1;
    model.or_weight1 += eps;
    gate.or_weight1 = (cost(model) - c) / eps;
    model.or_weight1 = saved;

    saved = model.or_weight2;
    model.or_weight2 += eps;
    gate.or_weight2 = (cost(model) - c) / eps;
    model.or_weight2 = saved;

    saved = model.or_bias;
    model.or_bias += eps;
    gate.or_bias = (cost(model) - c) / eps;
    model.or_bias = saved;

    saved = model.nand_weight1;
    model.nand_weight1 += eps;
    gate.nand_weight1 = (cost(model) - c) / eps;
    model.nand_weight1 = saved;

    saved = model.nand_weight2;
    model.nand_weight2 += eps;
    gate.nand_weight2 = (cost(model) - c) / eps;
    model.nand_weight2 = saved;

    saved = model.nand_bias;
    model.nand_bias += eps;
    gate.nand_bias = (cost(model) - c) / eps;
    model.nand_bias = saved;

    saved = model.and_weight1;
    model.and_weight1 +=eps;
    gate.and_weight1 = (cost(model) - c) / eps;
    model.and_weight1 = saved;

    saved = model.and_weight2;
    model.and_weight2 +=eps;
    gate.and_weight2 = (cost(model) - c) / eps;
    model.and_weight2 = saved;

    saved = model.and_bias;
    model.and_bias += eps;
    gate.and_bias = (cost(model) - c) / eps;
    model.and_bias = saved;

    return gate;
}

int main(void)
{
    Xor model = rand_xor();

    float eps = 1e-1;
    float rate = 1e-1;

    for (size_t i = 0; i < 10 * 1000; ++i) {
        Xor gate = finite_difference(model, eps);
        model = learn(model, gate, rate);
        printf("COST: %f\n", cost(model));
    }
}

#ifndef PERCEPTRON_H_INCLUDED
#define PERCEPTRON_H_INCLUDED

typedef struct
{
	float learningRate;
	float bias;
	float weights[2];
} perceptron_t;

float DotProduct(int *inputs, float *weights);
int Classify(perceptron_t *p, int *inputs);
void Train(perceptron_t *p, int *inputs, int classification);
void InitializePerceptron(perceptron_t *p);

float DotProduct(int *inputs, float *weights)
{
	float dot = 0;
	for (int i = 0; i < 2; i++)
	{
		dot += *(inputs + i) * *(weights + i);
	}
	return dot;
}

int Classify(perceptron_t *p, int *inputs)
{
	return DotProduct(inputs, p->weights) - p->bias > 0 ? 1 : 0;
}

void Train(perceptron_t *p, int *inputs, int classification)
{
	int error = classification - Classify(p, inputs);
	for (int i = 0; i < 2; i++)
	{
		p->weights[i] += p->learningRate * (float) error * *(inputs + i);
	}
}

void InitializePerceptron(perceptron_t *p)
{
	p->weights[0] = 0;
	p->weights[1] = 0;
	p->bias = 1;
	p->learningRate = 0.1;
}

#endif

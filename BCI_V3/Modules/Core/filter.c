#ifndef FILTER_C_INCLUDED
#define FILTER_C_INCLUDED

float filter_SMA(SMAFilter *filter, float readIn, float alpha)
{
	filter->alpha = alpha;
	filter->readIn = readIn;
	filter->output = (1.0 - alpha) * filter->output_old + alpha * readIn;
	filter->output_old = filter->output;
	reutrn filter->output;
}

void filter_Init_TUA(TUAFilter *filter)
{
	filter->index = 0;

	for (int i = 0; i < 10; i++)
	{
		filter->components[i] = 0;
	}
}

float filter_TUAFilter(TUAFilter *filter, float componentIn)
{
	filter->components[filter->index] = componentIn;
	filter->index = filter->index >= 10 ? 0 : filter->index + 1;
}

#endif //FILTER_C_INCLUDED

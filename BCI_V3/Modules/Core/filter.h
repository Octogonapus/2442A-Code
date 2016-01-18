#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

typedef struct SMAFilter
{
	float alpha;
	float readIn;
	float output;
	float output_old;
} SMAFilter;

typedef struct TUAFilter
{
	float components[10];
	int index;
} TUAFilter;

//Simple moving average filter
float filter_Init_SMA(SMAFilter *filter);
float filter_SMA(SMAFilter *filter, const float readIn, const float alpha);

//Ten-unit average filter
void filter_Init_TUA(TUAFilter *filter);
float filter_TUAFilter(TUAFilter *filter, const float componentIn);

#endif //FILTER_H_INCLUDED